#include "Stdafx.h"
#include "Stage14.h"

HRESULT Stage14::init(void)
{
	// 스테이지 세팅 (맵+플레이어 정보)
	DATAMANAGER->setStageSetting();

	_enemyM = new EnemyManager();
	_enemyM->init();

	_UIBar = new ProgressBar();
	_UIBar->init(DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxSp);


	_bossUIBar = new ProgressBarBoss();
	_bossUIBar->init(_enemyM->getMonsters()[0]->getHp());


	_subScreen = new SubMenu();
	_subScreen->init();

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
		cout << "끼임탈출!" << endl;
		DATAMANAGER->getPlayer()->getPlayer().movePosX = 50;
		DATAMANAGER->getPlayer()->getPlayer().movePosY = 300;
	}

	EFFECTMANAGER->update();

	_subScreen->update();


	// 죽으면 메인홀로 이동
	if (DATAMANAGER->getPlayer()->getState() == PLAYERSTATE::DEAD)
	{
		SCENEMANAGER->changeScene("main");
	}


	portalOn();
	collision();
}

void Stage14::render(void)
{
	int cameraLeft = CAM->getScreenRect().left;
	int cameraTop = CAM->getScreenRect().top;

	// 배경
	DATAMANAGER->getMapData().map->render
	(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);

	// 포탈
	if (_enemyM->getMonsters()[0]->getState() == MONSTERSTATE::DEAD)
	{
		IMGR("map_gate", getMemDC(),
			DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].left - cameraLeft,
			DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].top - cameraTop);
	}

	// 몬스터
	if (_enemyM->getMonsters()[0]->getHp() >= 0) _enemyM->render();

	// 플레이어 
	DATAMANAGER->getPlayer()->render();


	// 이펙트 렌더 
	EFFECTMANAGER->render();


	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		DATAMANAGER->getMapData().pixelMap->render
		(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);
	}

	// 서브화면(UI)
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

	// 메인홀로 가는 게이트 
	if (IntersectRect(&tempRc, &DATAMANAGER->getMapData().gate.inRc[GATE_HOME], &playerTempRc))
	{
		DATAMANAGER->getMapData().gate.inGateCount++;
		cout << "집가는 게이트 로딩 중 :" << DATAMANAGER->getMapData().gate.inGateCount << endl;
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

	// 몬스터의 인식범위 내 플레이어 충돌 시
	// 방향을 바꿔주고, 각도를 설정해 몬스터가 다가오게 한다.
	// 처음 지정한 인식범위를 초과한 경우 다시 돌아간다.
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// 몬스터 인식범위 -> 플레이어 피격범위
		if (IntersectRect(&tempRc, &_enemyM->getMonsters()[i]->getMonster().recognitionRc,
			&DATAMANAGER->getPlayer()->getPlayerCollisionRc().defRc))
		{
			_enemyM->getMonsters()[i]->getMonster().playerCheck = true;
			_enemyM->getMonsters()[i]->getMonster().angle = 
			getAngle(_enemyM->getMonsters()[i]->getMonster().movePosX, _enemyM->getMonsters()[i]->getMonster().movePosY,
				DATAMANAGER->getPlayer()->getPlayer().drawPosX, DATAMANAGER->getPlayer()->getPlayer().drawPosY);
		}
		else _enemyM->getMonsters()[i]->getMonster().playerCheck = false;
		break;
	}

	// 플레이어가 공격
	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// 플레이어 공격이펙트 -> 몬스터 피격박스
		if (IntersectRect(&tempRc, &DATAMANAGER->getPlayer()->getPlayerCollisionRc().attRc,
			&_enemyM->getMonsters()[i]->getMonsterCollisionRc().defRc)
			&& !(_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEF))
		{

			// 몬스터 체력감소 + 피격상태로 전환
			_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::DEF;
			// 몬스터 체력 세팅 함수
			int temp = 0;
			temp = playerRandomDamage();
			cout << "플레이어 데미지 : " << temp << endl;
			//_em->getMonsters()[i]->setHp(playerRandomDamage());
			//EFFECTMANAGER->getPlayer()->show(tempRc);

			_enemyM->getMonsters()[i]->setHp(temp);
			cout << "몬스터 남은 HP : " << _enemyM->getMonsters()[i]->getHp() << endl;;
			break;

		}
		// 몬스터 체력이 없으면 
		if (_enemyM->getMonsters()[i]->getHp() <= 0)
		{
			_lastStageGate = true;
			// 몬스터 죽음 이펙트 출력,
			//_monsterEffect->show(_enemyM->getMonsters()[i]->getMonster().moveRc);
			// 몬스터 데이터 플레이어에 적용,

			// 삭제 
			_enemyM->removeMonster(i);
		}

	}
}

int Stage14::playerRandomDamage()
{
	int rndPlayerDmg;

	rndPlayerDmg = RND->getFromIntTo(
		DATAMANAGER->getPlayer()->getPlayerStatus().iAtt*0.85,
		DATAMANAGER->getPlayer()->getPlayerStatus().iAtt);

	return rndPlayerDmg;
}

int Stage14::monsterRandomDamage(int i)
{
	int rndMonsterDmg;

	rndMonsterDmg = RND->getFromIntTo(
		_enemyM->getMonsters()[i]->getAtt() *0.85,
		_enemyM->getMonsters()[i]->getAtt());

	return rndMonsterDmg;
}