#include "stdafx.h"
#include "MapTool.h"

HRESULT MapTool::init(void)
{
	// 기본 스테이지 1-1
	_curAbyss = 1;
	_curStage = 1;

	// 타일 깔기
	createTileMap(TILEMAX_X, TILEMAX_Y);
	createSampleTile();

	_pickingPt = { 0,0 };
	_brushOn = _dragMode = false;
	_sampleTileOn = false;
	_guideOn = false;
	_tempTileOn = false;

	// info 버튼 자리
	_miniMap = RectMake(RSCENTER_X+10, 10, 290, 190);
	_selectTile = RectMake(1164, 276, 106,106);
	_plusButton[0] = RectMake(1220, 418, 50, 50);
	_plusButton[1] = RectMake(1220, 480, 50, 50);
	_minusButton[0] = RectMake(1160, 418, 50, 50);
	_minusButton[1] = RectMake(1160, 480, 50, 50);
	_tileViewButton = RectMake(RSCENTER_X + 10, 590,100,50);
	_wallOnButton = RectMake(1095, 590, 100, 50);
	_save = RectMake(RSCENTER_X + 10, 650, 100, 50);
	_load = RectMake(1095, 650, 100, 50);
	_tileSlot = RectMake(-50, -50, 24, 24);

	_tilePos.x = 0;
	_tilePos.y = 0;

	// 저장할 데이터 타일 초기화
	_tempTile.abyssType = NONE;
	_tempTile.x = 0;
	_tempTile.y = 0;



	return S_OK;
}

void MapTool::release(void)
{
}

void MapTool::update(void)
{
	if (KEYOKD(VK_F2))  _guideOn = true; //_guide.flip();
	if (KEYOKD(VK_F3))  _guideOn = false;

	tilePosCheck();
	if (KEYOKD(VK_LBUTTON))
	{
		selectSampleTile();
		selectTile();
		infoUpdate();
	}

	if (KEYOKD('A'))
	{
		cout << "셀렉타일 실행중" << endl;
		cout << "프레임 x : " << _tile[19].fX << endl;
		cout << "프레임 y : " << _tile[19].fY << endl;
		cout << "어비스 : " << _tile[19]._abyssType << endl;
	}

}

void MapTool::render(void)
{
	IMGR("mBG",getMemDC());

	tileRender();
	imageRender();
	infoRender();

}

#pragma region TileMap init Method

// 기본 바닥 타일
void MapTool::createTileMap(int tileX, int tileY)
{
	for (int i = 0; i < tileY; i++)
	{
		for (int j = 0; j < tileX; j++)
		{
			_tile[i * tileX + j ].pos.x = j; // n번째 xy
			_tile[i * tileX + j ].pos.y = i;
			_tile[i * tileX + j ].fX = 0;	 // frame xy = 0
			_tile[i * tileX + j ].fY = 0; 
			
			_tile[i * tileX + j]._moveCheck = GROUND;
			_tile[i * tileX + j]._abyssType = NONE;

			_tile[i * tileX + j].rc=
				RectMake(0 + (j * TILESIZE_X), 0 + (i * TILESIZE_Y), TILESIZE_X, TILESIZE_Y);
		}
	}
}



// 타일셋에서 고르는 타일 확인용
void MapTool::createSampleTile()
{
	for (int i = 0; i < SAMPLEMAX_Y; ++i)
	{
		for (int j = 0; j < SAMPLEMAX_X; ++j)
		{
			_sampleTile[i * SAMPLEMAX_X + j].frameX = j;
			_sampleTile[i * SAMPLEMAX_X + j].frameY = i;

			_sampleTile[i * SAMPLEMAX_X + j].rc = 
				RectMake( 380 + (j*24), 10 + (i*24), 24,24);
		}
	}
}

#pragma endregion

#pragma region TileMap update Method

void MapTool::selectTile()
{
	for (int i = 0; i < TILEMAX_X; i++)
	{
		for (int j = 0; j < TILEMAX_Y; j++)
		{
			//바닥타일 확인
			if (PtInRect(&_tile[i * TILEMAX_X + j].rc,_ptMouse));
			{
				_tile[i * TILEMAX_X + j].fX = _tempTile.x;
				_tile[i * TILEMAX_X + j].fY = _tempTile.y;
				_tile[i * TILEMAX_X + j]._abyssType = _tempTile.abyssType;

				if (_wallOn)
				{
					_tile[i * TILEMAX_X + j]._moveCheck = GROUND;
				}
				else
				{
					_tile[i * TILEMAX_X + j]._moveCheck = WALL;
				}
			}
		}
	}
	
}

// 타일셋에서 고른 타일 저장 
void MapTool::selectSampleTile()
{
	for (int i = 0; i < SAMPLEMAX_Y; ++i)
	{
		for (int j = 0; j < SAMPLEMAX_X; ++j)
		{
			if (PtInRect(&_sampleTile[i * SAMPLEMAX_X + j].rc, _ptMouse) && _sampleTileOn)
			{
				_tempTile.abyssType = static_cast<abyssType>(_curAbyss);
				_tempTile.x = _sampleTile[i * SAMPLEMAX_X + j].frameX;
				_tempTile.y = _sampleTile[i * SAMPLEMAX_X + j].frameY;

				// 샘플타일 확인
				_tileSlot.left = _sampleTile[i * SAMPLEMAX_X + j].rc.left;
				_tileSlot.top = _sampleTile[i * SAMPLEMAX_X + j].rc.top;
			}
		}
	}
}

void MapTool::infoUpdate()
{
	if (PtInRect(&_plusButton[0], _ptMouse))
	{
		if (_curAbyss <= 8) _curAbyss++;
	}
	if (PtInRect(&_minusButton[0], _ptMouse))
	{
		if (_curAbyss > 1) _curAbyss--;
	}
	if (PtInRect(&_plusButton[1], _ptMouse))
	{
		if (_curStage <= 3) _curStage++;
	}
	if (PtInRect(&_minusButton[1], _ptMouse))
	{
		if (_curStage > 1) _curStage--;
	}
	if (PtInRect(&_save, _ptMouse))
	{
		save();
	}
	if (PtInRect(&_load, _ptMouse))
	{
		load();
	}
	if (PtInRect(&_tileViewButton, _ptMouse) && !_sampleTileOn)
	{
		_sampleTileOn = true;
	}
	else if (PtInRect(&_tileViewButton, _ptMouse) && _sampleTileOn)
	{
		_sampleTileOn = false;
	}

}

#pragma endregion

#pragma region TileMap render Method

// 베이스 타일
void MapTool::tileRender()
{

	for (int i = 0; i < TILEMAX_X * TILEMAX_Y; ++i)
	{
		//바닥타일 확인
		rcMake(getMemDC(), _tile[TILEMAX_X * TILEMAX_Y].rc);
		IMGR("tileS", getMemDC(), 1 + (_tilePos.x*TILESIZE_X), 1 + (_tilePos.y*TILESIZE_Y));



		// 어비스 타입 미저장으로 건너뛰기
		//if (_tile[TILEMAX_X * TILEMAX_Y]._abyssType == NONE) continue;
		 {
			
			switch (_curAbyss)
			{
			case 1:

				IMGFR("abyss_tile1", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, 1, 0);
				//IMGFR("abyss_tile1", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			case 2:
				IMGFR("abyss_tile2", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, 1, 0);
				//IMGFR("abyss_tile2", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			case 3:
				IMGFR("abyss_tile3", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			case 4:
				IMGFR("abyss_tile4", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			case 5:
				IMGFR("abyss_tile5", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			case 6:
				IMGFR("abyss_tile6", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			case 7:
				IMGFR("abyss_tile7", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			case 8:
				IMGFR("abyss_tile8", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			case 9:
				IMGFR("abyss_tile9", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
				break;
			}
			




		}
	}
}

void MapTool::imageRender()
{
	// 범위 밖 타일은 컨티뉴로 예외처리 할 것 
	for (int i = 0; i < TILEMAX_X * TILEMAX_Y; ++i)
	{
		// 어비스 타입 미저장으로 건너뛰기
		if (_tile[TILEMAX_X * TILEMAX_Y]._abyssType == NONE) continue;
		else {
			/*
			switch (_curAbyss)
			{
			case 1:
				IMGFR("abyss_tile1", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			case 2:
				IMGFR("abyss_tile2", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			case 3:
				IMGFR("abyss_tile3", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			case 4:
				IMGFR("abyss_tile4", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			case 5:
				IMGFR("abyss_tile5", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			case 6:
				IMGFR("abyss_tile6", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			case 7:
				IMGFR("abyss_tile7", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			case 8:
				IMGFR("abyss_tile8", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			case 9:
				IMGFR("abyss_tile9", getMemDC(), _tile[i].pos.x, _tile[i].pos.y, _tile[i].fX, _tile[i].fY);
				break;
			}
			*/
			// 오브젝트를 그리려면 타일속성에 오브젝트 enum을 추가할까?


				//벽 타일 표시
			if (_tile[i]._moveCheck == WALL)
			{

			};

		}

		IMGR("tileS", getMemDC(), 1 + (_tilePos.x*TILESIZE_X), 1 + (_tilePos.y*TILESIZE_Y));
	}
}

void MapTool::infoRender()
{
	char str[512];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	IMGR("mbg", getMemDC(), RSCENTER_X, 0);

	rcMake(getMemDC(), _miniMap); // 미니맵 
	rcMake(getMemDC(), _selectTile); // 현재 선택한 타일 크게 보기 


	// 마우스 좌표 -> 나중에 카메라 좌표 반영된걸로 수정
	sprintf_s(str, "ptMouse X : %d , Y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), RSCENTER_X + 10, 210, str, strlen(str));

	sprintf_s(str, "베이스 타일 위치");
	TextOut(getMemDC(), RSCENTER_X + 10, 240, str, strlen(str));
	sprintf_s(str, "tile X : %d , Y : %d", _tilePos.x, _tilePos.y);
	TextOut(getMemDC(), RSCENTER_X + 10, 260, str, strlen(str));

	//cout << _tilePos.x << "," << _tilePos.y << endl;

	//일단 구현은 됬는데 드래그 표시를 어떻게해야하나... 고민중
	//if (_push && _dragMode) Rectangle(getMemDC(), _dragRc);

	//sprintf_s(str, "선택한 샘플 타일 위치");
	//TextOut(getMemDC(), RSCENTER_X + 10, 290, str, strlen(str));
	//
	//sprintf_s(str, "X : %d", _tempTile.x);
	//TextOut(getMemDC(), RSCENTER_X + 10, 320, str, strlen(str));
	//
	//sprintf_s(str, "Y : %d", _tempTile.y);
	//TextOut(getMemDC(), RSCENTER_X + 10, 350, str, strlen(str));


	for (int i = 0; i < TILEMAX_X * TILEMAX_Y; ++i)
	{
		sprintf_s(str, "%d, %d", _tile[i].pos.x, _tile[i].pos.y);
	}

	sprintf_s(str, "현재 어비스 : %d ", _curAbyss);
	TextOut(getMemDC(), RSCENTER_X + 10, 418, str, strlen(str));
	sprintf_s(str, "현재 스테이지 : %d ", _curStage);
	TextOut(getMemDC(), RSCENTER_X + 10, 480, str, strlen(str));

#pragma region 맵툴버튼 배치
	// rcMake(getMemDC(), _plusButton[0]);
	// rcMake(getMemDC(), _minusButton[0]);
	// rcMake(getMemDC(), _plusButton[1]);
	// rcMake(getMemDC(), _minusButton[1]);
	// rcMake(getMemDC(), _tileView);
	// rcMake(getMemDC(), _wallOn);
	// rcMake(getMemDC(), _save);
	// rcMake(getMemDC(), _load);

	IMGR("plusB", getMemDC(), _plusButton[0].left, _plusButton[0].top);
	IMGR("plusB", getMemDC(), _plusButton[1].left, _plusButton[1].top);
	IMGR("minusB", getMemDC(), _minusButton[0].left, _minusButton[0].top);
	IMGR("minusB", getMemDC(), _minusButton[1].left, _minusButton[1].top);
	IMGR("tileSetB", getMemDC(), _tileViewButton.left, _tileViewButton.top);
	IMGR("wallB", getMemDC(), _wallOnButton.left, _wallOnButton.top);
	IMGR("saveB", getMemDC(), _save.left, _save.top);
	IMGR("loadB", getMemDC(), _load.left, _load.top);
#pragma endregion

	// 타일셋에서 몇번째 타일을 선택중인지
	sampleTileRender();

}

void MapTool::sampleTileRender()
{
	// 샘플 타일셋 
	if (_sampleTileOn)
	{
		if (_curAbyss == 1) IMGR("abyss_tile1", getMemDC(), 380, 10);
		if (_curAbyss == 2) IMGR("abyss_tile2", getMemDC(), 380, 10);
		if (_curAbyss == 3) IMGR("abyss_tile3", getMemDC(), 380, 10);
		if (_curAbyss == 4) IMGR("abyss_tile4", getMemDC(), 380, 10);
		if (_curAbyss == 5) IMGR("abyss_tile5", getMemDC(), 380, 10);
		if (_curAbyss == 6) IMGR("abyss_tile6", getMemDC(), 380, 10);
		if (_curAbyss == 7) IMGR("abyss_tile7", getMemDC(), 380, 10);
		if (_curAbyss == 8) IMGR("abyss_tile8", getMemDC(), 380, 10);
		if (_curAbyss == 9) IMGR("abyss_tile9", getMemDC(), 380, 10);

		// 샘플타일셋 내 선택타일 위치 빨간 테두리 표시 
		IMGR("tileS", getMemDC(), _tileSlot.left, _tileSlot.top);
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
	if (_tempTile.abyssType == 1) _selectTileView = IMG("abyss_tile11");
	else if (_tempTile.abyssType == 2) _selectTileView = IMG("abyss_tile22");
	else if (_tempTile.abyssType == 3) _selectTileView = IMG("abyss_tile33");
	else if (_tempTile.abyssType == 4) _selectTileView = IMG("abyss_tile44");
	else if (_tempTile.abyssType == 5) _selectTileView = IMG("abyss_tile55");
	else if (_tempTile.abyssType == 6) _selectTileView = IMG("abyss_tile66");
	else if (_tempTile.abyssType == 7) _selectTileView = IMG("abyss_tile77");
	else if (_tempTile.abyssType == 8) _selectTileView = IMG("abyss_tile88");
	else _selectTileView = IMG("abyss_tile99");

	_selectTileView->frameRender(getMemDC(), _selectTile.left + 1, _selectTile.top + 1,
		_tempTile.x, _tempTile.y);

}

#pragma endregion

void MapTool::tilePosCheck()
{
	for (int i = 0; i < TILEMAX_X; i++)
	{
		for (int j = 0; j < TILEMAX_Y; j++)
		{
			if (PtInRect(&_tile[i * TILEMAX_X + j].rc, _ptMouse))
			{
				_tilePos.x = _tile[i * TILEMAX_X + j].pos.x;
				_tilePos.y = _tile[i * TILEMAX_X + j].pos.y;


			}
		}
	}
}

void MapTool::fill(int x, int y)
{
	for (int i = 0; i < TILEMAX_X* TILEMAX_Y; ++i)
	{
		if (!_wallOn) _tile[i]._moveCheck = GROUND;
		else  _tile[i]._moveCheck = WALL;
		_tile[i].fX = x;
		_tile[i].fY = y;
	}
}

void MapTool::save()
{

	if (PtInRect(&_save, _ptMouse))
	{

		HANDLE file;
		DWORD write;

		if (_curAbyss == 1)
		{
			if (_curStage == 1)
			{
				//file = CreateFile("1-1.txt", GENERIC_WRITE, NULL, NULL,
				//	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				//
				//WriteFile(file, _tile, sizeof(_tile) * TILEMAX_X * TILEMAX_Y, &write, NULL);
				//CloseHandle(file);
				cout <<  "1-1 파일 저장 클릭 " <<endl;
			}
		}
	}

	
}

void MapTool::load()
{
}



