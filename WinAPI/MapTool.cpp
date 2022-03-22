#include "stdafx.h"
#include "MapTool.h"

HRESULT MapTool::init(void)
{
	_curAbyss =	_curStage = 1;
	createTileMap(TILEMAX_X, TILEMAX_Y);
	_pickingPt = { 0,0 };
	_brushOn = _dragMode = false;


	return S_OK;
}

void MapTool::release(void)
{
}

void MapTool::update(void)
{

	

}

void MapTool::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	//IMGR("mbg", getMemDC(), 960, 0);
	imageRender();



	char str[256];

	// 타일셋에서 몇번째 타일을 선택중인지
	sprintf_s(str, "TempTile X : %d , Y : %d", _tempTile.x, _tempTile.y);
	TextOut(getMemDC(), CENTER_X, 70, str, strlen(str));

	for (int i = 0; i < TILEMAX_X * TILEMAX_Y; ++i)
	{
		sprintf_s(str, "%d, %d", _tile[i].nX, _tile[i].nY);
	}

	// 마우스 좌표 
	sprintf_s(str, "ptMouse X : %d , Y : %d", _cameraPtMouse.x, _cameraPtMouse.y);
	TextOut(getMemDC(), CENTER_X + 150, 70 + 70, str, strlen(str));

	//일단 구현은 됬는데 드래그 표시를 어떻게해야하나... 고민중
	//if (_push && _dragMode) Rectangle(getMemDC(), _dragRc);

}

#pragma region TileMap Method
void MapTool::createTileMap(int tileX, int tileY)
{
	for (int i = 0; i < tileY; i++)
	{
		for (int j = 0; j < tileX; j++)
		{
			_tile[i * tileX + j ].fX = 0; 
			_tile[i * tileX + j ].fY = 0; 
			_tile[i * tileX + j ].nX = j; 
			_tile[i * tileX + j ].nY = i;

			_tile[i * tileX + j].inTile = false;
			_tile[i * tileX + j].moveCheck = GROUND;
		}
	}

}

void MapTool::createTile()
{
}

void MapTool::tileInit()
{
}

void MapTool::tileRender()
{
}

void MapTool::openCloseBrush()
{
}

void MapTool::menuInpt()
{
}

void MapTool::dragPaint()
{
}

void MapTool::tempDrag()
{
}

void MapTool::dragOnOff()
{
}

#pragma endregion

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
				file = CreateFile("1-1.map", GENERIC_WRITE, NULL, NULL,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

				WriteFile(file, _tile, sizeof(_tile) * TILEMAX_X * TILEMAX_Y, &write, NULL);
				CloseHandle(file);
			}
		}
	}

	
}

void MapTool::load()
{
}

void MapTool::imageRender()
{
	IMGR("mbg", getMemDC(),960,0);

	if (_curAbyss == 1) 
	{
	//	IMGR("abyss_tile1", getMemDC(), 450, 50);

	}
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



