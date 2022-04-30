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
	if (fadeOut.onOff.test(NEXT) && DATAMANAGER->getPlayer()->getState() == PLAYERSTATE::DEAD) // 씬체인지
	{
		SCENEMANAGER->changeScene("gameOver");
	}

	// 죽으면 게임오버 화면으로 이동
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


	// 이펙트 렌더 
	if (_playerEff->onEffect) _playerEff->baseEffRender();


	// 랜덤 데미지 이펙트 
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

	// 메인홀로 가는 게이트 
	if (IntersectRect(&tempRc, &DATAMANAGER->getMapData().gate.inRc[GATE_HOME], &playerTempRc))
	{
		DATAMANAGER->getMapData().gate.inGateCount++;
		cout << "집가는 게이트 로딩 중 :" << DATAMANAGER->getMapData().gate.inGateCount << endl;
		if (DATAMANAGER->getMapData().gate.inGateCount > 90)
		{
			DATAMANAGER->getMapData().gate.inGateCount = 0;
			fadeOut.onOff.set(ON);
			gateIndex = 1;
			DATAMANAGER->setStoryRewardAbyss(0);
		}

	}
	else DATAMANAGER->getMapData().gate.inGateCount = 0;


	if (fadeOut.onOff.test(NEXT)) // 씬체인지
	{
		SOUNDMANAGER->stop("stage14");
		if (gateIndex == 1) SCENEMANAGER->changeScene("main");
	}
}

void Stage14::collision()
{
	RECT tempRc;

	// 몬스터의 인식범위 내 플레이어 충돌 시
#pragma region 몬스터의 플레이어 인식 

	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// 몬스터 인식범위 -> 플레이어 피격범위
		if (IntersectRect(&tempRc, &_enemyM->getMonsters()[i]->getReconitionRc(),
			&DATAMANAGER->getPlayer()->getPlayerCollisionRc().defRc))
		{
			// 몬스터가 플레이어를 인식 함 -> 따라다님
			_enemyM->getMonsters()[i]->setPlayerCheck(true);

			// 몬스터 방향전환을 위한 몬스터-플레이어 간 각도를 몬스터에 전달 
			getPlayerAngleAndDistance(i);

			// 렌더 순서와 비교할 몬스터 변수 저장
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


	// 플레이어 공격
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// 플레이어 공격이펙트 -> 몬스터 피격박스
		if (IntersectRect(&tempRc, &DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRc,
			&_enemyM->getMonsters()[i]->getMonsterCollisionRc().defRc)
			&& _enemyM->getMonsters()[i]->getState() != MONSTERSTATE::DEF)
		{

			// 몬스터 피격상태로 전환 
			_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::DEF;
			_dmgSettingOk = false;

			// 충돌위치 이펙트
			_playerEff->baseEffSetting(tempRc, EFFECT_TYPE::P_ATKACK_COLLISION);
			_playerEff->onDmgNumEffect = true;
			_playerEff2->createEff(tempRc, EFFECT_TYPE::P_ATKACK_COLLISION);
			
			break;
		}

	}


	// 몬스터 공격
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::ATK
			&& DATAMANAGER->getPlayer()->getPlayerStatus().curHp > 0 )
		{

			// 몬스터 공격이펙트 -> 플레이어 피격박스 충돌 판정 
			if (IntersectRect(&tempRc, &_enemyM->getMonsters()[i]->getMonsterCollisionRc().atkRc,
				&DATAMANAGER->getPlayer()->getPlayerCollisionRc().defRc)
				&& DATAMANAGER->getPlayer()->getState() != PLAYERSTATE::DEF)
			{

				// 플레이어 피격상태로 전환 + 체력감소 + 이펙트
				DATAMANAGER->getPlayer()->getState() = PLAYERSTATE::DEF;
				cout << "몬스터 타격렉트와 플레이어 피격렉트 충돌+피격상태로 " << endl;

				// 플레이어 체력 세팅 함수
				_monsterRndDmg = _enemyM->monsterRandomDamage(i);
				DATAMANAGER->getPlayer()->getPlayerStatus().curHp -= _monsterRndDmg;

				// 충돌위치 이펙트

				cout << "몬스터 데미지 : " << _monsterRndDmg << endl;
				cout << "플레이어 남은 HP : " << DATAMANAGER->getPlayer()->getPlayerStatus().curHp << endl;;

				_enemyM->getMonsters()[i]->setAtkStart(false);
				_monsterRndDmg = 0;
				break;

			}
		}
	}
}


// 피격 체력 반영
void Stage14::damageSetting()
{
	// 피격된 몬스터는 체력감소 + 이펙트.
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		if (_enemyM->getMonsters()[i]->getState() != MONSTERSTATE::DEF) continue;
		
		if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEF
			)//&& !_dmgSettingOk)
		{

			// 몬스터 피격 처리 
			if (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEF)
			{
				_playerRndDmg = DATAMANAGER->getPlayer()->playerRandomDamage();

				// 몬스터 체력 세팅
				_enemyM->getMonsters()[i]->setHp(_playerRndDmg);
				_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::IDLE; // 상태 수정
				_dmgSettingOk = true;
				cout << "플레이어 데미지 : " << _playerRndDmg << endl;
				cout << "몬스터 남은 HP : " << _enemyM->getMonsters()[i]->getHp() << endl;;
				 
				break;
			}
		}
	}


	int deadMonsterIndex = 0;
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		

		// 몬스터 체력이 없으면 
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

				// 경험치 획득 
				DATAMANAGER->getPlayer()->getPlayerStatus().curExp += _enemyM->getMonsters()[i]->getExp();
				_enemyM->getMonsters()[i]->setExp(0);
				break;
			}

			
			
			// 삭제 - 터짐
			//_enemyM->removeMonster(i);
		}
#pragma endregion 

	}
}

// probeDown(발밑)를 비교해서 렌더순서 변경
void Stage14::renderCheck()
{
	
	if (_tempMonsterNum == -1) // 몬스터가 플레이어 인식X
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



