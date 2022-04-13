#include "Stdafx.h"
#include "SubMap.h"

HRESULT SubMap::init(void)
{
	_settingAbyss = DATAMANAGER->getMapData().enterAbyssInfo.abyss;
	_settingStage = DATAMANAGER->getMapData().enterAbyssInfo.stage;
	_abyssThumbnail = IMG("map_thumbnail");
	_abyssNum = IMG("Num_UI2");
	_StageNum = IMG("Num_UI2");
	
	
	// minimap
	_mapMaxWidth =0;
	_mapMaxHeight = 0;
	_mapIndexX = 0;
	_mapIndexY = 0;
	_returnImg = IMG("map_point");			// frameX : 0 
	_nextImg = IMG("map_point");			// frameX : 1 
	_playerPositionImg = IMG("map_point");	// frameX : 2
	_returnNum = 0;
	_nextNum = 0;
	_curIndex = 0;

	for (int i = 0; i < 4; i++)
	{
		_mapRangeX[i] = 0;  		_mapRangeY[i] = 0;
	}


	for(int i = 0; i < 10 ; i++)
	{
		for (int j = 0; j <10 ; j++)
		{
		tagMiniMapImg data;

		// 미니맵 그려줄 타일 위치 추가하기 .
		data.miniMapTile = RectMake(640 + 328 + (25 * j),100 + (25 * i), 25, 25);
		data.miniMapPath = IMG("map_path");
		data.OnMiniMapTile.reset(0);
		data.pathFrameX = 0;

		_vMiniMap.push_back(data);
		}
	}
	return S_OK;
}

void SubMap::release(void)
{
}

void SubMap::update(void)
{
	minimapCheck();
}

void SubMap::render(void)
{
	FONTMANAGER->drawText(getMemDC(), CENTER_X + 85, 115, "둥근모꼴", 24, FW_EXTRABOLD,
		_abyssName[_settingAbyss].text, wcslen(_abyssName[_settingAbyss].text), RGB(0,0,0));

	_abyssThumbnail->frameRender(getMemDC(), CENTER_X + 76, 146, _settingAbyss-1, 0);
	IMGR("map_abyss",getMemDC(),CENTER_X+ 96, 326);
	IMGR("map_stage",getMemDC(),CENTER_X+ 96, 366);
	_abyssNum->frameRender(getMemDC(), CENTER_X + 196, 327, _settingAbyss, 0);
	_StageNum->frameRender(getMemDC(), CENTER_X + 196, 367, _settingStage, 0);


	// path render
	_viMiniMap = _vMiniMap.begin();
	for (; _viMiniMap != _vMiniMap.end(); _viMiniMap++)
	{
		if (_viMiniMap->OnMiniMapTile.test(0))
		{
			_viMiniMap->miniMapPath->frameRender(getMemDC(),
			_viMiniMap->miniMapTile.left, _viMiniMap->miniMapTile.top,
			_viMiniMap->pathFrameX, 0);
		}
		else continue;
	}


	if (_vMiniMap[_returnNum].OnMiniMapTile.test(0))
	{
		_returnImg->frameRender(getMemDC(), 
			_vMiniMap[_returnNum].miniMapTile.left, _vMiniMap[_returnNum].miniMapTile.top,
			1, 0);
	}
	if (_vMiniMap[_nextNum].OnMiniMapTile.test(0))
	{
		_returnImg->frameRender(getMemDC(),
			_vMiniMap[_nextNum].miniMapTile.left, _vMiniMap[_nextNum].miniMapTile.top,
			0, 0);
	}
	_playerPositionImg->frameRender(getMemDC(),
		_vMiniMap[_curIndex].miniMapTile.left, _vMiniMap[_curIndex].miniMapTile.top,
		2, 0);



}

void SubMap::minimapCheck()
{
	switch (_settingAbyss)
	{
	case 1: // 초원의 심연

		if (_settingStage == 1)
		{
			_vMiniMap[33].OnMiniMapTile.set(0);
			_vMiniMap[33].pathFrameX = 2;
			// 1-1 return Point
			_returnNum = 33;
			_curIndex = 33;

		}	// 스테이지 1 미니맵 정보 
			/*
			_mapMaxWidth = IMG("map_stage1")->getWidth();
			_mapMaxHeight = IMG("map_stage1")->getHeight();

			for (int i = 0; i < 4; i++)
			{
				_mapRangeX[i] = _mapMaxWidth * (0.25 * (i + 1));
				_mapRangeY[i] = _mapMaxHeight * (0.25 * (i + 1));
			}
			if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[0])
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[0])
				{
					_vMiniMap[33].OnMiniMapTile.set(0);
					_vMiniMap[33].pathFrameX = 2;
					// 1-1 return Point
					_returnNum = 33;
					_curIndex = 33;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[4])
				{
					_vMiniMap[43].OnMiniMapTile.set(1);
					_vMiniMap[43].pathFrameX = 15;
					_curIndex = 43;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[8])
				{
					_vMiniMap[53].OnMiniMapTile.set(1);
					_vMiniMap[53].pathFrameX = 15;
					_curIndex = 53;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[12])
				{
					//_vMiniMap[63].OnMiniMapTile.set(1);
					//_vMiniMap[63].pathFrameX = 8;
					//_curIndex = 63;
				}
			}
			if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[0]
				&& DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[1]
				)
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[1])
				{
					_vMiniMap[34].OnMiniMapTile.set(1);
					_vMiniMap[34].pathFrameX = 2;
					_curIndex = 34;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[5])
				{
					_vMiniMap[44].OnMiniMapTile.set(1);
					_vMiniMap[44].pathFrameX = 16;
					_curIndex = 44;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[9])
				{
					_vMiniMap[54].OnMiniMapTile.set(1);
					_vMiniMap[54].pathFrameX = 16;
					_curIndex = 54;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[13])
				{
					_vMiniMap[64].OnMiniMapTile.set(1);
					_vMiniMap[64].pathFrameX = 12;
					_curIndex = 64;
				}
			}
			if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[1]
				&& DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[2]
				)
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[2])
				{
					_vMiniMap[35].OnMiniMapTile.set(1);
					_vMiniMap[35].pathFrameX = 9;
					_curIndex = 35;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[6])
				{
					_vMiniMap[45].OnMiniMapTile.set(1);
					_vMiniMap[45].pathFrameX = 9;
					_curIndex = 45;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[10])
				{
					_vMiniMap[55].OnMiniMapTile.set(1);
					_vMiniMap[55].pathFrameX = 10;
					_curIndex = 55;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[14])
				{
					_vMiniMap[65].OnMiniMapTile.set(1);
					_vMiniMap[65].pathFrameX = 7;
					_curIndex = 65;
				}
			}
			if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[2]
				&& DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[3]
				)
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[3])
				{
					_vMiniMap[36].OnMiniMapTile.set(1);
					_vMiniMap[36].pathFrameX = 9;
					// 1-1 next Point
					_nextNum = 36;
					_curIndex = 36;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[7])
				{
					_vMiniMap[46].OnMiniMapTile.set(1);
					_vMiniMap[46].pathFrameX = 5;
					_curIndex = 46;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[11])
				{
					_vMiniMap[56].OnMiniMapTile.set(1);
					_vMiniMap[56].pathFrameX = 6;
					_curIndex = 56;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[15])
				{
					_vMiniMap[66].OnMiniMapTile.set(1);
					_vMiniMap[66].pathFrameX = 12;
					_curIndex = 66;
				}
			}
		}*/
		if (_settingStage == 2)
		{

		}
		if (_settingStage == 3)
		{

		}
		if (_settingStage == 4)
		{
			_vMiniMap[44].OnMiniMapTile.set(0);
			_vMiniMap[44].pathFrameX = 0;
			// 1-4 return Point
			_returnNum = 0;
			_curIndex = 44;
		}
		break;
	}
}



