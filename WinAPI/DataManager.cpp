#include "Stdafx.h"
#include "DataManager.h"

// 플레이어 데이터 를 먼저 받아서 숫자를 뿌려야 하나 
HRESULT DataManager::init(PLAYERNUMBER playerNum)
{
	switch (playerNum)
	{
	case PLAYERNUMBER::PLAYER_ONE:
		// 파일입출력. 파일이 있으면 파일읽어오기
		// 파일없으면 기본값으로 새로 시작하기 
		//DATAMANAGER->getPlayer()->init();
		break;

	case PLAYERNUMBER::PLAYER_TWO:
		break;

	case PLAYERNUMBER::PLAYER_THREE:
		break;

	}



	//_pixelMap = IMG("map_stage1_pixel");



	return S_OK;
}

HRESULT DataManager::init(void)
{

	//_mapData.enterAbyssInfo.abyss = 0;
	//_mapData.enterAbyssInfo.stage = 0;
	_mapData.enterAbyssInfo.abyss = 1; // 임시
	_mapData.enterAbyssInfo.stage = 1; // 임시

	
	_player = new Player(); // 플레이어 객체 생성 
	_player->init();



	return S_OK;
}

void DataManager::release(void)
{

	_player->release();
	SAFE_DELETE(_player);
}

void DataManager::update(void)
{
}

void DataManager::render(void)
{
}

void DataManager::setStageSetting(void)
{
	int settingAbyss = _mapData.enterAbyssInfo.abyss;
	int settingStage = _mapData.enterAbyssInfo.stage;

	switch (settingAbyss)
	{
		// 세팅할 데이터 초기화
		_mapData.map = nullptr;
		_mapData.mapObject = nullptr;
		_mapData.mapTop = nullptr;
		_mapData.pixelMap = nullptr;
		for (int i = 0; i < GATE_END; i++)
		{
			_mapData.gate.rc[i] = RectMakeCenter(-200, -200, 100, 50);
		}

		// 어비스-스테이지(index범위)
		// ex :  11(0~19)  12(20~39)   13(40~59)   14(60~79)
		//		 21(80~99) 22(100~119) 23(120~139) 24(140~159)
	case 1:
		if (settingStage == 1)
		{
			// 스테이지의 맵 정보 세팅
			_mapData.map		 = IMG("map_stage1");
			_mapData.mapObject  = IMG("map_stage1");
			_mapData.mapTop	 = IMG("map_stage1_top");
			_mapData.pixelMap	 = IMG("map_stage1_pixel");

			_mapData.gate.rc[GATE_HOME] =
				RectMake(25,328,IMG("map_gate")->getWidth(), IMG("map_gate")->getHeight());
			_mapData.gate.rc[GATE_NEXTSTAGE] =
				RectMake(2110, 660, IMG("map_gate")->getWidth(), IMG("map_gate")->getHeight());

			// 플레이어 정보 세팅
			_player->playerInStageSetting(50, 300, PLAYERDIRECTION::RIGHTDOWN);
 
		}
		if (settingStage == 2)
		{
			cout << "어비스1 - 스테이지2" << endl;
		}

		break;
	}


}


