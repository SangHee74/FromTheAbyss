#include "Stdafx.h"
#include "Stage.h"

HRESULT Stage::init(void)
{

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, IMG("Å×¸Ê")->getWidth());
	CAM->setLimitsY(CENTER_Y, IMG("Å×¸Ê")->getHeight());

	_player = new Player();
	_player->init();

	return S_OK;
}

void Stage::release(void)
{
	
	_player->release();
	SAFE_DELETE(_player);
}

void Stage::update(void)
{
	POINT cameraPos;
	cameraPos.x = _player->getPlayerPosX();
	cameraPos.y = _player->getPlayerPosY();

	CAM->setCameraPos(cameraPos);
	CAM->update();
	CAM->setCameraPos(cameraPos);
	CAM->update();
	_player->setCameraRect(CAM->getScreenRect());
	_player->update();

	POINT playerPoint = { _player->getPlayerPosX(),_player->getPlayerPosY() };


	_player->update();
}

void Stage::render(void)
{

	CAM->render();

		int cameraLeft = CAM->getScreenRect().left;
		int cameraTop = CAM->getScreenRect().top;

		IMAGEMANAGER->render("Å×¸Ê", getMemDC(), 0, 0,
			cameraLeft,
			cameraTop,
			WINSIZE_X, WINSIZE_Y);

	IMGR("map", getMemDC(),CENTER_X,0);


	//IMGR("p_idle_6", getMemDC(), _rc.left, _rc.top);
	_player->render();
}
