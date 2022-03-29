#include "Stdafx.h"
#include "Player.h"
#include "STATE.h"


HRESULT Player::init(void)
{
	if(_playerType==ONE) _faceImg = IMG("p_sum_1R");
	_playerState = PLAYERSTATE::IDLE;
	_playerDirection = PLAYERDIRECTION::DOWN;

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
	_isRunnig = _isAttacking = false;

	_speed = 2;

	_tempFrameX = _tempFrameY = _tempCount = 0;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	_tempCount++;
	
	if (_isLive)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !_isRunnig)
		{
			_isLeft = true;
			_pos.x -= _speed;

			_playerDirection = PLAYERDIRECTION::LEFT;
			_playerState = PLAYERSTATE::MOVE;


			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_playerDirection = PLAYERDIRECTION::LEFTUP;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_playerDirection = PLAYERDIRECTION::LEFTDOWN;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !_isRunnig)
		{
			_isLeft = false;
			_pos.x += _speed;

			_playerDirection = PLAYERDIRECTION::RIGHT;
			_playerState = PLAYERSTATE::MOVE;



			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_playerDirection = PLAYERDIRECTION::RIGHTUP;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_playerDirection = PLAYERDIRECTION::RIGHTDOWN;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && !_isRunnig)
		{
			_pos.y -= _speed;

			_playerDirection = PLAYERDIRECTION::UP;
			_playerState = PLAYERSTATE::MOVE;


			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_playerDirection = PLAYERDIRECTION::LEFTUP;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_playerDirection = PLAYERDIRECTION::RIGHTUP;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !_isRunnig)
		{
			_pos.y += _speed;

			_playerDirection = PLAYERDIRECTION::DOWN;
			_playerState = PLAYERSTATE::MOVE;


			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_playerDirection = PLAYERDIRECTION::LEFTDOWN;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_playerDirection = PLAYERDIRECTION::RIGHTDOWN;
			}
		}

		if (KEYOKU(VK_LEFT) || KEYOKU(VK_UP)|| KEYOKU(VK_DOWN))
		{
			_isRunnig = false;
			_playerState = PLAYERSTATE::IDLE;
		}
		if (KEYOKU(VK_RIGHT))
		{
			_isRunnig = false;
			_playerState = PLAYERSTATE::IDLE;
			_isLeft = false;
		}

		if (KEYMANAGER->isStayKeyDown('X') && !_isAttacking)
		{
			_playerState = PLAYERSTATE::ATT;
		}
		if (KEYOKU('X'))
		{
			_isAttacking = false;
			_playerState = PLAYERSTATE::IDLE;
		}


		// 나중에 상태패턴에서 각 이미지의 길이, 높이를 받아서 해야겠다.
		// w,h 안쓰니까 초점이 잘 안맞음
		w = IMG("p_idle_6")->getWidth();
		h = IMG("p_idle_6")->getHeight();
		_rcPlayer = RectMakeCenter(_pos.x, _pos.y, w, h);

	}
	else
	{
		w = IMG("p_down")->getWidth();
		h = IMG("p_down")->getHeight();
		_rcPlayer = RectMakeCenter(_pos.x, _pos.y, w, h);
		_playerState = PLAYERSTATE::DEAD;
	}

	if (this->_status.curHp <= 0) _isLive = false;

	// 임시 카운트 - 프레임
	if (_isLeft)
	{
		_tempFrameY = 0;
	}
	else _tempFrameY = 1;

	if (_tempCount % 10 == 0)
	{
		if (_isLeft)
		{
			_tempFrameX++;
			if (_tempFrameX >= 3) _tempFrameX = 0;
		}
		else
		{
			_tempFrameX--;
			if (_tempFrameX < 0) _tempFrameX = 3;
		}

	}
	if (_isAttacking) // 공격시임시프레임
	{
		if (_tempCount % 15== 0)
		_tempFrameX++;
		if (_tempFrameX >= 2) _tempFrameX = 0;
	}
		
}

void Player::render(void)
{
	float left = _rcPlayer.left - _rcCamera.left;
	float top = _rcPlayer.top - _rcCamera.top;

		
	if (_isLive)
	{
		if (_playerState == PLAYERSTATE::IDLE)
		{
			
			IMGFR("p_idle", getMemDC(), left, top, static_cast<int>(_playerDirection), 1);

		}
		else if (_playerState == PLAYERSTATE::MOVE)
		{
			if (_playerDirection == PLAYERDIRECTION::UP)
			{
				IMGFR("p_run_12", getMemDC(), left, top, _tempFrameX, _tempFrameY);
			}
			if (_playerDirection == PLAYERDIRECTION::DOWN)
			{
				IMGFR("p_run_6", getMemDC(), left, top, _tempFrameX, _tempFrameY);
			}
			if ((_playerDirection == PLAYERDIRECTION::LEFT) || (_playerDirection == PLAYERDIRECTION::RIGHT))
			{
				IMGFR("p_run_9", getMemDC(), left, top, _tempFrameX, _tempFrameY);
			}
			if ((_playerDirection == PLAYERDIRECTION::LEFTUP) || (_playerDirection == PLAYERDIRECTION::RIGHTUP))
			{
				IMGFR("p_run_11", getMemDC(), left, top, _tempFrameX, _tempFrameY);
			}
			if ((_playerDirection == PLAYERDIRECTION::LEFTDOWN) || (_playerDirection == PLAYERDIRECTION::RIGHTDOWN))
			{
				IMGFR("p_run_7", getMemDC(), left, top, _tempFrameX, _tempFrameY);
			}

		}
		else if (_playerState == PLAYERSTATE::ATT)
		{
			IMGFR("p_att_ax_6", getMemDC(), left, top, _tempFrameX, _tempFrameY);
		}
	}
	else IMGR("p_down", getMemDC(), left, top);

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


// 상태패턴
// 상태 세팅
void Player::setPlayerState(STATE* state)
{
	this->_pState = state;
}

// 행동 세팅
void Player::idle()
{
	_pState->idle(this);
}

void Player::move()
{
	_pState->move(this);
}

void Player::attack()
{
	_pState->attack(this);
}

void Player::beHit()
{
	_pState->beHit(this);
}


