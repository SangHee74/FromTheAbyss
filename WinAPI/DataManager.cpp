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

	return S_OK;
}

HRESULT DataManager::init(void)
{

	//_mapData.enterAbyssInfo.abyss = 0;
	//_mapData.enterAbyssInfo.stage = 0;
	_mapData.enterAbyssInfo.abyss = 1; // �ӽ�
	_mapData.enterAbyssInfo.stage = 1; // �ӽ�

	_mapData.map = nullptr;
	_mapData.mapObject = nullptr;
	_mapData.mapTop = nullptr;
	_mapData.pixelMap = nullptr;

	_mapData.gate.inGateCount = 0;
	
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
	int inRcWidth = 60;
	int inRcHeight = 20;

	switch (settingAbyss)
	{
		for (int i = 0; i < GATE_END; i++)
		{
			_mapData.gate.drawRc[i] = RectMakeCenter(-200, -200, 120, 50);
			_mapData.gate.inRc[i]	= RectMakeCenter(-200, -200, inRcWidth, inRcHeight);
		}
	case 1:
		if (settingStage == 1)
		{
			// ���������� �� ���� ����
			_mapData.map		 = IMG("map_stage1");
			_mapData.mapObject  = IMG("map_stage1");
			_mapData.mapTop	 = IMG("map_stage1_top");
			_mapData.pixelMap	 = IMG("map_stage1_pixel");
			_mapData.gate.drawRc[GATE_HOME] = RectMakeCenter(75, 353, 120, 50);
			_mapData.gate.inRc[GATE_HOME] = RectMakeCenter(75, 353, inRcWidth, inRcHeight);
			_mapData.gate.drawRc[GATE_NEXTSTAGE] = RectMakeCenter(2160,685, 120, 50);
			_mapData.gate.inRc[GATE_NEXTSTAGE] = RectMakeCenter(2160,685, inRcWidth, inRcHeight);

			// �÷��̾� ���� ����
			_player->playerInStageSetting(162, 330, PLAYERDIRECTION::RIGHTDOWN);
 
		}
		if (settingStage == 2)
		{
			cout << "���1 - ��������2 �̱������� ���� ������ ���ư��ϴ�" << endl;
			SCENEMANAGER->changeScene("main");
		}

		break;
	}


}


