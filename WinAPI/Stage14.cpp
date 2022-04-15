#include "Stdafx.h"
#include "Stage14.h"

HRESULT Stage14::init(void)
{
	// �������� ���� (��+�÷��̾� ����)
	DATAMANAGER->setStageSetting();

	_enemyM = new EnemyManager();
	_enemyM->init();

	_enemyEff = new MonsterEffect();
	_enemyEff->init();

	_playerEff = new PlayerEffect();
	_playerEff->init();

	_UIBar = new ProgressBar();
	_UIBar->init(DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);

	_bossUIBar = new ProgressBarBoss();
	_bossUIBar->init(_enemyM->getMonsters()[0]->getHp());

	_subScreen = new SubMenu();
	_subScreen->init();

	_tempMonsterNum = -1;

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, DATAMANAGER->getMapData().map->getWidth());
	CAM->setLimitsY(CENTER_Y, DATAMANAGER->getMapData().map->getHeight());

	_enterInfo.alpha = 255;
	_enterInfo.showTime = 0;

	_lastStageGate = false;

	return S_OK;
}

void Stage14::release(void)
{
	_UIBar->release();
	SAFE_DELETE(_UIBar);

	_bossUIBar->release();
	SAFE_DELETE(_bossUIBar);

	_subScreen->release();
	SAFE_DELETE(_subScreen);

	_enemyM->release();
	SAFE_DELETE(_enemyM);

	_enemyEff->release();
	SAFE_DELETE(_enemyEff);

	_playerEff->release();
	SAFE_DELETE(_playerEff);
}

void Stage14::update(void)
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
	_enemyEff->update();
	_playerEff->update();

	_UIBar->setHpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxHp);
	_UIBar->setSpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curSp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);
	_UIBar->update();
	IMG("Num_UI")->setFrameX(11);
	IMG("Num_UI")->setFrameY(1);

	if (_enemyM->getMonsters()[0]->getHp() >= 0)
	{
		_bossUIBar->setBossHpGauge(_enemyM->getMonsters()[0]->getHp());
		_bossUIBar->update();
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


	if (_lastStageGate) 	portalOn();
	collision();
	//monsterMovetoPlayer();
}

void Stage14::render(void)
{
	int cameraLeft = CAM->getScreenRect().left;
	int cameraTop = CAM->getScreenRect().top;

	// ���
	DATAMANAGER->getMapData().map->render
	(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);

	// ��Ż(������ ������)
	if (_lastStageGate) 
	{
		IMGR("map_gate", getMemDC(),
			DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].left - cameraLeft,
			DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].top - cameraTop);
	}

	renderCheck();



	// ����Ʈ ���� 
	_enemyEff->render();
	_playerEff->render();


	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		DATAMANAGER->getMapData().pixelMap->render
		(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);
	}


	// ����ȭ��+UI
	_UIBar->render();
	_UIBar->renderHpSpNumImg(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().curSp,
		DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);
		

	_subScreen->render();

	Rectangle(getMemDC(),
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].left - cameraLeft,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].top - cameraTop,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].right - cameraLeft,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].bottom - cameraTop
	);

	// �� ���� �� �ʹ� ������ ���ķ����̹���
	IMGAR("map_abyss", getMemDC(), LSCENTER_X, CENTER_Y - 10, _enterInfo.alpha);
	IMGFAR("Num_UI", getMemDC(), LSCENTER_X + 70, CENTER_Y - 10, DATAMANAGER->getMapData().enterAbyssInfo.stage, 0, _enterInfo.alpha);
	IMGFAR("Num_UI", getMemDC(), LSCENTER_X + 70, CENTER_Y - 10, DATAMANAGER->getMapData().enterAbyssInfo.stage, 0, _enterInfo.alpha);


}

void Stage14::enterInfoCheck()
{
}

void Stage14::portalOn()
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
	else DATAMANAGER->getMapData().gate.inGateCount = 0;
}

void Stage14::collision()
{
	RECT tempRc;

	// ������ �νĹ��� �� �÷��̾� �浹 ��
#pragma region ������ �÷��̾� �ν� 

	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// ���� �νĹ��� -> �÷��̾� �ǰݹ���
		if (IntersectRect(&tempRc, &_enemyM->getMonsters()[i]->getReconitionRc(),
			&DATAMANAGER->getPlayer()->getPlayerCollisionRc().defRc))
		{
			// ���Ͱ� �÷��̾ �ν� �� -> ����ٴ�
			_enemyM->getMonsters()[i]->getPlayerCheck() = true;

			// ���� ������ȯ�� ���� ����-�÷��̾� �� ������ ���Ϳ� ���� 
			getPlayerAngleAndDistance(i);

			// ���� ������ ���� ���� ���� ����
			_tempMonsterNum = i;
			
		}
		else
		{
			_enemyM->getMonsters()[i]->getPlayerCheck() = false;
			_tempMonsterNum = -1;
		}
		break;
	}

#pragma endregion

#pragma region �÷��̾��� ����

	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// �÷��̾� ��������Ʈ -> ���� �ǰݹڽ�
		if (IntersectRect(&tempRc, &DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRc,
			&_enemyM->getMonsters()[i]->getMonsterCollisionRc().defRc)
			&& _enemyM->getMonsters()[i]->getState() != MONSTERSTATE::DEF )
		{
			// ���� �ǰݻ��·� ��ȯ + ü�°��� + ����Ʈ
			_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::DEF;
			
			// ���� ü�� ���� �Լ�
			int temp = 0;
			temp = DATAMANAGER->getPlayer()->playerRandomDamage();
			_enemyM->getMonsters()[i]->setHp(temp);

			// �浹��ġ ����Ʈ
			_playerEff->createEff(tempRc, EFFECT_TYPE::P_ATKACK_COLLISION);

			cout << "�÷��̾� ������ : " << temp << endl;
			cout << "���� ���� HP : " << _enemyM->getMonsters()[i]->getHp() << endl;;
			break;

		}
		// ���� ü���� ������ 
		if (_enemyM->getMonsters()[i]->getHp() <= 0)
		{
			_lastStageGate = true;
			
			// ���� ���� ����Ʈ
			_enemyEff->createEff(tempRc,EFFECT_TYPE::M_DEFFENSE_BOSSDIE);

			// ����ġ ȹ�� 
			DATAMANAGER->getPlayer()->getPlayerStatus().curExp += _enemyM->getMonsters()[i]->getExp();

			// ���� - ����
			//_enemyM->removeMonster(i);
			_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::DEAD;
		}
#pragma endregion 

#pragma region ������ ����

		// ���� ��������Ʈ -> �÷��̾� �ǰݹڽ�
		if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::ATK)
		{
			if (IntersectRect(&tempRc, &_enemyM->getMonsters()[i]->getMonsterCollisionRc().atkRc,
				&DATAMANAGER->getPlayer()->getPlayerCollisionRc().defRc)
				&& DATAMANAGER->getPlayer()->getState() != PLAYERSTATE::DEF)
			{
				cout << "���� Ÿ�ݷ�Ʈ�� �÷��̾� �ǰݷ�Ʈ �浹" << endl;

				// �÷��̾� �ǰݻ��·� ��ȯ + ü�°��� + ����Ʈ
				DATAMANAGER->getPlayer()->getState() = PLAYERSTATE::DEF;

				// �÷��̾� ü�� ���� �Լ�
				int temp = 0;
				temp = _enemyM->monsterRandomDamage(i);
				DATAMANAGER->getPlayer()->getPlayerStatus().curHp -= temp;

				// �浹��ġ ����Ʈ
				_enemyEff->createEff(tempRc,EFFECT_TYPE::M_ATKACK_COLLISION);

				DATAMANAGER->getPlayer()->getPlayerStatus().curHp -= temp;
				cout << "���� ������ : " << temp << endl;
				cout << "�÷��̾� ���� HP : " << DATAMANAGER->getPlayer()->getPlayerStatus().curHp << endl;;
				break;

			}
		}
		
#pragma endregion 

	}
}



// probeDown(�߹�)�� ���ؼ� �������� ����
void Stage14::renderCheck()
{
	if (_tempMonsterNum < 0)
	{
		if (_enemyM->getMonsters()[0]->getHp() >= 0) _enemyM->render();
		DATAMANAGER->getPlayer()->render();
	}
	else if ( _enemyM->getMonsters()[_tempMonsterNum]->getMonsterPixel().probeDown
				<= DATAMANAGER->getPlayer()->getPlayerPixel().probeDown
			 && (_tempMonsterNum >= 0)  )
	{
		if (_enemyM->getMonsters()[0]->getHp() >= 0) _enemyM->render();
		DATAMANAGER->getPlayer()->render();
	}
	else
	{
		DATAMANAGER->getPlayer()->render();
		if (_enemyM->getMonsters()[0]->getHp() >= 0) _enemyM->render();
	}

}


void Stage14::getPlayerAngleAndDistance(int i)
{
	// angle
	_enemyM->getMonsters()[i]->getAngle() =
		getAngle(_enemyM->getMonsters()[i]->getMovePosX(),
			_enemyM->getMonsters()[i]->getMovePosY(),
			DATAMANAGER->getPlayer()->getPlayer().drawPosX,
			DATAMANAGER->getPlayer()->getPlayer().drawPosY);

	// distance 
	_enemyM->getMonsters()[i]->getDistance() =
		getDistance(_enemyM->getMonsters()[i]->getMovePosX(),
			_enemyM->getMonsters()[i]->getMovePosY(),
			DATAMANAGER->getPlayer()->getPlayer().drawPosX,
			DATAMANAGER->getPlayer()->getPlayer().drawPosY);

	// distance view
	LineMake(getMemDC(), 
		_enemyM->getMonsters()[i]->getMovePosX(),
		_enemyM->getMonsters()[i]->getMovePosY(),
		DATAMANAGER->getPlayer()->getPlayer().drawPosX,
		DATAMANAGER->getPlayer()->getPlayer().drawPosY
		);

	
}



