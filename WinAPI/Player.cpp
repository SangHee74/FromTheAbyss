#include "Stdafx.h"
#include "Player.h"


HRESULT Player::init(void)
{

	_pos.x = LSCENTER_X;
	_pos.y = WINSIZE_Y - 140;
	_rcPlayer = RectMakeCenter(_pos.x, _pos.y, IMG("p_idle_6")->getFrameWidth(), IMG("p_idle_6")->getFrameHeight());

	_status.curHp = 100;
	_status.curSp = 100;
	_status.curExp = 0;
	_status.maxHp = _status.curHp;
	_status.maxSp = _status.curSp;
	_status.maxExp = 100;
	_status.lv = 1;
	_status.gold = 0;
	_status.iAtt = 10;
	_status.iDef = 10;
	_status.iInt = 10;
	_status.iMen = 10;
	_status.iAgi = 10;
	_status.iLuk = 10;

	_UIBar = new ProgressBar;
	_UIBar->init(_status.maxHp, _status.maxSp);

	_isLeft = false;
	_isLive = true;

	_speed = 2;

	return S_OK;
}

void Player::release(void)
{
	_UIBar->release();
	SAFE_DELETE(_UIBar);
}

void Player::update(void)
{
		_UIBar->update();
		IMG("Num_UI")->setFrameX(11);//, getMemDC(), 205, 15);
		IMG("Num_UI")->setFrameY(1);// IMG("NUM_UI", getMemDC(), 510, 15);

	// 포션 적용 시 ( 인벤토리 작성 후 getPotionGauge() 할 것
	if(KEYMANAGER->isOnceKeyDown(VK_F10))
	{
		int healGayge = 100;
		_UIBar->setHpGauge(healGayge, _status.maxHp);
		_UIBar->setSpGauge(healGayge, _status.maxSp);

	}
	if (_isLive)
	{
		
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_isLeft = true;
			_pos.x -= _speed;

			IMG("p_run_9")->setFrameX(2);
			IMG("p_run_9")->setFrameY(0);

		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_isLeft = false;
			_pos.x += _speed;

			IMG("p_run_9")->setFrameX(2);
			IMG("p_run_9")->setFrameY(1);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_isLeft = true;

			_pos.y -= _speed;
			IMG("p_run_12")->setFrameX(1);
			IMG("p_run_12")->setFrameY(1);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_isLeft = true;

			_pos.y += _speed;
			IMG("p_run_6")->setFrameX(2);
			IMG("p_run_6")->setFrameY(1);
		}
	
		_rcPlayer = RectMakeCenter(_pos.x, _pos.y, IMG("p_idle_6")->getFrameWidth(), IMG("p_idle_6")->getFrameHeight());
	}
}

void Player::render(void)
{

		_UIBar->render();
		IMGFR("Num_UI", getMemDC(), 205, 15);
		IMGFR("Num_UI", getMemDC(), 510, 15);

	if (_isLive)
	{
		float left = _rcPlayer.left - _rcCamera.left;
		float top = _rcPlayer.top - _rcCamera.top;

		IMGR("p_idle_6", getMemDC(), left, top);

		
	}
}


float Player::getPlayerPosX()
{
	return _pos.x;
}

float Player::getPlayerPosY()
{
	return _pos.y;
}

void Player::setPlayerPosX(float x)
{
	_pos.x = x;
}
void Player::setPlayerPosY(float y)
{
	_pos.y = y;
}

RECT Player::getPlayerRect()
{
	return _rcPlayer;
}

void Player::setCameraRect(RECT rc)
{
	_rcCamera = rc;
}
