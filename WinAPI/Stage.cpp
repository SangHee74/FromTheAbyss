#include "Stdafx.h"
#include "Stage.h"
#include "Abyss.h"

HRESULT Stage::init(void)
{
	// �������� ���� (��+�÷��̾� ����)
	DATAMANAGER->setStageSetting();
	
	_em = new EnemyManager();
	_em->init(_currentAbyss, _currentStage);

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
		DATAMANAGER->getMapData().gate.rc[GATE_HOME].left - cameraLeft,
		DATAMANAGER->getMapData().gate.rc[GATE_HOME].top - cameraTop);
	IMGR("map_gate", getMemDC(),
		DATAMANAGER->getMapData().gate.rc[GATE_NEXTSTAGE].left - cameraLeft,
		DATAMANAGER->getMapData().gate.rc[GATE_NEXTSTAGE].top - cameraTop);


	// ����
	_em->render();

	// �÷��̾� 
	DATAMANAGER->getPlayer()->render();

	// ������Ʈ - ���� ���� Ȯ��
	//

	// ��� ž
	DATAMANAGER->getMapData().mapTop->render
	(getMemDC(), 0, 0, cameraLeft,	cameraTop,	CENTER_X, WINSIZE_Y);
	

	if (KEYMANAGER->isToggleKey(VK_F2))
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




}

void Stage::portalOn()
{
	RECT tempRc;
	// ����Ȧ�� ���� ����Ʈ 
	if (IntersectRect(&tempRc, &DATAMANAGER->getMapData().gate.rc[GATE_HOME],
		&DATAMANAGER->getPlayer()->getPlayer().drawRc))
	{

	}
}

