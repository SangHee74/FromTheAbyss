#include "stdafx.h"
#include "MapTool.h"

HRESULT MapTool::init(void)
{
	// �⺻ �������� 1-1
	_curAbyss = 1;
	_curStage = 1;

	// Ÿ�� ���
	createTileMap(TILEMAX_X, TILEMAX_Y);
	createSampleTile();

	_pickingPt = { 0,0 };
	_brushOn = _dragMode = false;
	_sampleTileOn = false;
	_guideOn = false;
	_tempTileOn = false;

	// info ��ư ��ġ
	_miniMap = RectMake(RSCENTER_X+10, 10, 290, 190);
	_selectTile = RectMake(1164, 276, 106,106);
	_plusButton[ABYSSRC] = RectMake(1220, 418, 50, 50);
	_plusButton[STAGERC] = RectMake(1220, 480, 50, 50);
	_minusButton[ABYSSRC] = RectMake(1160, 418, 50, 50);
	_minusButton[STAGERC] = RectMake(1160, 480, 50, 50);
	_tileViewButton = RectMake(RSCENTER_X + 10, 590,100,50);
	_wallOnButton = RectMake(RSCENTER_X + 100 + 14 , 590, 100, 50);
	_fillAllTile = RectMake(RSCENTER_X + 200 + 18, 590, 100, 50);
	_save = RectMake(RSCENTER_X + 10, 650, 100, 50);
	_load = RectMake(RSCENTER_X + 100 + 14, 650, 100, 50);
	_undo = RectMake(RSCENTER_X + 200 + 18, 650, 100, 50);
	_tileSlot = RectMake(-50, -50, TILESIZE_X, TILESIZE_Y);

	// ���� Ÿ�� ���� 
	_tilePos.x = 0;
	_tilePos.y = 0;

	// ������ ������ Ÿ�� �ʱ�ȭ
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
	if (KEYOKD(VK_F2))  _guideOn = true; 
	if (KEYOKD(VK_F3))  _guideOn = false;

	// Ÿ�� �� ���콺��ġ üũ 
	ptInTileCheck();

	// ���� ���
	if (KEYSKD(VK_LBUTTON))
	{
		selectSampleTile();
		selectTile();
		infoUpdate();
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

void MapTool::createTileMap(int tileX, int tileY)
{
	for (int i = 0; i < tileY; i++)
	{
		for (int j = 0; j < tileX; j++)
		{
			_tile[i * tileX + j ].pos.x = j;
			_tile[i * tileX + j ].pos.y = i;
			_tile[i * tileX + j ].fX = 0;	
			_tile[i * tileX + j ].fY = 0; 
			_tile[i * tileX + j].ptInRect = false;
			_tile[i * tileX + j]._moveCheck = GROUND;
			_tile[i * tileX + j]._abyssType = NONE;

			_tile[i * tileX + j].rc=
				RectMake( 0+ (j * TILESIZE_X), 0 + (i * TILESIZE_Y), TILESIZE_X, TILESIZE_Y);
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
				RectMake( 380 + (j*TILESIZE_Y), 10 + (i*TILESIZE_Y), TILESIZE_Y, TILESIZE_Y);
		}
	}
}

#pragma endregion

#pragma region TileMap update Method

void MapTool::selectTile()
{
 
	for (int i = 0; i < TILEMAX_X*TILEMAX_Y; i++)
	{
		//�ٴ�Ÿ�� Ȯ��
		if (PtInRect(&_tile[i].rc, _ptMouse) && !_inSampleTile )
		{

			_tile[i].fX = _tempTile.x;
			_tile[i].fY = _tempTile.y;
			_tile[i]._abyssType = _tempTile.abyssType;

			if (_wallOn) _tile[i]._moveCheck = GROUND;
			else _tile[i]._moveCheck = WALL;



		}
	}
	
}

void MapTool::selectSampleTile()
{
	for (int i = 0; i < SAMPLEMAX_X*SAMPLEMAX_Y; ++i)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse) && _sampleTileOn)
		{
			_tempTile.abyssType = static_cast<abyssType>(_curAbyss);
			_tempTile.x = _sampleTile[i].frameX;
			_tempTile.y = _sampleTile[i].frameY;

			// info���� ����Ÿ�� Ȯ��
			_tileSlot.left = _sampleTile[i].rc.left;
			_tileSlot.top = _sampleTile[i].rc.top;
		}
		
	}
}

void MapTool::infoUpdate()
{

		if (PtInRect(&_plusButton[ABYSSRC], _ptMouse))
		{
			if (_curAbyss <= 8) _curAbyss++;
		}
		if (PtInRect(&_minusButton[ABYSSRC], _ptMouse))
		{
			if (_curAbyss > 1) _curAbyss--;
		}
		if (PtInRect(&_plusButton[STAGERC], _ptMouse))
		{
			if (_curStage <= 3) _curStage++;
		}
		if (PtInRect(&_minusButton[STAGERC], _ptMouse))
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

void MapTool::tileRender()
{
	for (int i = 0; i < TILEMAX_X*TILEMAX_Y; ++i)
	{
		// �ٴ� Ÿ�� ����
		rcMake(getMemDC(), _tile[i].rc);

		// ��� Ÿ�� ������ �ǳʶٱ�
		if (_tile[i]._abyssType == NONE) continue;
		if (_tile[i]._abyssType == ABYSS1)
		{
			IMGFR("abyss_tile1", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS2)
		{
			IMGFR("abyss_tile2", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS3)
		{
			IMGFR("abyss_tile3", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS4)
		{
			IMGFR("abyss_tile4", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS5)
		{
			IMGFR("abyss_tile5", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS6)
		{
			IMGFR("abyss_tile6", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS7)
		{
			IMGFR("abyss_tile7", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
		}
		else if (_tile[i]._abyssType == ABYSS8)
		{
			IMGFR("abyss_tile8", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);
		}
		else IMGFR("abyss_tile9", getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].fX, _tile[i].fY);

	}

	for (int i = 0; i < TILEMAX_X*TILEMAX_Y; ++i)
	{
		// �ٴ� Ÿ�� �� ���콺�� ��ġ�� Ÿ��
		if (_tile[i].ptInRect) IMGR("tileS", getMemDC(), _tile[i].rc.left, _tile[i].rc.top);
		else continue;
	}

}

void MapTool::imageRender()
{
	
	//�� Ÿ�� ǥ��
	if (_tile[0]._moveCheck == WALL)
	{

	};

		

}

void MapTool::infoRender()
{
	IMGR("mbg", getMemDC(), RSCENTER_X, 0);
	rcMake(getMemDC(), _miniMap); // �̴ϸ� 
	rcMake(getMemDC(), _selectTile); // ���� ������ Ÿ�� ũ�� ���� 

	char str[512];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	// ���콺 ��ǥ -> ���߿� ī�޶� ��ǥ �ݿ��Ȱɷ� ����
	sprintf_s(str, "ptMouse X : %d , Y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), RSCENTER_X + 10, 210, str, strlen(str));

	sprintf_s(str, "���̽� Ÿ�� ��ġ");
	TextOut(getMemDC(), RSCENTER_X + 10, 240, str, strlen(str));
	sprintf_s(str, "tile X : %d , Y : %d", _tilePos.x, _tilePos.y);
	TextOut(getMemDC(), RSCENTER_X + 10, 260, str, strlen(str));

	sprintf_s(str, "���� ��� : %d ", _curAbyss);
	TextOut(getMemDC(), RSCENTER_X + 10, 418, str, strlen(str));
	sprintf_s(str, "���� �������� : %d ", _curStage);
	TextOut(getMemDC(), RSCENTER_X + 10, 480, str, strlen(str));

#pragma region ������ư ��ġ
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
	IMGR("tileSetB", getMemDC(), _tileViewButton.left, _tileViewButton.top);
	IMGR("wallB", getMemDC(), _wallOnButton.left, _wallOnButton.top);
	IMGR("fillB", getMemDC(), _fillAllTile.left, _fillAllTile.top);
	IMGR("saveB", getMemDC(), _save.left, _save.top);
	IMGR("loadB", getMemDC(), _load.left, _load.top);
	IMGR("undoB", getMemDC(), _undo.left, _undo.top);

#pragma endregion

	// Ÿ�ϼ¿��� ���° Ÿ���� ����������
	sampleTileRender();

}

void MapTool::sampleTileRender()
{
	// ���� Ÿ�ϼ� 
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

		// ����Ÿ�ϼ� �� ����Ÿ�� ��ġ ���� �׵θ� ǥ�� 
		IMGR("tileS", getMemDC(), _tileSlot.left, _tileSlot.top);
	}

	// F2 ���̵� On
	if (_guideOn)
	{
		// ���� Ÿ�ϼ� �̹����� ���������� 
		if (_sampleTileOn)
		{
			for (int i = 0; i < SAMPLEMAX_Y; i++)
			{
				for (int j = 0; j < SAMPLEMAX_X; j++)
				{
					// ����Ÿ�ϼ��� rc��ġ Ȯ�ο�
					rcMake(getMemDC(), _sampleTile[i * SAMPLEMAX_X + j].rc);
				}
			}
		}
	}

	// �������� ���õ� ���� Ÿ�ϼ� ũ�� ����
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

	_selectTileView->frameRender(getMemDC(), _selectTile.left + 1, _selectTile.top + 1,
		_tempTile.x, _tempTile.y);

}

#pragma endregion

#pragma region TileMap function
void MapTool::ptInTileCheck()
{
	// ���� ���̽� Ÿ�� üũ 
	for (int i = 0; i < TILEMAX_X * TILEMAX_Y; ++i)
	{
		if (PtInRect(&_tile[i].rc,_ptMouse))
		{
			_tile[i].ptInRect = true;
		}
		else _tile[i].ptInRect = false;

		if (_tile[i].ptInRect)
		{
			_tilePos.x = _tile[i].pos.x;
			_tilePos.y = _tile[i].pos.y;
		}
		else continue;
	}

	// ���� ���� Ÿ�� üũ 
	RECT sampleTileRect;
	sampleTileRect = RectMake(380, 10, 
		IMG("abyss_tile11")->getWidth(), IMG("abyss_tile11")->getHeight());

	if (PtInRect(&sampleTileRect, _ptMouse)) _inSampleTile = true;
	else _inSampleTile = false;
	
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
				file = CreateFile("1-1.txt", GENERIC_WRITE, NULL, NULL,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				
				WriteFile(file, _tile, sizeof(_tile) * TILEMAX_X * TILEMAX_Y, &write, NULL);
				CloseHandle(file);
				cout <<  "1-1 ���� ���� Ŭ�� " <<endl;
			}
		}
	}

	
}

void MapTool::load()
{
	if (PtInRect(&_save, _ptMouse))
	{
		HANDLE file;
		DWORD read;

		if (_curAbyss == 1)
		{
			if (_curStage == 1)
			{
				file = CreateFile("1-1.txt", GENERIC_WRITE, NULL, NULL,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

				WriteFile(file, _tile, sizeof(_tile) * TILEMAX_X * TILEMAX_Y, &read, NULL);
				CloseHandle(file);
				cout << "1-1 ���� ���� Ŭ�� " << endl;
			}
		}
	}
}

#pragma endregion


