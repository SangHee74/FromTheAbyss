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
	
	_subScreen = new SubMenu();
	_subScreen->init();

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, DATAMANAGER->getMapData().map->getWidth());
	CAM->setLimitsY(CENTER_Y, DATAMANAGER->getMapData().map->getHeight());

	_alpha = 0;

	return S_OK;
}

void Stage::release(void)
{
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
		DATAMANAGER->getPlayer()->setState(PLAYERSTATE::HIT);
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


	// 배경 탑
	DATAMANAGER->getMapData().mapTop->render
	(getMemDC(), 0, 0, cameraLeft,	cameraTop,	CENTER_X, WINSIZE_Y);
	

	if (KEYMANAGER->isToggleKey(VK_F2))
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
			DATAMANAGER->getMapData().enterAbyssInfo.stage++;
			DATAMANAGER->getPlayer()->getPlayerAbyss().stage++;

			SCENEMANAGER->changeScene("stage");
		}

	}
	else DATAMANAGER->getMapData().gate.inGateCount = 0;
}

