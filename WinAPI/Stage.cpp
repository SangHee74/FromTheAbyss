#include "Stdafx.h"
#include "Stage.h"
#include "Abyss.h"

HRESULT Stage::init(void)
{
	// �������� ���� (��+�÷��̾� ����)
	DATAMANAGER->setStageSetting();
	
	_em = new EnemyManager();
	_em->init();

	_UIBar = new ProgressBar();
	_UIBar->init(DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);
	
	_playereEffect = new PlayerEffect();
	_playereEffect->init();

	_monsterEffect = new MosterEffect();
	_monsterEffect->init();

	_subScreen = new SubMenu();
	_subScreen->init();

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, DATAMANAGER->getMapData().map->getWidth());
	CAM->setLimitsY(CENTER_Y, DATAMANAGER->getMapData().map->getHeight());

	_alpha = 0;
	

	return S_OK;
}

HRESULT Stage::stageChangeInit(void)
{

	// �������� ���� (�� ����)
	DATAMANAGER->setStageSetting();

	return S_OK;
}

void Stage::release(void)
{

	_playereEffect->release();
	SAFE_DELETE(_playereEffect);

	_monsterEffect->release();
	SAFE_DELETE(_monsterEffect);

	_UIBar->release();
	SAFE_DELETE(_UIBar);

	_subScreen->release();
	SAFE_DELETE(_subScreen);

	_em->release();
	SAFE_DELETE(_em);

	//STATE::destroy();

}

void Stage::update(void)
{
	POINT cameraPos;
	cameraPos.x = DATAMANAGER->getPlayer()->getPlayer().movePosX;
	cameraPos.y = DATAMANAGER->getPlayer()->getPlayer().movePosY;
	CAM->setCameraPos(cameraPos);
	CAM->update();
	DATAMANAGER->getPlayer()->getPlayerCAM().rc = CAM->getScreenRect();

	DATAMANAGER->getPlayer()->update();

	_em->update();

	_UIBar->setHpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxHp);
	_UIBar->setSpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curSp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);
	_UIBar->update();
	IMG("Num_UI")->setFrameX(11);
	IMG("Num_UI")->setFrameY(1);




	if (KEYOKD('5'))
	{
		DATAMANAGER->getPlayer()->getPlayerStatus().curHp -= 10;
		DATAMANAGER->getPlayer()->setState(PLAYERSTATE::DEF);
	}

	if (KEYOKD('6'))
	{
		DATAMANAGER->getPlayer()->getPlayerStatus().curHp += 10;
	}

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
	_playereEffect->update();
	_monsterEffect->update();

}


// ������ ���� ���� �Լ� �߰� �ʿ�
void Stage::render(void)
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
	_em->render();

	// �÷��̾� 
	DATAMANAGER->getPlayer()->render();

	// ������Ʈ - ���� ���� Ȯ��
	//

	// ����Ʈ ���� 
	_monsterEffect->render();
	_playereEffect->render();

	// ��� ž
	DATAMANAGER->getMapData().mapTop->render(getMemDC(), 0, 0, cameraLeft,	cameraTop,	CENTER_X, WINSIZE_Y);
	

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		DATAMANAGER->getMapData().pixelMap->render
		(getMemDC(), 0, 0, cameraLeft, 	cameraTop, 	CENTER_X, WINSIZE_Y);
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

}

void Stage::portalOn()
{
	RECT tempRc;
	RECT playerTempRc;
	playerTempRc = RectMakeCenter(
		DATAMANAGER->getPlayer()->getPlayer().movePosX,
		DATAMANAGER->getPlayer()->getPlayer().moveRc.bottom,
		40, 30);

	// ����Ȧ�� ���� ����Ʈ 
	if ( IntersectRect(&tempRc, &DATAMANAGER->getMapData().gate.inRc[GATE_HOME], &playerTempRc) )
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
			//DATAMANAGER->getMapData().enterAbyssInfo.stage++;
			//DATAMANAGER->getPlayer()->getPlayerAbyss().stage++;

			DATAMANAGER->getMapData().enterAbyssInfo.stage = 4;
			DATAMANAGER->getPlayer()->getPlayerAbyss().stage = 4;

			stageChangeInit();
		}

	}
	else DATAMANAGER->getMapData().gate.inGateCount = 0;
}


void Stage::collision(void)
{
	RECT tempRc;
	for (int i = 0; i < _em->getMonsters().size(); i++)
	{
		// �÷��̾� ��������Ʈ -> ���� �ǰݹڽ�
		if ( IntersectRect(&tempRc, &DATAMANAGER->getPlayer()->getPlayerCollisionRc().attRc,
			&_em->getMonsters()[i]->getMonsterCollisionRc().defRc)      
			&& ! (_em->getMonsters()[i]->getState() == MONSTERSTATE::DEF) )
		{

			// ���� ü�°��� + �ǰݻ��·� ��ȯ
			_em->getMonsters()[i]->getState()= MONSTERSTATE::DEF;
			// ���� ü�� ���� �Լ�
			int temp = 0;
			temp = playerRandomDamage();
			cout << "�÷��̾� ������ : " << temp << endl;
			//_em->getMonsters()[i]->setHp(playerRandomDamage());
			_playereEffect->show(tempRc);
			_em->getMonsters()[i]->setHp(temp);
			cout << "���� ���� HP : " << _em->getMonsters()[i]->getHp() << endl;;
			break;

		}
		// ���� ü���� ������ 
		if (_em->getMonsters()[i]->getHp() <= 0)
		{
			// ���� ���� ����Ʈ ���,
			_monsterEffect->show(_em->getMonsters()[i]->getMonster().moveRc);
			// ���� ������ �÷��̾ ����,

			// ���� 
			_em->removeMonster(i);
		}

	}

}

int Stage::playerRandomDamage()
{
	int rndPlayerDmg;

		rndPlayerDmg = RND->getFromIntTo(
			DATAMANAGER->getPlayer()->getPlayerStatus().iAtt*0.85,
			DATAMANAGER->getPlayer()->getPlayerStatus().iAtt		);

	return rndPlayerDmg;

}

int Stage::monsterRandomDamage(int i)
{
	int rndMonsterDmg;

	rndMonsterDmg = RND->getFromIntTo(
		_em->getMonsters()[i]->getAtt() *0.85,
		_em->getMonsters()[i]->getAtt()            );

	return rndMonsterDmg;
}
