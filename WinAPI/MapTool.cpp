#include "stdafx.h"
#include "MapTool.h"

HRESULT MapTool::init(void)
{
	_curAbyss =	_curStage = 1;
	createTileMap(TILEMAX_X, TILEMAX_Y);
	_pickingPt = { 0,0 };
	_brushOn = _menuInpt = _dragMode = false;
	_curAbyss = _curStage = 0;


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
}

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



