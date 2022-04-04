#include "Stdafx.h"
#include "Stage.h"
//#include "STATE.h"


HRESULT Stage::init(void)
{
	_player = new Player();
	_player->init();
	

	_subScreen = new SubMenu();
	_subScreen->init();

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, IMG("¸Ê2")->getWidth());
	CAM->setLimitsY(CENTER_Y, IMG("¸Ê2")->getHeight());


	_UIBar = new ProgressBar;
	_UIBar->init(_player->getPlayerStatus().maxHp, _player->getPlayerStatus().maxSp);

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

	// Æ÷¼Ç Àû¿ë ½Ã ( ÀÎº¥Åä¸® ÀÛ¼º ÈÄ getPotionGauge() ÇÒ °Í
	if (KEYMANAGER->isOnceKeyDown(VK_F10))
	{
		int healGayge = 100;
		_UIBar->setHpGauge(healGayge, _player->getPlayerStatus().maxHp);
		_UIBar->setSpGauge(healGayge, _player->getPlayerStatus().maxSp);

	}

	_subScreen->update();
	
	
	// Á×À¸¸é ¸ŞÀÎÈ¦·Î ÀÌµ¿
	if ( !_player->getIsStateCheck().test(4))
	{
		SCENEMANAGER->changeScene("main");
	}
}

void Stage::render(void)
{
	int cameraLeft = CAM->getScreenRect().left;
	int cameraTop = CAM->getScreenRect().top;

	IMGR("¸Ê2", getMemDC(), 0, 0,
		cameraLeft,
		cameraTop,
		CENTER_X, WINSIZE_Y);

	IMGR("UI_pathInfo", getMemDC(), LSCENTER_X-21, 10);

	_player->render();

	_UIBar->render();
	_UIBar->renderHpSpNumImg(_player->getPlayerStatus().curHp, _player->getPlayerStatus().curSp,
		_player->getPlayerStatus().maxHp, _player->getPlayerStatus().maxSp);
	_subScreen->render();

}
