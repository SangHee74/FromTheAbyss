#include "Stdafx.h"
#include "StageBossIntro.h"

HRESULT StageBossIntro::init(void)
{
	// stage setting (map + player Info)
	DATAMANAGER->setStageSetting();

	// menu setting
	_subScreen = new SubMenu();
	_subScreen->init();

	// camera setting
	CAM->init();
	CAM->setLimitsX(LSCENTER_X, DATAMANAGER->getMapData().map->getWidth());
	CAM->setLimitsY(CENTER_Y, DATAMANAGER->getMapData().map->getHeight());

	// boss setting
	_bossPos = { 0,0 };
	bossImageChange(false);
	_bossFrameX = 0;
	_bossFrameCount = 0;
	_bossNameAlpha = 254;

	_eventStart = false;
	_eventEnd = false;

	_firstUpdate = 0;

	fadeOut.init();


	return S_OK;
}


void StageBossIntro::release(void)
{
}


void StageBossIntro::update(void)
{

	POINT cameraPos;
	cameraPos.x = DATAMANAGER->getPlayer()->getPlayer().movePosX;
	cameraPos.y = DATAMANAGER->getPlayer()->getPlayer().movePosY;
	CAM->setCameraPos(cameraPos);
	CAM->update();
	DATAMANAGER->getPlayer()->getPlayerCAM().rc = CAM->getScreenRect();


	if (_firstUpdate < 10)
	{
		DATAMANAGER->getPlayer()->update();
		_firstUpdate++;

		CAM->focusStart(_bossPos);
	}

	if (CAM->getFocusOn())
	{
		bossImageChange(); // skill img
		_eventStart = true;
	}


	// boss frame Update
	_bossFrameCount++;
	if (CAM->getFocusOn())
	{
		if (_bossFrameCount % 5 == 0)
		{
			_bossFrameCount = 0;
			_bossFrameX++;
		}
	}
	else
	{
		if (_bossFrameCount % 30 == 0)
		{
			_bossFrameCount = 0;
			_bossFrameX++;
		}
	}

	if (_bossFrameX >= 3) _bossFrameX = 0;



	if (_eventStart)
	{
		_bossNameAlpha--;
		if (_bossNameAlpha <= 0)
		{
			_bossNameAlpha = 254;
			fadeOut.onOff.set(ON);
		}
	}


	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // scene change
	{
		switch (DATAMANAGER->getMapData().enterAbyssInfo.abyss)
		{
		case 1:
			SCENEMANAGER->changeScene("stage14");
			break;
		}

	}
}


void StageBossIntro::render(void)
{
	int cameraLeft = CAM->getScreenRect().left;
	int cameraTop = CAM->getScreenRect().top;

	// backGround
	DATAMANAGER->getMapData().map->render(getMemDC(), 0, 0, cameraLeft, cameraTop, CENTER_X, WINSIZE_Y);
	
	DATAMANAGER->getPlayer()->render();

	_bossImage->frameRender(getMemDC(), _bossPos.x - cameraLeft, _bossPos.y - cameraTop, _bossFrameX,0);
	if (CAM->getFocusOn()) 	_bossName->alphaRender(getMemDC(), 0, WINSIZE_Y - _bossName->getHeight(), _bossNameAlpha);


	// MENU (LEFT SCREEN)
	_subScreen->render();


	// fadeOut
	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);
}

void StageBossIntro::bossImageChange(bool skill)
{
	switch (DATAMANAGER->getMapData().enterAbyssInfo.abyss)
	{
	case 1:
		_bossPos = { 1064 , 650 };
		_bossName = IMG("mino_name");
		if( skill ) _bossImage = IMG("mino_skill");
		else _bossImage = IMG("mino_idle2");
		break;
		

	case 2:
		break;

	}

	
}



