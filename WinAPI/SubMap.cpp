#include "Stdafx.h"
#include "SubMap.h"

HRESULT SubMap::init(void)
{
	_settingAbyss = DATAMANAGER->getMapData().enterAbyssInfo.abyss;
	_settingStage = DATAMANAGER->getMapData().enterAbyssInfo.stage;
	_abyssThumbnail = IMG("map_thumbnail");
	_abyssNum = IMG("Num_UI2");
	_StageNum = IMG("Num_UI2");
	_mapMaxWidth =0;
	_mapMaxHeight = 0;
	_mapIndexX = 0;
	_mapIndexY = 0;

	for (int i = 0; i < 4; i++)
	{
		_mapRangeX[i] = 0;
		_mapRangeY[i] = 0;
	}

	for(int i = 0; i < 16 ; i++)
	{
		// 미니맵 그려줄 타일 위치 추가하기 .
		_pathNavigation.miniMapTile[i] ;
		_pathNavigation.miniMap[i] = IMG("map_path");
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

}

void SubMap::minimapCheck()
{
	switch (_settingAbyss)
	{
	case 1: // 초원의 심연
		if (_settingStage == 1)
		{
			_mapMaxWidth = IMG("map_stage1")->getWidth();
			_mapMaxHeight = IMG("map_stage1")->getHeight();
			
			for(int i = 0; i<4 ; i++)
			{
			_mapRangeX[i] = _mapMaxWidth  * (0.25 * (i+1)) ;
			_mapRangeY[i] = _mapMaxHeight * (0.25 * (i+1)) ;
			}


			if ( DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[0] )
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[0]) _nimiMapOpen.set(0);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[4]) _nimiMapOpen.set(4);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[8]) _nimiMapOpen.set(8);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[12]) _nimiMapOpen.set(12);
			}
			if ( DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[0] 
				&& DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[1]
				)
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[1]) _nimiMapOpen.set(1);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[5]) _nimiMapOpen.set(5);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[9]) _nimiMapOpen.set(9);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[13]) _nimiMapOpen.set(13);
			}
			if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[1]
				&& DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[2]
				)
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[2]) _nimiMapOpen.set(2);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[6]) _nimiMapOpen.set(6);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[10]) _nimiMapOpen.set(10);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[14]) _nimiMapOpen.set(14);
			}
			if (DATAMANAGER->getPlayer()->getPlayer().movePosX > _mapRangeX[2]
				&& DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeX[3]
				)
			{
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[3]) _nimiMapOpen.set(3);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[7]) _nimiMapOpen.set(7);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[11]) _nimiMapOpen.set(11);
				if (DATAMANAGER->getPlayer()->getPlayer().movePosX < _mapRangeY[15]) _nimiMapOpen.set(15);
			}


		}
		if (_settingStage == 2)
		{

		}
		if (_settingStage == 3)
		{

		}
		if (_settingStage == 4)
		{

		}
		break;
	}
}

void SubMap::minimapRender()
{
}


