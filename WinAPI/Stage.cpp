#include "Stdafx.h"
#include "Stage.h"
//#include "STATE.h"


HRESULT Stage::init(void)
{
	_player = new Player();
	_player->init();
	_player->setPixelMap("map_stage1_pixel");

	_UIBar = new ProgressBar();
	_UIBar->init(_player->getPlayerStatus().maxHp, _player->getPlayerStatus().maxSp);
	
	_subScreen = new SubMenu();
	_subScreen->init();

	_em = new EnemyManager();
	_em->init();

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, IMG("map_stage1")->getWidth());
	CAM->setLimitsY(CENTER_Y, IMG("map_stage1")->getHeight());

	_alpha;

	return S_OK;
}

void Stage::release(void)
{
	_UIBar->release();
	SAFE_DELETE(_UIBar);

	_subScreen->release();
	SAFE_DELETE(_subScreen);

	_player->release();
	SAFE_DELETE(_player);

	_em->release();
	SAFE_DELETE(_em);

	//STATE::destroy();

}

void Stage::update(void)
{
	POINT cameraPos;
	cameraPos.x = _player->getPlayer().movePosX;
	cameraPos.y = _player->getPlayer().movePosY;
	CAM->setCameraPos(cameraPos);
	CAM->update();
	_player->getPlayerCAM().rc = CAM->getScreenRect();
	_player->update();

	_UIBar->update();
	IMG("Num_UI")->setFrameX(11);
	IMG("Num_UI")->setFrameY(1);

	// 포션 적용 시 ( 인벤토리 작성 후 getPotionGauge() 할 것
	if (KEYMANAGER->isOnceKeyDown(VK_F10))
	{
		int healGayge = 100;
		_UIBar->setHpGauge(healGayge, _player->getPlayerStatus().maxHp);
		_UIBar->setSpGauge(healGayge, _player->getPlayerStatus().maxSp);

	}

	_subScreen->update();
	
	
	// 죽으면 메인홀로 이동
	if ( !_player->getIsStateCheck().test(4))
	{
		SCENEMANAGER->changeScene("main");
	}

	_em->update();

	int tempDistance;
	//getDistance(_player->getPlayer().movePosX, _player->getPlayer().movePosY,
	//	_em->getMonsters())

}

void Stage::render(void)
{
	int cameraLeft = CAM->getScreenRect().left;
	int cameraTop = CAM->getScreenRect().top;

	IMGR("map_stage1", getMemDC(), 0, 0,
		cameraLeft,
		cameraTop,
		CENTER_X, WINSIZE_Y);

	_player->render();

	//_em->render();

	IMGR("map_stage1_top", getMemDC(), 0, 0,
		cameraLeft,
		cameraTop,
		CENTER_X, WINSIZE_Y);
	
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		IMGR("map_stage1_pixel", getMemDC(), 0, 0,
			cameraLeft,
			cameraTop,
			CENTER_X, WINSIZE_Y);
	}
	_UIBar->render();
	_UIBar->renderHpSpNumImg(_player->getPlayerStatus().curHp, _player->getPlayerStatus().curSp,
		_player->getPlayerStatus().maxHp, _player->getPlayerStatus().maxSp);
	//IMGR("UI_pathInfo", getMemDC(), LSCENTER_X-21, 10);

	_subScreen->render();



}
