#include "Stdafx.h"
#include "Stage11.h"

HRESULT Stage11::init(void)
{
	// �������� ���� (��+�÷��̾� ����)
	DATAMANAGER->setStageSetting();

	_enemyM = new EnemyManager();
	_enemyM->init();

	_UIBar = new ProgressBar();
	_UIBar->init(DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);

	_subScreen = new SubMenu();
	_subScreen->init();

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, DATAMANAGER->getMapData().map->getWidth());
	CAM->setLimitsY(CENTER_Y, DATAMANAGER->getMapData().map->getHeight());

	_enterInfo.alpha = 255;
	_enterInfo.showTime = 0;


	return S_OK;
}

void Stage11::release(void)
{
	_UIBar->release();
	SAFE_DELETE(_UIBar);

	_subScreen->release();
	SAFE_DELETE(_subScreen);

	_enemyM->release();
	SAFE_DELETE(_enemyM);
}

void Stage11::update(void)
{
	enterInfoCheck();


	POINT cameraPos;
	cameraPos.x = DATAMANAGER->getPlayer()->getPlayer().movePosX;
	cameraPos.y = DATAMANAGER->getPlayer()->getPlayer().movePosY;
	CAM->setCameraPos(cameraPos);
	CAM->update();
	DATAMANAGER->getPlayer()->getPlayerCAM().rc = CAM->getScreenRect();

	DATAMANAGER->getPlayer()->update();

	_enemyM->update();

	_UIBar->setHpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxHp);
	_UIBar->setSpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curSp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);
	_UIBar->update();
	IMG("Num_UI")->setFrameX(11);
	IMG("Num_UI")->setFrameY(1);


	if (KEYOKD('7'))
	{
		cout << "����Ż��!" << endl;
		DATAMANAGER->getPlayer()->getPlayer().movePosX = 50;
		DATAMANAGER->getPlayer()->getPlayer().movePosY = 300;
	}

	_subScreen->update();


	// ������ ����Ȧ�� �̵�
	if (DATAMANAGER->getPlayer()->getState() == PLAYERSTATE::DEAD)
	{
		SCENEMANAGER->changeScene("main");
	}


	portalOn();
	collision();

}

void Stage11::render(void)
{
	int cameraLeft = CAM->getScreenRect().left;
	int cameraTop = CAM->getScreenRect().top;

	// ���
	DATAMANAGER->getMapData().map->render
	(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);

	// ��Ż
	IMGR("map_gate", getMemDC(),
		DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].left - cameraLeft,
		DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].top - cameraTop);
	IMGR("map_gate", getMemDC(),
		DATAMANAGER->getMapData().gate.drawRc[GATE_NEXTSTAGE].left - cameraLeft,
		DATAMANAGER->getMapData().gate.drawRc[GATE_NEXTSTAGE].top - cameraTop);

	//if()
	// ����
	_enemyM->render();

	// �÷��̾� 
	DATAMANAGER->getPlayer()->render();

	// ������Ʈ - ���� ���� Ȯ��
	//

	// ����Ʈ ���� 
	EFFECTMANAGER->render();

	// ��� ž
	DATAMANAGER->getMapData().mapTop->render(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);


	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		DATAMANAGER->getMapData().pixelMap->render
		(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);
	}

	// ����ȭ��(UI)
	_UIBar->render();
	_UIBar->renderHpSpNumImg(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().curSp,
		DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);
	//IMGR("UI_pathInfo", getMemDC(), LSCENTER_X-21, 10);

	_subScreen->render();

	Rectangle(getMemDC(),
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].left - cameraLeft,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].top - cameraTop,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].right - cameraLeft,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].bottom - cameraTop
	);

	IMGAR("map_abyss", getMemDC(), LSCENTER_X,CENTER_Y-10,_enterInfo.alpha);
	IMGFAR("Num_UI", getMemDC(), LSCENTER_X+70,CENTER_Y-10,DATAMANAGER->getMapData().enterAbyssInfo.stage,0,_enterInfo.alpha);
	IMGFAR("Num_UI", getMemDC(), LSCENTER_X+70,CENTER_Y-10,DATAMANAGER->getMapData().enterAbyssInfo.stage,0,_enterInfo.alpha);

}


void Stage11::enterInfoCheck()
{
	_enterInfo.showTime += TIMEMANAGER->getElapsedTime();
	if (_enterInfo.showTime > 0.6f)
	{
		_enterInfo.showTime = 0;
		_enterInfo.alpha -=2 ;
		if (_enterInfo.alpha <= 0) _enterInfo.alpha = 0;
	}
}

void Stage11::portalOn()
{
	RECT tempRc;
	RECT playerTempRc;
	playerTempRc = RectMakeCenter(
		DATAMANAGER->getPlayer()->getPlayer().movePosX,
		DATAMANAGER->getPlayer()->getPlayer().moveRc.bottom,
		40, 30);

	// ����Ȧ�� ���� ����Ʈ 
	if (IntersectRect(&tempRc, &DATAMANAGER->getMapData().gate.inRc[GATE_HOME], &playerTempRc))
	{
		DATAMANAGER->getMapData().gate.inGateCount++;
		cout << "������ ����Ʈ �ε� �� :" << DATAMANAGER->getMapData().gate.inGateCount << endl;
		if (DATAMANAGER->getMapData().gate.inGateCount > 90)
		{
			DATAMANAGER->getMapData().gate.inGateCount = 0;
			SCENEMANAGER->changeScene("main");
		}

	}
	else if (IntersectRect(&tempRc, &DATAMANAGER->getMapData().gate.inRc[GATE_NEXTSTAGE], &playerTempRc))
	{
		DATAMANAGER->getMapData().gate.inGateCount++;
		cout << "���� �������� ���� ����Ʈ �ε� �� :" << DATAMANAGER->getMapData().gate.inGateCount << endl;
		if (DATAMANAGER->getMapData().gate.inGateCount > 90)
		{
			DATAMANAGER->getMapData().gate.inGateCount = 0;
			// ���� ���������� ���� �������� ������Ʈ ���� �� 
			DATAMANAGER->getMapData().enterAbyssInfo.stage = 4;
			DATAMANAGER->getPlayer()->getPlayerAbyss().stage = 4;

			// ��ü���� stageChangeInit();
			SCENEMANAGER->changeScene("stage14");
		}

	}
	else DATAMANAGER->getMapData().gate.inGateCount = 0;
}

void Stage11::collision()
{
	RECT tempRc;
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// �÷��̾� ��������Ʈ -> ���� �ǰݹڽ�
		if (IntersectRect(&tempRc, &DATAMANAGER->getPlayer()->getPlayerCollisionRc().attRc,
			&_enemyM->getMonsters()[i]->getMonsterCollisionRc().defRc)
			&& ! (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEF))
		{

			// ���� �ǰݻ��·� ��ȯ + ü�°���
			_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::DEF;
			int temp = 0;
			temp = DATAMANAGER->getPlayer()->playerRandomDamage();
			cout << "�÷��̾� ������ : " << temp << endl;
			//EFFECTMANAGER->getPlayerEff().show(tempRc); //����Ʈ ������!!!!

			_enemyM->getMonsters()[i]->setHp(temp);
			cout << "���� ���� HP : " << _enemyM->getMonsters()[i]->getHp() << endl;;
			break;

		}
		// ���� ü���� ������ 
		if (_enemyM->getMonsters()[i]->getHp() <= 0)
		{
			// ���� ���� ����Ʈ ���, //����Ʈ ������!!!!
			//EFFECTMANAGER->getMonsterEff()->show(_enemyM->getMonsters()[i]->getMonster().moveRc);
			// ���� ������ �÷��̾ ����,

			// ���� 
			_enemyM->removeMonster(i);
		}

	}


	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// ���� ��������Ʈ -> �÷��̾� �ǰݹڽ�
		if (IntersectRect(&tempRc, &_enemyM->getMonsters()[i]->getMonsterCollisionRc().attRc,
			&DATAMANAGER->getPlayer()->getPlayerCollisionRc().defRc )
			&& ! (DATAMANAGER->getPlayer()->getState() == PLAYERSTATE::DEF))
		{
			// �÷��̾� �ǰݻ��·� ��ȯ + ü�°���
			DATAMANAGER->getPlayer()->getState() = PLAYERSTATE::DEF;

			// �÷��̾� ü�� ���� �Լ�
			int temp = 0;
			temp = _enemyM->monsterRandomDamage(i);
			cout << "������ ������ : " << temp << endl;


			DATAMANAGER->getPlayer()->getPlayerStatus().curHp -= temp;
			_UIBar->setHpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxHp);
			//EFFECTMANAGER->getPlayer()->show(tempRc);

			_enemyM->getMonsters()[i]->setHp(temp);
			cout << "�÷��̾� ���� HP : " << _enemyM->getMonsters()[i]->getHp() << endl;;
			break;
		}
	}
}
