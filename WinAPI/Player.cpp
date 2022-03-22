#include "Stdafx.h"
#include "Player.h"


HRESULT Player::init(void)
{

	_pos.x = LSCENTER_X;
	_pos.y = CENTER_Y;
	w = IMG("p_idle_6")->getWidth();
	h = IMG("p_idle_6")->getHeight();
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

	_abyss = 1;
	_stage = 1;

	_isLeft = false;
	_isLive = true;

	_speed = 2;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{

	
	if (_isLive)
	{
		
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_isLeft = true;
			_pos.x -= _speed;

			IMG("p_run_9")->setFrameX(2);
			IMG("p_run_9")->setFrameY(0);

		}
		 if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_isLeft = false;
			_pos.x += _speed;

			IMG("p_run_9")->setFrameX(2);
			IMG("p_run_9")->setFrameY(1);
		}
		 if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_isLeft = true;

			_pos.y -= _speed;
			IMG("p_run_12")->setFrameX(1);
			IMG("p_run_12")->setFrameY(1);
		}
		 if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_isLeft = true;

			_pos.y += _speed;
			IMG("p_run_6")->setFrameX(2);
			IMG("p_run_6")->setFrameY(1);
		}
	

		 // 나중에 상태패턴에서 각 이미지의 길이, 높이를 받아서 해야겠다.
		 // w,h 안쓰니까 초점이 잘 안맞음
		 w = IMG("p_idle_6")->getWidth();
		 h = IMG("p_idle_6")->getHeight();
		_rcPlayer = RectMakeCenter(_pos.x, _pos.y,w,h);
	}
}

void Player::render(void)
{

		
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

void Player::setAbyss(int num)
{
	_abyss = num;
}

void Player::setStage(int num)
{
	_stage = num;
}

