#include "stdafx.h"
#include "MapTool.h"
int tempC = 0;
HRESULT MapTool::init(void)
{
	// 기본 스테이지 1-1
	_curAbyss = 1;
	_curStage = 1;
	_curTileIndex = -1;

	_startTileX = _startTileY = _endTileX = _endTileY = _countX = _countY = 0;

	// 타일 깔기
	createTileMap();
	createSampleTile();
	createMiniMapTile();
	_sampleTileOn = false;
	_inSampleTile = false;
	_guideOn = false;
	_wallOn = false;
	_tempTileOn = false;

	_pickingPt = { 0,0 };
	_cameraPtMouse = { 0,0 };
	_brushOn = _dragMode = false;


	// info 배치
	_sampleTileRect = RectMake(WINSIZE_X - 900, 10,
		IMG("abyss_tile11")->getWidth(), IMG("abyss_tile11")->getHeight());

	_miniMap = RectMake(WINSIZE_X - 310, 10, 290, 190);
	_selectTile = RectMake(WINSIZE_X - 116, 276, 106, 106);
	_plusButton[ABYSSRC] = RectMake(WINSIZE_X - 60, 418, 50, 50);
	_plusButton[STAGERC] = RectMake(WINSIZE_X - 60, 480, 50, 50);
	_minusButton[ABYSSRC] = RectMake(WINSIZE_X - 120, 418, 50, 50);
	_minusButton[STAGERC] = RectMake(WINSIZE_X - 120, 480, 50, 50);
	_clear = RectMake(WINSIZE_X - 60, 535, 50, 50);
	_tileViewButton = RectMake(WINSIZE_X - 310, 590, 100, 50);
	_wallOnButton = RectMake(WINSIZE_X - 206, 590, 100, 50);
	_fillAllTile = RectMake(WINSIZE_X - 102, 590, 100, 50);
	_save = RectMake(WINSIZE_X - 310, 650, 100, 50);
	_load = RectMake(WINSIZE_X - 206, 650, 100, 50);
	//_undo = RectMake(WINSIZE_X-102, 650, 100, 50); // 터져서 막아둠
	_tileSlot = RectMake(-500, -500, TILESIZE_X, TILESIZE_Y);

	// 현재 타일 정보 
	_tilePos.x = 0;
	_tilePos.y = 0;

	// 저장할 데이터 타일 초기화
	_tempTile.abyssType = NONE;
	_tempTile.x = 0;
	_tempTile.y = 0;


	// 카메라
	int camLimitLeft;
	camLimitLeft = (WINSIZE_X - 310)*0.5;
	createCameraLimit();
	CAM->init();
	CAM->setLimitsX(camLimitLeft, _curMapSize.x);
	CAM->setLimitsY(CENTER_Y, _curMapSize.y);
	_curPos = { 740 , CENTER_Y };

	return S_OK;
}

void MapTool::release(void)
{
}

void MapTool::update(void)
{
	if (KEYOKD(VK_F2))  _guideOn = true;
	if (KEYOKD(VK_F3))  _guideOn = false;

	// 카메라 반영
	POINT cameraPos;
	cameraPos = _curPos;
	CAM->setCameraPos(cameraPos);
	CAM->update();
	camControl();

	if (KEYSKD(VK_UP)) _curPos.y -= 4;
	if (KEYSKD(VK_DOWN)) _curPos.y += 4;
	if (KEYSKD(VK_LEFT)) _curPos.x -= 4;
	if (KEYSKD(VK_RIGHT)) _curPos.x += 4;

	// 타일 위 마우스위치 체크 
	ptInTileCheck();

	// 맵툴 기능
	if (KEYOKD(VK_LBUTTON))
	{
		infoUpdate();
	}
	if (KEYSKD(VK_LBUTTON))
	{
		selectSampleTile();
		selectTile();
	}
	if (KEYOKU(VK_LBUTTON))
	{
		for (int i = 0; i < SAMPLEMAX_X*SAMPLEMAX_Y; ++i)
		{

			if (PtInRect(&_sampleTile[i].rc, _cameraPtMouse))
			{
				_endTileX = _sampleTile[i].frameX;
				_endTileY = _sampleTile[i].frameY;
				clearCurTile();
				setCurTile(_endTileX - _startTileX, _endTileY - _startTileY);
				for (int i = 0; i < _startTileX*_startTileY; ++i)
				{
					//addCurTile(_tile[i]);
				}
			}
		}
	}

	//if (_curTileIndex != -1 && n != _curTileIndex)
	{
		//	if (n == 0) cout << "false" << endl;
		//	_tile[n].ptInRect = false;
			//_tilePos.x = _tile[n].pos.x;
			//_tilePos.y = _tile[n].pos.y;
	}

}

void MapTool::render(void)
{
	camLeft = CAM->getScreenRect().left;
	camTop = CAM->getScreenRect().top;
	IMGR("mBG", getMemDC(), 0 - camLeft, 0 - camTop);

	tileRender();
	imageRender();
	infoRender();

}

#pragma region TileMap init Method

void MapTool::createCameraLimit()
{
	_curMapSize.x = 2000;
	_curMapSize.y = 2000;
	//_curMapSize.x = TILEMAX_X * TILESIZE_X;
	//_curMapSize.y = TILEMAX_Y * TILESIZE_Y;
}

void MapTool::createTileMap()
{
	for (int i = 0; i < TILEMAX_Y; i++)
	{
		for (int j = 0; j < TILEMAX_X; j++)
		{
			_tile[i * TILEMAX_X + j].pos.x = j;
			_tile[i * TILEMAX_X + j].pos.y = i;
			_tile[i * TILEMAX_X + j].fX = 0;
			_tile[i * TILEMAX_X + j].fY = 0;
			_tile[i * TILEMAX_X + j].onDraw = false;
			_tile[i * TILEMAX_X + j].ptInRect = false;
			_tile[i * TILEMAX_X + j]._moveCheck = GROUND;
			_tile[i * TILEMAX_X + j]._abyssType = NONE;

			_tile[i * TILEMAX_X + j].rc =
				RectMake(0 + (j * TILESIZE_X), 0 + (i * TILESIZE_Y), TILESIZE_X, TILESIZE_Y);
		}
	}
}

void MapTool::createSampleTile()
{
	for (int i = 0; i < SAMPLEMAX_Y; ++i)
	{
		for (int j = 0; j < SAMPLEMAX_X; ++j)
		{
			_sampleTile[i * SAMPLEMAX_X + j].frameX = j;
			_sampleTile[i * SAMPLEMAX_X + j].frameY = i;

			_sampleTile[i * SAMPLEMAX_X + j].rc =
				RectMake(380 + (j*TILESIZE_X), 10 + (i*TILESIZE_Y), TILESIZE_X, TILESIZE_Y);
		}
	}

}

void MapTool::createMiniMapTile()
{
	int temp;
	temp = 4;
	for (int i = 0; i < TILEMAX_Y; ++i)
	{
		for (int j = 0; j < TILEMAX_X; ++j)
		{
			_minimapTile[i * TILEMAX_X + j].pos.x = j;
			_minimapTile[i * TILEMAX_X + j].pos.y = i;
			_minimapTile[i * TILEMAX_X + j].fX = 2;
			_minimapTile[i * TILEMAX_X + j].fY = 2;
			_minimapTile[i * TILEMAX_X + j]._abyssType = ABYSS2;;

			_minimapTile[i * TILEMAX_X + j].rc =
				RectMake(WINSIZE_X - 310 + (j*TILEMAX_X), 10 + (i*TILEMAX_Y), temp, temp);
		}
	}

}

#pragma endregion

#pragma region TileMap update Method

void MapTool::selectTile()
{
	tagTileStage tileDate;

	for (int i = 0; i < TILEMAX_X*TILEMAX_Y; i++)
	{
		//바닥타일 확인
		if (PtInRect(&_tile[i].rc, _ptMouse) && !_inSampleTile)
		{
			_tile[i].fX = _tempTile.x;
			_tile[i].fY = _tempTile.y;
			_tile[i].onDraw = true;
			_tile[i]._abyssType = _tempTile.abyssType;
			_tile[i]._moveCheck = GROUND;

			// nudo 데이터 저장
			tileDate.tile[i].fX = _tile[i].fX;
			tileDate.tile[i].fY = _tile[i].fY;
			tileDate.tile[i].onDraw = _tile[i].onDraw;
			tileDate.tile[i]._abyssType = _tile[i]._abyssType;
			tileDate.tile[i]._moveCheck = _tile[i]._moveCheck;
		}
		if (PtInRect(&_tile[i].rc, _ptMouse) && !_inSampleTile && _wallOn)
		{
			_tile[i]._moveCheck = WALL;
			tileDate.tile[i]._moveCheck = _tile[i]._moveCheck;
		}
	}

	//_sTile.push(tileDate);




}

void MapTool::selectSampleTile()
{
	if (_sampleTileOn && _ptMouse.x > 0 && _ptMouse.y > 0)
	{

		// 마우스 좌표로 검사할 타일 찾기
		int indexX;
		int indexY;

		indexX = (_cameraPtMouse.x - (WINSIZE_X - 900)) / TILESIZE_X;
		indexY = (_cameraPtMouse.y - 10) / TILESIZE_Y;

		int n = indexX * indexY;

		_tempTile.abyssType = static_cast<abyssType>(_curAbyss);
		_tempTile.x = _sampleTile[n].frameX;
		_tempTile.y = _sampleTile[n].frameY;

		// info에서 샘플타일 확인
		_tileSlot.left = _sampleTile[n].rc.left;
		_tileSlot.top = _sampleTile[n].rc.top;
		cout << "index X : " << indexX << " , index Y :" << indexY << endl;
		cout << "선택샘플타일슬롯 L : " << _tileSlot.left << endl;
	}


	// 타일 범위 선택 시 
	_tempTile.x = _startTileX;
	_tempTile.y = _startTileY;
	_dragMode = true;


	/*
	for (int i = 0; i < SAMPLEMAX_X*SAMPLEMAX_Y; ++i)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse) && _sampleTileOn)
		{
			_tempTile.abyssType = static_cast<abyssType>(_curAbyss);
			_tempTile.x = _sampleTile[i].frameX;
			_tempTile.y = _sampleTile[i].frameY;

			// info에서 샘플타일 확인
			_tileSlot.left = _sampleTile[i].rc.left;
			_tileSlot.top = _sampleTile[i].rc.top;
		}

	}
	*/
}

void MapTool::infoUpdate()
{

	if (PtInRect(&_plusButton[ABYSSRC], _cameraPtMouse))
	{
		if (_curAbyss <= 8) _curAbyss++;
	}
	if (PtInRect(&_minusButton[ABYSSRC], _cameraPtMouse))
	{
		if (_curAbyss > 1) _curAbyss--;
	}
	if (PtInRect(&_plusButton[STAGERC], _cameraPtMouse))
	{
		if (_curStage <= 3) _curStage++;
	}
	if (PtInRect(&_minusButton[STAGERC], _cameraPtMouse))
	{
		if (_curStage > 1) _curStage--;
	}
	if (PtInRect(&_clear, _cameraPtMouse))
	{
		clear();
	}
	if (PtInRect(&_fillAllTile, _cameraPtMouse))
	{
		fill(_tempTile.abyssType, _tempTile.x, _tempTile.y);
	}
	if (PtInRect(&_undo, _cameraPtMouse))
	{
		undo();
	}
	if (PtInRect(&_save, _cameraPtMouse))
	{
		save();
	}
	if (PtInRect(&_load, _cameraPtMouse))
	{
		load();
	}

	if (PtInRect(&_wallOnButton, _cameraPtMouse) && !_wallOn)
	{
		_wallOn = true;
	}
	else if (PtInRect(&_wallOnButton, _cameraPtMouse))
	{
		_wallOn = false;
	}

	if (PtInRect(&_tileViewButton, _cameraPtMouse) && !_sampleTileOn)
	{
		_sampleTileOn = true;
	}
	else if (PtInRect(&_tileViewButton, _cameraPtMouse) && _sampleTileOn)
	{
		_sampleTileOn = false;
	}




}

void MapTool::camControl()
{
	// 샘플타일셋이 꺼져있고, 인포부분에 마우스가 있다면 : 논리좌표
	if (!_sampleTileOn && _ptMouse.x > WINSIZE_X - 320)
	{
		_cameraPtMouse.x = _ptMouse.x;
		_cameraPtMouse.y = _ptMouse.y;
	}
	// 샘플타일셋이 켜져있고, 
	else if (_sampleTileOn)
	{
		// 인포부분에 마우스가 있다면 : 논리좌표
		if (_ptMouse.x > WINSIZE_X - 320)
		{
			_cameraPtMouse.x = _ptMouse.x;
			_cameraPtMouse.y = _ptMouse.y;
		}
		// 샘플타일셋 렉트 안에 마우스가 있다면 : 논리좌표
		else if (_inSampleTile)
		{
			_cameraPtMouse.x = _ptMouse.x;
			_cameraPtMouse.y = _ptMouse.y;
		}
	}


	// 샘플타일셋 꺼져있고, 인포 부분이 아니면 : 상대좌표 
	if (!_sampleTileOn && _ptMouse.x < WINSIZE_X - 320)
	{
		_cameraPtMouse.x = _ptMouse.x + CAM->getScreenRect().left;
		_cameraPtMouse.y = _ptMouse.y + CAM->getScreenRect().top;
	}
	// 샘플타일셋 켜져있고, 샘플타일셋 렉트 안에 마우스가 없으면 : 상대좌표 
	if (_sampleTileOn && !_inSampleTile)
	{
		_cameraPtMouse.x = _ptMouse.x + CAM->getScreenRect().left;
		_cameraPtMouse.y = _ptMouse.y + CAM->getScreenRect().top;
	}

}


#pragma endregion

#pragma region TileMap render Method

void MapTool::tileRender()
{
	for (int i = 0; i < TILEMAX_X*TILEMAX_Y; ++i)
	{
		// 바닥 타일 보기
		Rectangle(getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top,
			_tile[i].rc.left - CAM->getScreenRect().left + TILESIZE_X, _tile[i].rc.top - CAM->getScreenRect().top + TILESIZE_Y);


		// 어비스 타입 미저장 건너뛰기
		if (_tile[i]._abyssType == NONE) { ; }
		if (_tile[i]._abyssType == ABYSS1)
		{
			IMGFR("abyss_tile1", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS2)
		{
			IMGFR("abyss_tile2", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS3)
		{
			IMGFR("abyss_tile3", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS4)
		{
			IMGFR("abyss_tile4", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS5)
		{
			IMGFR("abyss_tile5", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS6)
		{
			IMGFR("abyss_tile6", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS7)
		{
			IMGFR("abyss_tile7", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS8)
		{
			IMGFR("abyss_tile8", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);
		}
		else IMGFR("abyss_tile9", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top, _tile[i].fX, _tile[i].fY);


		// 벽타일 설정 시 추가 렌더
		if (_tile[i]._moveCheck == GROUND) continue;
		else IMGR("wallMark", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top);

	}

	for (int i = 0; i < TILEMAX_X*TILEMAX_Y; ++i)
	{
		if (i == 0 && tempC++ % 15 == 0) {
			if (_tile[i].ptInRect)cout << "pt true" << endl;
			else cout << "pt false" << endl;

		}
		// 바닥 타일 중 마우스가 위치한 타일
		if (_tile[i].ptInRect)
			IMGR("tileS", getMemDC(), _tile[i].rc.left - CAM->getScreenRect().left, _tile[i].rc.top - CAM->getScreenRect().top);
		else continue;
	}



}

void MapTool::imageRender()
{

	//벽 타일 표시
	if (_tile[0]._moveCheck == WALL)
	{

	};



}

void MapTool::infoRender()
{
	IMGR("mbg", getMemDC(), WINSIZE_X - 320, 0);
	rcMake(getMemDC(), _miniMap); // 미니맵 
	rcMake(getMemDC(), _selectTile); // 현재 선택한 타일 크게 보기 

	char str[2000];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	// 마우스 좌표 -> 나중에 카메라 좌표 반영된걸로 수정
	sprintf_s(str, "ptMouse X : %d , Y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), WINSIZE_X - 210, 210, str, strlen(str));

	sprintf_s(str, "CAMMouse X : %d , Y : %d", _cameraPtMouse.x, _cameraPtMouse.y);
	TextOut(getMemDC(), WINSIZE_X - 210, 230, str, strlen(str));

	sprintf_s(str, "베이스 타일 위치");
	TextOut(getMemDC(), WINSIZE_X - 310, 280, str, strlen(str));
	sprintf_s(str, "tile X : %d , Y : %d", _tilePos.x, _tilePos.y);
	TextOut(getMemDC(), WINSIZE_X - 310, 300, str, strlen(str));

	sprintf_s(str, "현재 어비스 : %d ", _curAbyss);
	TextOut(getMemDC(), WINSIZE_X - 310, 418, str, strlen(str));
	sprintf_s(str, "현재 스테이지 : %d ", _curStage);
	TextOut(getMemDC(), WINSIZE_X - 310, 480, str, strlen(str));


	if (_wallOn)
	{
		sprintf_s(str, "벽타일 설정 중!!");
		TextOut(getMemDC(), WINSIZE_X - 310, 570, str, strlen(str));
	}

#pragma region 맵툴버튼 배치
	// rcMake(getMemDC(), _plusButton[ABYSSRC]);
	// rcMake(getMemDC(), _minusButton[ABYSSRC]);
	// rcMake(getMemDC(), _plusButton[STAGERC]);
	// rcMake(getMemDC(), _minusButton[STAGERC]);
	// rcMake(getMemDC(), _tileView);
	// rcMake(getMemDC(), _wallOn);
	// rcMake(getMemDC(), _fillAllTile);
	// rcMake(getMemDC(), _save);
	// rcMake(getMemDC(), _load);
	// rcMake(getMemDC(), _undo);

	IMGR("plusB", getMemDC(), _plusButton[ABYSSRC].left, _plusButton[ABYSSRC].top);
	IMGR("plusB", getMemDC(), _plusButton[STAGERC].left, _plusButton[STAGERC].top);
	IMGR("minusB", getMemDC(), _minusButton[ABYSSRC].left, _minusButton[ABYSSRC].top);
	IMGR("minusB", getMemDC(), _minusButton[STAGERC].left, _minusButton[STAGERC].top);
	IMGR("clearB", getMemDC(), _clear.left, _clear.top);
	IMGR("tileSetB", getMemDC(), _tileViewButton.left, _tileViewButton.top);
	if (!_wallOn) IMGR("wallB", getMemDC(), _wallOnButton.left, _wallOnButton.top);
	else IMGR("wallB_on", getMemDC(), _wallOnButton.left, _wallOnButton.top);
	IMGR("fillB", getMemDC(), _fillAllTile.left, _fillAllTile.top);
	IMGR("saveB", getMemDC(), _save.left, _save.top);
	IMGR("loadB", getMemDC(), _load.left, _load.top);
	IMGR("undoB", getMemDC(), _undo.left, _undo.top);

#pragma endregion

	// 타일셋에서 몇번째 타일을 선택중인지
	sampleTileRender();


}

void MapTool::sampleTileRender()
{
	// 샘플 타일셋 
	if (_sampleTileOn)
	{
		if (_curAbyss == 1) IMGR("abyss_tile1", getMemDC(), WINSIZE_X - 900, 10);
		if (_curAbyss == 2) IMGR("abyss_tile2", getMemDC(), WINSIZE_X - 900, 10);
		if (_curAbyss == 3) IMGR("abyss_tile3", getMemDC(), WINSIZE_X - 900, 10);
		if (_curAbyss == 4) IMGR("abyss_tile4", getMemDC(), WINSIZE_X - 900, 10);
		if (_curAbyss == 5) IMGR("abyss_tile5", getMemDC(), WINSIZE_X - 900, 10);
		if (_curAbyss == 6) IMGR("abyss_tile6", getMemDC(), WINSIZE_X - 900, 10);
		if (_curAbyss == 7) IMGR("abyss_tile7", getMemDC(), WINSIZE_X - 900, 10);
		if (_curAbyss == 8) IMGR("abyss_tile8", getMemDC(), WINSIZE_X - 900, 10);
		if (_curAbyss == 9) IMGR("abyss_tile9", getMemDC(), WINSIZE_X - 900, 10);

		// 샘플타일셋 내 선택타일 위치 빨간 테두리 표시 
		IMGR("tileS", getMemDC(), _tileSlot.left - CAM->getScreenRect().left, _tileSlot.top - CAM->getScreenRect().top);
	}

	// F2 가이드 On
	if (_guideOn)
	{
		// 샘플 타일셋 이미지가 켜져있으면 
		if (_sampleTileOn)
		{
			for (int i = 0; i < SAMPLEMAX_Y; i++)
			{
				for (int j = 0; j < SAMPLEMAX_X; j++)
				{
					// 샘플타일셋의 rc위치 확인용
					rcMake(getMemDC(), _sampleTile[i * SAMPLEMAX_X + j].rc);
				}
			}
		}
	}

	// 인포에서 선택된 샘플 타일셋 크게 보기
	if (_tempTile.abyssType == 0) _selectTileView = IMG("abyss_tile11");
	else if (_tempTile.abyssType == 1) _selectTileView = IMG("abyss_tile11");
	else if (_tempTile.abyssType == 2) _selectTileView = IMG("abyss_tile22");
	else if (_tempTile.abyssType == 3) _selectTileView = IMG("abyss_tile33");
	else if (_tempTile.abyssType == 4) _selectTileView = IMG("abyss_tile44");
	else if (_tempTile.abyssType == 5) _selectTileView = IMG("abyss_tile55");
	else if (_tempTile.abyssType == 6) _selectTileView = IMG("abyss_tile66");
	else if (_tempTile.abyssType == 7) _selectTileView = IMG("abyss_tile77");
	else if (_tempTile.abyssType == 8) _selectTileView = IMG("abyss_tile88");
	else _selectTileView = IMG("abyss_tile99");

	_selectTileView->frameRender(getMemDC(), (_selectTile.left + 1) - CAM->getScreenRect().left,
		(_selectTile.top + 1) - CAM->getScreenRect().top,
		_tempTile.x, _tempTile.y);

}

#pragma endregion

#pragma region TileMap function
void MapTool::ptInTileCheck()
{
	if (_sampleTileOn)
	{
		// 타일셋 켜져있고, 절대좌표에서 확인되면 타일체크 중
		if (PtInRect(&_sampleTileRect, _ptMouse)) {
			_inSampleTile = true;
		}
		else {
			_inSampleTile = false;
		};
	}



	// 마우스 좌표로 검사할 타일 찾기
	int indexX;
	int indexY;
	int n;

	if ((_cameraPtMouse.x >= 0 && _cameraPtMouse.x <= CAM->getScreenRect().right)
		&& (_cameraPtMouse.y >= 0 && _cameraPtMouse.y <= CAM->getScreenRect().bottom))
	{
		indexX = _cameraPtMouse.x / TILESIZE_X;
		indexY = _cameraPtMouse.y / TILESIZE_Y;

		n = indexY * TILEMAX_X + indexX;
		_curTileIndex = n; // 이전 인덱스를 저장해서, 다음거에서 바꿈
		// 좌측 베이스 타일 체크 
		if (PtInRect(&_tile[n].rc, _cameraPtMouse))
		{
			if (n == 0 && tempC++ % 15 == 0) {
				cout << _tile[n].rc.left << endl;
				cout << _tile[n].rc.top << endl;
				cout << _tile[n].rc.right << endl;
				cout << _tile[n].rc.bottom << endl;
				cout << "//" << endl;
				cout << _cameraPtMouse.x << endl;
				cout << _cameraPtMouse.y << endl;
			}
			_tile[n].ptInRect = true;
			//_tilePos.x = _tile[n].pos.x;
			//_tilePos.y = _tile[n].pos.y;
		}

	}


	//============================================================================================================
		// 우측 샘플 타일 체크 

	if (PtInRect(&_sampleTileRect, _cameraPtMouse) && _sampleTileOn)
	{
		//_inSampleTile = true;
	}
	if (!PtInRect(&_sampleTileRect, _cameraPtMouse) && _sampleTileOn)
	{
		//_inSampleTile = false;
	}


	// 작성중
	if ((_cameraPtMouse.x >= _sampleTileRect.left && _cameraPtMouse.x <= _sampleTileRect.right)
		&& (_cameraPtMouse.y >= _sampleTileRect.top && _cameraPtMouse.y <= _sampleTileRect.bottom))
	{
		indexX = _cameraPtMouse.x / TILESIZE_X;
		indexY = _cameraPtMouse.y / TILESIZE_Y;

		n = indexY * TILEMAX_X + indexX;

		// 우측 샘플 타일 체크 
		if (PtInRect(&_tile[n].rc, _cameraPtMouse))
		{
			//_tile[n].ptInRect = true;
			_tilePos.x = _tile[n].pos.x;
			_tilePos.y = _tile[n].pos.y;
		}
	}


}

void MapTool::clear()
{
	tagTileStage tileDate;

	for (int i = 0; i < TILEMAX_X* TILEMAX_Y; ++i)
	{
		_tile[i].fX = 0;
		_tile[i].fY = 0;
		_tile[i].onDraw = false;
		_tile[i]._abyssType = static_cast<abyssType>(NONE);
		_tile[i]._moveCheck = GROUND;

		// nudo 데이터 저장
		tileDate.tile[i].fX = _tile[i].fX;
		tileDate.tile[i].fY = _tile[i].fY;
		tileDate.tile[i].onDraw = _tile[i].onDraw;
		tileDate.tile[i]._abyssType = _tile[i]._abyssType;
		tileDate.tile[i]._moveCheck = _tile[i]._moveCheck;
	}
	_sTile.push(tileDate);
}

void MapTool::fill(int abyss, int x, int y)
{
	tagTileStage tileDate;


	for (int i = 0; i < TILEMAX_X* TILEMAX_Y; ++i)
	{
		if (!_wallOn) _tile[i]._moveCheck = GROUND;
		else  _tile[i]._moveCheck = WALL;

		_tile[i].fX = x;
		_tile[i].fY = y;
		_tile[i].onDraw = true;
		_tile[i]._abyssType = static_cast<abyssType>(abyss);


		// nudo 데이터 저장
		tileDate.tile[i].fX = x;
		tileDate.tile[i].fY = y;
		tileDate.tile[i].onDraw = true;
		tileDate.tile[i]._abyssType = static_cast<abyssType>(abyss);
		tileDate.tile[i]._moveCheck = _tile[i]._moveCheck;
	}
	_sTile.push(tileDate);
}

void MapTool::undo()
{
	if (_sTile.empty()) return;
	else
	{
		while (true)
		{
			bool isSame = true;

			for (int i = 0; i < TILEMAX_X* TILEMAX_Y; ++i)
			{
				if (_tile[i].onDraw != _sTile.top().tile[i].onDraw)
				{
					isSame = false;
					break;
				}

				if (isSame)
				{
					// 마지막 타일 정보를 뺀 후 
					_sTile.pop();

					// 스택의 마지막 정보를 현재 타일로 바꿈
					_undoTile[i] = _sTile.top().tile[i];
					_sTile.pop();
				}
				else
					break;
			}
		}
	}

}

void MapTool::save()
{
	if (PtInRect(&_save, _cameraPtMouse))
	{
		HANDLE file;
		DWORD write;

		if (_curAbyss == 1)
		{
			if (_curStage == 1)
			{
				file = CreateFile("1-1.txt", GENERIC_WRITE, NULL, NULL,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

				WriteFile(file, _tile, sizeof(_tile) * TILEMAX_X * TILEMAX_Y, &write, NULL);
				CloseHandle(file);
				cout << "1-1 파일 저장 클릭 " << endl;
			}
		}
	}


}

void MapTool::load()
{
	if (PtInRect(&_save, _cameraPtMouse))
	{
		HANDLE file;
		DWORD read;

		if (_curAbyss == 1)
		{
			if (_curStage == 1)
			{
			}
		}
	}
}

Tile MapTool::tileDataSave(Tile tileValue)
{
	Tile tileDate;
	tileDate.fX = tileValue.fX;
	tileDate.fY = tileValue.fY;
	tileDate.onDraw = tileValue.onDraw;
	tileDate._abyssType = tileValue._abyssType;
	tileDate._moveCheck = tileValue._moveCheck;

	return tileDate;
}

#pragma endregion


