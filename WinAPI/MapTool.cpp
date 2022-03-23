#include "stdafx.h"
#include "MapTool.h"

HRESULT MapTool::init(void)
{
	_curAbyss =	_curStage = 1;
	createTileMap(TILEMAX_X, TILEMAX_Y);
	createSampleTile();
	_pickingPt = { 0,0 };
	_brushOn = _dragMode = false;
	_tileOn = false;
	_isWall = false;
	_guideOn = false;
	//_guide.reset();

	_miniMap = RectMake(RSCENTER_X+10, 10, 290, 190);
	_selectTile = RectMake(1164, 276, 106,106);
	_plusButton[0] = RectMake(1220, 418, 50, 50);
	_plusButton[1] = RectMake(1220, 480, 50, 50);
	_minusButton[0] = RectMake(1160, 418, 50, 50);
	_minusButton[1] = RectMake(1160, 480, 50, 50);
	_tileView = RectMake(RSCENTER_X + 10, 590,100,50);
	_wallOn = RectMake(1095, 590, 100, 50);
	_save = RectMake(RSCENTER_X + 10, 650, 100, 50);
	_load = RectMake(1095, 650, 100, 50);
	_tileSlot = RectMake(-50, -50, 24, 24);

	_tempTile.abyssType = NONE;
	_tempTile.x = 0;
	_tempTile.y = 0;

	//_sampleTile._rc
	return S_OK;
}

void MapTool::release(void)
{
}

void MapTool::update(void)
{
	if (KEYOKD(VK_F2))  _guideOn = true; //_guide.flip();
	if (KEYOKD(VK_F3))  _guideOn = false;


	if (KEYOKD(VK_LBUTTON))
	{
		selectSampleTile();
		infoUpdate();
	}

}

void MapTool::render(void)
{
	IMGR("mBG",getMemDC());

	infoRender();
	imageRender();
	tileRender();


}

#pragma region TileMap Method

void MapTool::createTileMap(int tileX, int tileY)
{
	for (int i = 0; i < tileY; i++)
	{
		for (int j = 0; j < tileX; j++)
		{
			_tile[i * tileX + j ].fX = 0; // 프레임xy = 0
			_tile[i * tileX + j ].fY = 0; 
			_tile[i * tileX + j ].nX = j; 
			_tile[i * tileX + j ].nY = i;

			_tile[i * tileX + j].inTile = false;
			_tile[i * tileX + j]._moveCheck = GROUND;
			_tile[i * tileX + j]._abyssType = NONE;
		}
	}

}

void MapTool::createTile()
{
	if (_tileOn)
	{
		// 2중 포문으로 x,y 검출 
		if (PtInRect(&_tileView, _ptMouse))
		{

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

// 타일셋에서 고른 타일 저장 
void MapTool::selectSampleTile()
{
	for (int i = 0; i < SAMPLEMAX_Y; ++i)
	{
		for (int j = 0; j < SAMPLEMAX_X; ++j)
		{
			if (PtInRect(&_sampleTile[i * SAMPLEMAX_X + j].rc, _ptMouse) && _tileOn)
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
	
	cout << _tempTile.x << endl;
}


	// F2 가이드 On
void MapTool::tileRender()
{
	//if (_guide.any())
	if (_guideOn)
	{
		for (int i = 0; i < TILEMAX_X; i++)
		{
			for (int j = 0; j < TILEMAX_Y; j++)
			{

			}
		}		


		if (_tileOn)
		{
			for (int i = 0; i < SAMPLEMAX_Y; i++)
			{
				for (int j = 0; j < SAMPLEMAX_X; j++)
				{
					rcMake(getMemDC(), _sampleTile[i * SAMPLEMAX_X + j].rc);
				}
			}
		}
	}




	for (int i = 0; i < SAMPLEMAX_Y; i++)
	{
		for (int j = 0; j < SAMPLEMAX_X; j++)
		{
		//	rcMake(getMemDC(), _sampleTile[j * i].rc);
			int n = j * i;
		//	cout << "rc" << n <<": On " << endl;
		}

	}
}



#pragma endregion

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

void MapTool::imageRender()
{
	if (_tileOn)
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

		IMGR("tileS", getMemDC(), _tileSlot.left, _tileSlot.top);
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
	if (PtInRect(&_tileView, _ptMouse) && !_tileOn)
	{
		_tileOn = true;
	}
	else if (PtInRect(&_tileView, _ptMouse) && _tileOn)
	{
		_tileOn = false;
	}

	if (PtInRect(&_wallOn, _ptMouse) && ! _isWall)
	{
		_isWall = true;
	}
	else if (PtInRect(&_wallOn, _ptMouse) && _isWall)
	{
		_isWall = false;
	}
}

void MapTool::infoRender()
{
	char str[256];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	IMGR("mbg", getMemDC(), RSCENTER_X, 0);

	rcMake(getMemDC(), _miniMap); // 미니맵 
	rcMake(getMemDC(), _selectTile); // 현재 선택한 타일 크게 보기 


	// 마우스 좌표 -> 나중에 카메라 좌표 반영된걸로 수정
	sprintf_s(str, "ptMouse X : %d , Y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), RSCENTER_X + 10, 230, str, strlen(str));

	//일단 구현은 됬는데 드래그 표시를 어떻게해야하나... 고민중
	//if (_push && _dragMode) Rectangle(getMemDC(), _dragRc);



	// 타일셋에서 몇번째 타일을 선택중인지
	sampleRender();

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
		sprintf_s(str, "%d, %d", _tile[i].nX, _tile[i].nY);
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
	IMGR("tileSetB", getMemDC(), _tileView.left, _tileView.top);
	IMGR("wallB", getMemDC(), _wallOn.left, _wallOn.top );
	IMGR("saveB", getMemDC(), _save.left, _save.top );
	IMGR("loadB", getMemDC(), _load.left , _load.top);



#pragma endregion






}

void MapTool::sampleRender()
{
	if (_tempTile.abyssType == 1) _selectTileView	   =IMG("abyss_tile11");
	else if (_tempTile.abyssType == 2) _selectTileView =IMG("abyss_tile22");
	else if (_tempTile.abyssType == 3) _selectTileView =IMG("abyss_tile33");
	else if (_tempTile.abyssType == 4) _selectTileView =IMG("abyss_tile44");
	else if (_tempTile.abyssType == 5) _selectTileView =IMG("abyss_tile55");
	else if (_tempTile.abyssType == 6) _selectTileView =IMG("abyss_tile66");
	else if (_tempTile.abyssType == 7) _selectTileView =IMG("abyss_tile77");
	else if (_tempTile.abyssType == 8) _selectTileView =IMG("abyss_tile88");
	else _selectTileView							   =IMG("abyss_tile99");

	_selectTileView->frameRender(getMemDC(), _selectTile.left+1, _selectTile.top+1,
		_tempTile.x, _tempTile.y);

}

void MapTool::fill()
{
}

void MapTool::cameraControl()
{
}

void MapTool::numberInput()
{
}






