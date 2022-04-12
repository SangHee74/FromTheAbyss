#include "Stdafx.h"
#include "Stage.h"
#include "Abyss.h"

HRESULT Stage::init(void)
{
	// 스테이지 세팅 (맵+플레이어 정보)
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

	// 스테이지 세팅 (맵 정보)
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
	_playereEffect->update();
	_monsterEffect->update();

}


// 렌더링 순서 변경 함수 추가 필요
void Stage::render(void)
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
	_em->render();

	// 플레이어 
	DATAMANAGER->getPlayer()->render();

	// 오브젝트 - 렌더 순서 확인
	//

	// 이펙트 렌더 
	_monsterEffect->render();
	_playereEffect->render();

	// 배경 탑
	DATAMANAGER->getMapData().mapTop->render(getMemDC(), 0, 0, cameraLeft,	cameraTop,	CENTER_X, WINSIZE_Y);
	

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		DATAMANAGER->getMapData().pixelMap->render
		(getMemDC(), 0, 0, cameraLeft, 	cameraTop, 	CENTER_X, WINSIZE_Y);
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

}

void Stage::portalOn()
{
	RECT tempRc;
	RECT playerTempRc;
	playerTempRc = RectMakeCenter(
		DATAMANAGER->getPlayer()->getPlayer().movePosX,
		DATAMANAGER->getPlayer()->getPlayer().moveRc.bottom,
		40, 30);

	// 메인홀로 가는 게이트 
	if ( IntersectRect(&tempRc, &DATAMANAGER->getMapData().gate.inRc[GATE_HOME], &playerTempRc) )
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
		// 플레이어 공격이펙트 -> 몬스터 피격박스
		if ( IntersectRect(&tempRc, &DATAMANAGER->getPlayer()->getPlayerCollisionRc().attRc,
			&_em->getMonsters()[i]->getMonsterCollisionRc().defRc)      
			&& ! (_em->getMonsters()[i]->getState() == MONSTERSTATE::DEF) )
		{

			// 몬스터 체력감소 + 피격상태로 전환
			_em->getMonsters()[i]->getState()= MONSTERSTATE::DEF;
			// 몬스터 체력 세팅 함수
			int temp = 0;
			temp = playerRandomDamage();
			cout << "플레이어 데미지 : " << temp << endl;
			//_em->getMonsters()[i]->setHp(playerRandomDamage());
			_playereEffect->show(tempRc);
			_em->getMonsters()[i]->setHp(temp);
			cout << "몬스터 남은 HP : " << _em->getMonsters()[i]->getHp() << endl;;
			break;

		}
		// 몬스터 체력이 없으면 
		if (_em->getMonsters()[i]->getHp() <= 0)
		{
			// 몬스터 죽음 이펙트 출력,
			_monsterEffect->show(_em->getMonsters()[i]->getMonster().moveRc);
			// 몬스터 데이터 플레이어에 적용,

			// 삭제 
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
