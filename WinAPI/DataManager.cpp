#include "Stdafx.h"
#include "DataManager.h"

// �÷��̾� ������ �� ���� �޾Ƽ� ���ڸ� �ѷ��� �ϳ� 
HRESULT DataManager::init(PLAYERNUMBER playerNum)
{
	switch (playerNum)
	{
	case PLAYERNUMBER::PLAYER_ONE:
		// ���������. ������ ������ �����о����
		// ���Ͼ����� �⺻������ ���� �����ϱ� 
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
	_mapData.enterAbyssInfo.abyss = 1; // �ӽ�
	_mapData.enterAbyssInfo.stage = 1; // �ӽ�

	
	_player = new Player(); // �÷��̾� ��ü ���� 
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
		// ������ ������ �ʱ�ȭ
		_mapData.map = nullptr;
		_mapData.mapObject = nullptr;
		_mapData.mapTop = nullptr;
		_mapData.pixelMap = nullptr;
		for (int i = 0; i < GATE_END; i++)
		{
			_mapData.gate.rc[i] = RectMakeCenter(-200, -200, 100, 50);
		}

		// ���-��������(index����)
		// ex :  11(0~19)  12(20~39)   13(40~59)   14(60~79)
		//		 21(80~99) 22(100~119) 23(120~139) 24(140~159)
	case 1:
		if (settingStage == 1)
		{
			// ���������� �� ���� ����
			_mapData.map		 = IMG("map_stage1");
			_mapData.mapObject  = IMG("map_stage1");
			_mapData.mapTop	 = IMG("map_stage1_top");
			_mapData.pixelMap	 = IMG("map_stage1_pixel");

			_mapData.gate.rc[GATE_HOME] =
				RectMake(25,328,IMG("map_gate")->getWidth(), IMG("map_gate")->getHeight());
			_mapData.gate.rc[GATE_NEXTSTAGE] =
				RectMake(2110, 660, IMG("map_gate")->getWidth(), IMG("map_gate")->getHeight());

			// �÷��̾� ���� ����
			_player->playerInStageSetting(50, 300, PLAYERDIRECTION::RIGHTDOWN);
 
		}
		if (settingStage == 2)
		{
			cout << "���1 - ��������2" << endl;
		}

		break;
	}


}


