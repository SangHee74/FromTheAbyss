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
	_mapData.enterAbyssInfo.stage =4; // �ӽ�

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

	//_player->release();
	//SAFE_DELETE(_player);
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
	int gateInRcWidth = 60;
	int gateInRcHeight = 20;

	switch (settingAbyss)
	{
		for (int i = 0; i < GATE_END; i++)
		{
			_mapData.gate.drawRc[i] = RectMakeCenter(-200, -200, 120, 50);
			_mapData.gate.inRc[i]	= RectMakeCenter(-200, -200, gateInRcWidth, gateInRcHeight);
		}
	case 1:
		if (settingStage == 1)
		{
			// ���������� �� ���� ����
			_mapData.map		 = IMG("map_stage11");
			//_mapData.mapObject   = IMG("map_stage1");
			_mapData.mapTop	     = IMG("map_stage11_top");
			_mapData.pixelMap	 = IMG("map_stage11_pixel");
			_mapData.gate.drawRc[GATE_HOME] = RectMakeCenter(75, 353, 120, 50);
			_mapData.gate.inRc[GATE_HOME] = RectMakeCenter(75, 353, gateInRcWidth, gateInRcHeight);
			_mapData.gate.drawRc[GATE_NEXTSTAGE] = RectMakeCenter(2160,685, 120, 50);
			_mapData.gate.inRc[GATE_NEXTSTAGE] = RectMakeCenter(2160,685, gateInRcWidth, gateInRcHeight);

			// �÷��̾� ���� ����
			//_player->playerInStageSetting(162, 330, PLAYERDIRECTION::RIGHTDOWN);

			// ������ �׽�Ʈ ��
			_player->playerInStageSetting(2436,867, PLAYERDIRECTION::LEFTUP);
 
		}
		if (settingStage == 4)
		{
			_mapData.map = IMG("map_stage14");
			_mapData.pixelMap = IMG("map_stage14_pixel");
			_mapData.gate.drawRc[GATE_HOME] = RectMakeCenter(75, 353, 120, 50);
			_mapData.gate.inRc[GATE_HOME] = RectMakeCenter(75, 353, gateInRcWidth, gateInRcHeight);

			// �÷��̾� ���� ����
			//_player->playerInStageSetting(_mapData.map->getWidth()*0.5, _mapData.map->getHeight()-400, PLAYERDIRECTION::UP);
			_player->playerInStageSetting(_mapData.map->getWidth()*0.5, _mapData.map->getHeight()-1200, PLAYERDIRECTION::UP);
		}

		break;
	}


}


