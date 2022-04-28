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
	_curPathFrameX = 0;

	for (int i = 0; i < 4; i++)
	{
		_mapRangeX[i] = 0;  		_mapRangeY[i] = 0;
	}


	for(int i = 0; i < 10 ; i++)
	{
		for (int j = 0; j < 10 ; j++)
		{
		tagMiniMapImg data;

		// 미니맵 그려줄 타일 위치 추가하기 .
		data.miniMapTile = RectMake(640 + 328 + (25 * j),100 + (25 * i), 25, 25);
		data.miniMapPath = IMG("map_path");
		data.OnMiniMapTile = false;
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

	if (_settingStage == 4) _settingStage = 2; // 임시 수정
	_StageNum->frameRender(getMemDC(), CENTER_X + 196, 367, _settingStage, 0);


	// path render
	_viMiniMap = _vMiniMap.begin();
	for (; _viMiniMap != _vMiniMap.end(); _viMiniMap++)
	{
		if (_viMiniMap->OnMiniMapTile)
		{
			_viMiniMap->miniMapPath->frameRender(getMemDC(),
			_viMiniMap->miniMapTile.left, _viMiniMap->miniMapTile.top,
			_viMiniMap->pathFrameX, 0);
		}
		else continue;
	}


	if (_vMiniMap[_returnNum].OnMiniMapTile)
	{
		_returnImg->frameRender(getMemDC(), 
			_vMiniMap[_returnNum].miniMapTile.left, _vMiniMap[_returnNum].miniMapTile.top,
			1, 0);
	}
	if (_vMiniMap[_nextNum].OnMiniMapTile)
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
			// 스테이지 1 미니맵 정보 
			_mapMaxWidth = IMG("map_stage11")->getWidth();
			_mapMaxHeight = IMG("map_stage11")->getHeight();

			for (int i = 0; i < 4 ; i++) // 가로 세로 각 4칸 총 16 범위
			{
				_mapRangeX[i] = _mapMaxWidth * (0.25 * (i + 1)); 
				_mapRangeY[i] = _mapMaxHeight * (0.25 * (i + 1)); 
			}

			if (DATAMANAGER->getPlayer()->getPlayer().movePosY < _mapRangeY[0])
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[0])
				{
					_vMiniMap[33].OnMiniMapTile = true;
					_vMiniMap[33].pathFrameX = _curPathFrameX = 2;
					// 1-1 return Point
					_curIndex =  33;
					_returnNum = 33;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[0] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[1])
				{
					_vMiniMap[34].OnMiniMapTile = true;
					_vMiniMap[34].pathFrameX = _curPathFrameX = 2;

					_curIndex = 34;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[1] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[2])
				{
					_vMiniMap[35].OnMiniMapTile = true;
					_vMiniMap[35].pathFrameX = _curPathFrameX = 4 ;
					// 1-3 next Point
					_curIndex = 35;	
					_nextNum = 35;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[2] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[3])
				{
					_vMiniMap[36].OnMiniMapTile = true;
					_vMiniMap[36].pathFrameX = _curPathFrameX = 8;

					_curIndex = 36;
				}
			}

			if (DATAMANAGER->getPlayer()->getPlayer().movePosY > _mapRangeY[0] 
				&& DATAMANAGER->getPlayer()->getPlayer().movePosY < _mapRangeY[1])
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[0])
				{
					_vMiniMap[43].OnMiniMapTile = true;
					_vMiniMap[43].pathFrameX = _curPathFrameX = 14;

					_curIndex = 43;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[0] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[1])
				{
					_vMiniMap[44].OnMiniMapTile = true;
					_vMiniMap[44].pathFrameX = _curPathFrameX = 15;

					_curIndex = 44;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[1] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[2])
				{
					_vMiniMap[45].OnMiniMapTile = true;
					_vMiniMap[45].pathFrameX = _curPathFrameX = 8;

					_curIndex = 45;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[2] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[3])
				{
					_vMiniMap[46].OnMiniMapTile = true;
					_vMiniMap[46].pathFrameX = _curPathFrameX = 5;

					_curIndex = 46;
				}
			}

			if (DATAMANAGER->getPlayer()->getPlayer().movePosY > _mapRangeY[1]
				&& DATAMANAGER->getPlayer()->getPlayer().movePosY < _mapRangeY[2])
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[0])
				{
					_vMiniMap[53].OnMiniMapTile = true;
					_vMiniMap[53].pathFrameX = _curPathFrameX = 14;

					_curIndex = 53;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[0] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[1])
				{
					_vMiniMap[54].OnMiniMapTile = true;
					_vMiniMap[54].pathFrameX = _curPathFrameX = 15;

					_curIndex = 54;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[1] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[2])
				{
					_vMiniMap[55].OnMiniMapTile = true;
					_vMiniMap[55].pathFrameX = _curPathFrameX = 9;

					_curIndex = 55;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[2] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[3])
				{
					_vMiniMap[56].OnMiniMapTile = true;
					_vMiniMap[56].pathFrameX = _curPathFrameX = 5;

					_curIndex = 56;
				}
			}

			if (DATAMANAGER->getPlayer()->getPlayer().movePosY > _mapRangeY[2]
				&& DATAMANAGER->getPlayer()->getPlayer().movePosY < _mapRangeY[3])
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[0])
				{
					_vMiniMap[63].OnMiniMapTile = true;
					_vMiniMap[63].pathFrameX = _curPathFrameX = 7;

					_curIndex = 63;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[0] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[1])
				{
					_vMiniMap[64].OnMiniMapTile = true;
					_vMiniMap[64].pathFrameX = _curPathFrameX = 11;

					_curIndex = 64;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[1] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[2])
				{
					_vMiniMap[65].OnMiniMapTile = true;
					_vMiniMap[65].pathFrameX = _curPathFrameX = 6;

					_curIndex = 65;
				}
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[2] && DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[3])
				{
					_vMiniMap[66].OnMiniMapTile = true;
					_vMiniMap[66].pathFrameX = _curPathFrameX = 9;

					_curIndex = 66;
				}
			}

		}
	//====================================================================================
		if (_settingStage == 4)
		{
			_vMiniMap[44].OnMiniMapTile = true;
			_vMiniMap[44].pathFrameX = _curPathFrameX =  0;
			// 1-4 return Point
			_returnNum = 0;
			_curIndex = 44;
		}
		break;
	}
}



