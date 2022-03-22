#include "Stdafx.h"
#include "Stage.h"

HRESULT Stage::init(void)
{
	_player = new Player();
	_player->init();

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, IMG("�׸�")->getWidth());
	CAM->setLimitsY(CENTER_Y, IMG("�׸�")->getHeight());


	_UIBar = new ProgressBar;
	_UIBar->init(_player->getStatus().maxHp, _player->getStatus().maxSp);
	return S_OK;
}

void Stage::release(void)
{
	_UIBar->release();
	SAFE_DELETE(_UIBar);

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
	_player->setCameraRect(CAM->getScreenRect());
	_player->update();

	//cout <<"ī�޶�pos : " <<  cameraPos.x  << " , " << cameraPos.y<< endl;


	_UIBar->update();
	IMG("Num_UI")->setFrameX(11);
	IMG("Num_UI")->setFrameY(1);

	// ���� ���� �� ( �κ��丮 �ۼ� �� getPotionGauge() �� ��
	if (KEYMANAGER->isOnceKeyDown(VK_F10))
	{
		int healGayge = 100;
		_UIBar->setHpGauge(healGayge, _player->getStatus().maxHp);
		_UIBar->setSpGauge(healGayge, _player->getStatus().maxSp);

	}

	
}

void Stage::render(void)
{
	

	CAM->render();

		int cameraLeft = CAM->getScreenRect().left;
		int cameraTop = CAM->getScreenRect().top;

		if (KEYOKD(VK_F3))
		{
			cout << "ī�޶�X : " << cameraLeft << endl;
		}

		IMGR("�׸�", getMemDC(), 0, 0,
			cameraLeft,
			cameraTop,
			CENTER_X, WINSIZE_Y);

	IMGR("sub_map", getMemDC(), CENTER_X,0);


	_player->render();

	_UIBar->render();

}
