#include "Stdafx.h"
#include "Stage11.h"

HRESULT Stage11::init(void)
{
	// 스테이지 세팅 (맵+플레이어 정보)
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
		cout << "끼임탈출!" << endl;
		DATAMANAGER->getPlayer()->getPlayer().movePosX = 50;
		DATAMANAGER->getPlayer()->getPlayer().movePosY = 300;
	}

	_subScreen->update();


	// 죽으면 메인홀로 이동
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

	// 배경
	DATAMANAGER->getMapData().map->render
	(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);

	// 포탈
	IMGR("map_gate", getMemDC(),
		DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].left - cameraLeft,
		DATAMANAGER->getMapData().gate.drawRc[GATE_HOME].top - cameraTop);
	IMGR("map_gate", getMemDC(),
		DATAMANAGER->getMapData().gate.drawRc[GATE_NEXTSTAGE].left - cameraLeft,
		DATAMANAGER->getMapData().gate.drawRc[GATE_NEXTSTAGE].top - cameraTop);


	//if()
	// 몬스터
	_enemyM->render();

	// 플레이어 
	DATAMANAGER->getPlayer()->render();

	// 오브젝트 - 렌더 순서 확인
	//

	// 이펙트 렌더 
	//_effectM->render();

	// 배경 탑
	DATAMANAGER->getMapData().mapTop->render(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);


	if (KEYMANAGER->isToggleKey(VK_F2))
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
	else if (IntersectRect(&tempRc, &DATAMANAGER->getMapData().gate.inRc[GATE_NEXTSTAGE], &playerTempRc))
	{
		DATAMANAGER->getMapData().gate.inGateCount++;
		cout << "다음 스테이지 가는 게이트 로딩 중 :" << DATAMANAGER->getMapData().gate.inGateCount << endl;
		if (DATAMANAGER->getMapData().gate.inGateCount > 90)
		{
			DATAMANAGER->getMapData().gate.inGateCount = 0;
			// 다음 스테이지를 위해 스테이지 업데이트 해줄 것 
			DATAMANAGER->getMapData().enterAbyssInfo.stage = 4;
			DATAMANAGER->getPlayer()->getPlayerAbyss().stage = 4;

			// 씬체인지 stageChangeInit();
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
		// 플레이어 공격이펙트 -> 몬스터 피격박스
		if (IntersectRect(&tempRc, &DATAMANAGER->getPlayer()->getPlayerCollisionRc().attRc,
			&_enemyM->getMonsters()[i]->getMonsterCollisionRc().defRc)
			&& ! (_enemyM->getMonsters()[i]->getState() == MONSTERSTATE::DEF))
		{

			// 몬스터 피격상태로 전환 + 체력감소
			_enemyM->getMonsters()[i]->getState() = MONSTERSTATE::DEF;
			int temp = 0;
			temp = DATAMANAGER->getPlayer()->playerRandomDamage();
			cout << "플레이어 데미지 : " << temp << endl;
			//EFFECTMANAGER->getPlayerEff().show(tempRc); //이펙트 수정중!!!!

			_enemyM->getMonsters()[i]->setHp(temp);
			cout << "몬스터 남은 HP : " << _enemyM->getMonsters()[i]->getHp() << endl;;
			break;

		}
		// 몬스터 체력이 없으면 
		if (_enemyM->getMonsters()[i]->getHp() <= 0)
		{
			// 몬스터 죽음 이펙트 출력, //이펙트 수정중!!!!
			//EFFECTMANAGER->getMonsterEff()->show(_enemyM->getMonsters()[i]->getMonster().moveRc);
			// 몬스터 데이터 플레이어에 적용,

			// 삭제 
			_enemyM->removeMonster(i);
		}

	}


	for (int i = 0; i < _enemyM->getMonsters().size(); i++)
	{
		// 몬스터 공격이펙트 -> 플레이어 피격박스
		if (IntersectRect(&tempRc, &_enemyM->getMonsters()[i]->getMonsterCollisionRc().attRc,
			&DATAMANAGER->getPlayer()->getPlayerCollisionRc().defRc )
			&& ! (DATAMANAGER->getPlayer()->getState() == PLAYERSTATE::DEF))
		{
			// 플레이어 피격상태로 전환 + 체력감소
			DATAMANAGER->getPlayer()->getState() = PLAYERSTATE::DEF;

			// 플레이어 체력 세팅 함수
			int temp = 0;
			temp = _enemyM->monsterRandomDamage(i);
			cout << "몬스터의 데미지 : " << temp << endl;


			DATAMANAGER->getPlayer()->getPlayerStatus().curHp -= temp;
			_UIBar->setHpGauge(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, DATAMANAGER->getPlayer()->getPlayerStatus().maxHp);
			//EFFECTMANAGER->getPlayer()->show(tempRc);

			_enemyM->getMonsters()[i]->setHp(temp);
			cout << "플레이어 남은 HP : " << _enemyM->getMonsters()[i]->getHp() << endl;;
			break;
		}
	}
}

