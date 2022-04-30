#include "Stdafx.h"
#include "Stage14.h"

HRESULT Stage14::init(void)
{
	SOUNDMANAGER->play("stage14", 0.05f);

	// stage setting (map + player Info)
	DATAMANAGER->setStageSetting();

	_enemyM = new EnemyManager();
	_enemyM->init();

	_playerEff = new Effect();
	_monsterEff = new Effect();
	_playerEff2 = new PlayerEffect();
	_playerEff2->init();

	_UIBar = new ProgressBar();
	_UIBar->init(DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);

	_bossUIBar = new ProgressBarBoss();
	_bossUIBar->init(70,75,520,15);

	_subScreen = new SubMenu();
	_subScreen->init();

	// camera setting
	CAM->init();
	CAM->setLimitsX(LSCENTER_X, DATAMANAGER->getMapData().map->getWidth());
	CAM->setLimitsY(CENTER_Y, DATAMANAGER->getMapData().map->getHeight());


	_playerRndDmg = 0;
	_monsterRndDmg = 0;
	_tempMonsterNum = -1;

	_lastStageGate = false;
	_dmgSettingOk = false;


	fadeOut.init();

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

	SAFE_DELETE(_playerEff);
	SAFE_DELETE(_monsterEff);

	_playerEff2->release();
	SAFE_DELETE(_playerEff2);
}

void Stage14::update(void)
{
	POINT cameraPos;
	cameraPos.x = DATAMANAGER->getPlayer()->getPlayer().movePosX;
	cameraPos.y = DATAMANAGER->getPlayer()->getPlayer().movePosY;
	CAM->setCameraPos(cameraPos);
	CAM->update();
	DATAMANAGER->getPlayer()->getPlayerCAM().rc = CAM->getScreenRect();

	DATAMANAGER->getPlayer()->update();


	_enemyM->update();

	_playerEff->effUpdate();
	_playerEff2->update();



	_UIBar->setHpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxHp);
	_UIBar->setSpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curSp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);
	_UIBar->update();
	IMG("Num_UI")->setFrameX(11);
	IMG("Num_UI")->setFrameY(1);

	if (_enemyM->getMonsters()[0]->getHp() >= 0)
	{
		_bossUIBar->setBossHpGauge(_enemyM->getMonsters()[0]->getHp(), _enemyM->getMonsters()[0]->getMaxHp() );
	}

	_bossUIBar->update();

	_subScreen->update();

	if (_lastStageGate) 	portalOn();
	collision();
	damageSetting();


	fadeOut.update();
	if (fadeOut.onOff.test(NEXT) && DATAMANAGER->getPlayer()->getState() == PLAYERSTATE::DEAD) // ��ü����
	{
		SCENEMANAGER->changeScene("gameOver");
	}

	// ������ ���ӿ��� ȭ������ �̵�
	if (DATAMANAGER->getPlayer()->getState() == PLAYERSTATE::DEAD)
	{
		fadeOut.onOff.set(ON);
	}

}

void Stage14::render(void)
{

	int cameraLeft = CAM->getScreenRect().left;
	int cameraTop = CAM->getScreenRect().top;

	// backGround
	DATAMANAGER->getMapData().map->render(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);

	// portal(if Boss dead)
	if (_lastStageGate) 
	{
		DATAMANAGER->getPlayer()->getPlayerAbyss().abyss = 2;
		IMGR("map_gate", getMemDC(),
			DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].left - cameraLeft,
			DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].top - cameraTop);
	}

	// player + boss Render
	renderCheck();

	// guide Key (pixelCollision + gate Rect
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		DATAMANAGER->getMapData().pixelMap->render
		(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);

	Rectangle(getMemDC(),
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].left - cameraLeft,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].top - cameraTop,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].right - cameraLeft,
		DATAMANAGER->getMapData().gate.inRc[GATE_HOME].bottom - cameraTop );
	}


	// ================================================================================================
	// Effect (RIGHT SCREEN)
	// ================================================================================================


	// ����Ʈ ���� 
	if (_playerEff->onEffect) _playerEff->baseEffRender();


	// ���� ������ ����Ʈ 
	if(_playerEff->onDmgNumEffect) _playerEff->dmgEffRender();
	_playerEff2->render();


	// ================================================================================================
	// UI (RIGHT TOP SCREEN)
	// ================================================================================================

	_UIBar->render();
	_UIBar->renderHpSpNumImg(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().curSp,
		DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);
	
	if (!_lastStageGate) _bossUIBar->render();

	// ================================================================================================
	// MENU (LEFT SCREEN)
	// ================================================================================================

	_subScreen->render();
	_subScreen->renderUIMapInfo();
}

void Stage14::enterInfoCheck()
{
}

void Stage14::portalOn()
{
	int  gateIndex = 0;
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
			fadeOut.onOff.set(ON);
			gateIndex = 1;
			DATAMANAGER->setStoryRewardAbyss(0);
		}

	}
	else DATAMANAGER->getMapData().gate.inGateCount = 0;


	if (fadeOut.onOff.test(NEXT)) // ��ü����
	{
		SOUNDMANAGER->stop("stage14");
		if (gateIndex == 1) SCENEMANAGER->changeScene("main");
	}
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
			_enemyM->getMonsters()[i]->setPlayerCheck(true);

			// ���� ������ȯ�� ���� ����-�÷��̾� �� ������ ���Ϳ� ���� 
			getPlayerAngleAndDistance(i);

			// ���� ������ ���� ���� ���� ����
			_tempMonsterNum = i;

			break;

		}
		else
		{
			_enemyM->getMonsters()[i]->setPlayerCheck(false);
			_tempMonsterNum = -1;

			break;
		}
	}

#pragma endregion


	// �÷��̾� ����
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// �÷��̾� ��������Ʈ -> ���� �ǰݹڽ�
		if (IntersectRect(&tempRc, &DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRc,
			&_enemyM->getMonsters()[i]->getMonsterCollisionRc().defRc)
			&& _enemyM->getMonsters()[i]->getState() != MONSTERSTATE::DEF)
		{

			// ���� �ǰݻ��·� ��ȯ 
			_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::DEF;
			_dmgSettingOk = false;

			// �浹��ġ ����Ʈ
			_playerEff->baseEffSetting(tempRc, EFFECT_TYPE::P_ATKACK_COLLISION);
			_playerEff->onDmgNumEffect = true;
			_playerEff2->createEff(tempRc, EFFECT_TYPE::P_ATKACK_COLLISION);
			
			break;
		}

	}


	// ���� ����
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::ATK
			&& DATAMANAGER->getPlayer()->getPlayerStatus().curHp > 0 )
		{

			// ���� ��������Ʈ -> �÷��̾� �ǰݹڽ� �浹 ���� 
			if (IntersectRect(&tempRc, &_enemyM->getMonsters()[i]->getMonsterCollisionRc().atkRc,
				&DATAMANAGER->getPlayer()->getPlayerCollisionRc().defRc)
				&& DATAMANAGER->getPlayer()->getState() != PLAYERSTATE::DEF)
			{

				// �÷��̾� �ǰݻ��·� ��ȯ + ü�°��� + ����Ʈ
				DATAMANAGER->getPlayer()->getState() = PLAYERSTATE::DEF;
				cout << "���� Ÿ�ݷ�Ʈ�� �÷��̾� �ǰݷ�Ʈ �浹+�ǰݻ��·� " << endl;

				// �÷��̾� ü�� ���� �Լ�
				_monsterRndDmg = _enemyM->monsterRandomDamage(i);
				DATAMANAGER->getPlayer()->getPlayerStatus().curHp -= _monsterRndDmg;

				// �浹��ġ ����Ʈ

				cout << "���� ������ : " << _monsterRndDmg << endl;
				cout << "�÷��̾� ���� HP : " << DATAMANAGER->getPlayer()->getPlayerStatus().curHp << endl;;

				_enemyM->getMonsters()[i]->setAtkStart(false);
				_monsterRndDmg = 0;
				break;

			}
		}
	}
}


// �ǰ� ü�� �ݿ�
void Stage14::damageSetting()
{
	// �ǰݵ� ���ʹ� ü�°��� + ����Ʈ.
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		if (_enemyM->getMonsters()[i]->getState() != MONSTERSTATE::DEF) continue;
		
		if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEF
			)//&& !_dmgSettingOk)
		{

			// ���� �ǰ� ó�� 
			if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEF)
			{
				_playerRndDmg = DATAMANAGER->getPlayer()->playerRandomDamage();

				// ���� ü�� ����
				_enemyM->getMonsters()[i]->setHp(_playerRndDmg);
				_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::IDLE; // ���� ����
				_dmgSettingOk = true;
				cout << "�÷��̾� ������ : " << _playerRndDmg << endl;
				cout << "���� ���� HP : " << _enemyM->getMonsters()[i]->getHp() << endl;;
				 
				break;
			}
		}
	}


	int deadMonsterIndex = 0;
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		

		// ���� ü���� ������ 
		if (_enemyM->getMonsters()[i]->getHp() <= 0)
		{
			
			if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEAD &&
				_enemyM->getMonsters()[i]->getFrameX() == _enemyM->getMonsters()[i]->getImage()->getMaxFrameX())
			{
				_lastStageGate = true;
				DATAMANAGER->getStoryRewardAbyss().set(0);
			}


			if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEAD) continue;
			else
			{
				_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::DEAD;

				// ����ġ ȹ�� 
				DATAMANAGER->getPlayer()->getPlayerStatus().curExp += _enemyM->getMonsters()[i]->getExp();
				_enemyM->getMonsters()[i]->setExp(0);
				break;
			}

			
			
			// ���� - ����
			//_enemyM->removeMonster(i);
		}
#pragma endregion 

	}
}

// probeDown(�߹�)�� ���ؼ� �������� ����
void Stage14::renderCheck()
{
	
	if (_tempMonsterNum == -1) // ���Ͱ� �÷��̾� �ν�X
	{
		if (_enemyM->getMonsters()[0]->getHp() >= 0) _enemyM->render();
		DATAMANAGER->getPlayer()->render();
	}
	else if ( _enemyM->getMonsters()[_tempMonsterNum]->getMonsterPixel().probeDown
		<= DATAMANAGER->getPlayer()->getPlayerPixel().probeDown && (_tempMonsterNum >= 0)  )
	{
		if (_enemyM->getMonsters()[0]->getHp() >= 0) _enemyM->render();
		DATAMANAGER->getPlayer()->render();
	}
	else
	{
		DATAMANAGER->getPlayer()->render();
		if (_enemyM->getMonsters()[0]->getHp() >= 0) _enemyM->render();
	}


	cout << _enemyM->getMonsters()[0]->getMovePosY() << endl;

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
	MONSTERDIRECTION tempDirection;
	int sMPosX, sMPosY, ePPosX, ePPosY;
	sMPosX = sMPosY = ePPosX = ePPosY = 0;
	tempDirection = _enemyM->getMonsters()[i]->getDirection();

	switch (tempDirection)
	{
	case MONSTERDIRECTION::UP:
		sMPosX = _enemyM->getMonsters()[i]->getMovePosX();
		sMPosY = _enemyM->getMonsters()[i]->getMonsterCollisionRc().atkPosY;
		ePPosX = DATAMANAGER->getPlayer()->getPlayer().drawPosX;
		ePPosY = DATAMANAGER->getPlayer()->getPlayer().drawPosY;
		break;
	case MONSTERDIRECTION::DOWN:
		sMPosX = _enemyM->getMonsters()[i]->getMovePosX();
		sMPosY = _enemyM->getMonsters()[i]->getMonsterCollisionRc().atkPosY;
		ePPosX = DATAMANAGER->getPlayer()->getPlayer().drawPosX;
		ePPosY = DATAMANAGER->getPlayer()->getPlayer().drawPosY;
		break;
	case MONSTERDIRECTION::LEFT:
		sMPosX = _enemyM->getMonsters()[i]->getMonsterCollisionRc().defRc.left;
		sMPosY = _enemyM->getMonsters()[i]->getMovePosY();
		ePPosX = DATAMANAGER->getPlayer()->getPlayer().drawPosX;
		ePPosY = DATAMANAGER->getPlayer()->getPlayer().drawPosY;
		break;
	case MONSTERDIRECTION::RIGHT:		
		sMPosX = _enemyM->getMonsters()[i]->getMonsterCollisionRc().defRc.right;
		sMPosY = _enemyM->getMonsters()[i]->getMovePosY();
		ePPosX = DATAMANAGER->getPlayer()->getPlayer().drawPosX;
		ePPosY = DATAMANAGER->getPlayer()->getPlayer().drawPosY;
		break;

	}

	_enemyM->getMonsters()[i]->getDistance() =
		getDistance(sMPosX, sMPosY, ePPosX, ePPosY);
	
}



