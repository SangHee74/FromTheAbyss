#include "Stdafx.h"
#include "Player.h"
#include "STATE.h"


HRESULT Player::init(void)
{
	_faceImg = IMG("p_face");
	_playerState = PLAYERSTATE::IDLE;
	_playerDirection = PLAYERDIRECTION::DOWN;
	_weaponType = WEAPONTYPE::SWORD;
	
	_playerImg = IMG("p_idle_oneHand");
	_pos.x = LSCENTER_X;
	_pos.y = CENTER_Y;
	_width = _playerImg->getWidth();
	_height = _playerImg->getHeight();
	_rcPlayer = RectMakeCenter(_pos.x, _pos.y, _width, _height);


	// 제이슨 로더에서 가져오면 좋을거같은데..
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


	// isLive on
	_isStateCheck.reset();
	_isStateCheck.set(4);


	_speed = 2;

	_tempFrameX = _tempFrameY = _tempCount = 0;


	// 상태패턴 
	// 초기에는 대기상태로 시작
	_pStatePattern = IdleState::getInstance();


	return S_OK;
}

void Player::release(void)
{
	_pStatePattern->stateRelease();
}

void Player::update(void)
{
	_tempCount++;
	
	// state pattern update
	stateUpdate();

	


}

void Player::render(void)
{
	float left = _rcPlayer.left - _rcCamera.left;
	float top = _rcPlayer.top - _rcCamera.top;

	 
	if (!_isStateCheck.test(5))
	{
		_playerImg->render(getMemDC(), left, top);
	}
	else
	{
		_playerImg->frameRender(getMemDC(), left, top, _frameX, _frameY);
	}

	// 프레임값 임시
	_weaponimage->frameRender(getMemDC(),left,top+20, 1,1);
	
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


// 상태 세팅
void Player::setPlayerState(STATE* state)
{
	this->_pStatePattern = state;
	_pStatePattern->stateInit(this);

	

}

// 행동 세팅
void Player::stateUpdate()
{
	_pStatePattern->stateUpdate(this);

	_width = _playerImg->getWidth();
	_height = _playerImg->getHeight();

	_rcPlayer = RectMakeCenter(_pos.x, _pos.y, _width, _height);

	// 왼쪽은 상시 체크 
	if (_playerDirection == PLAYERDIRECTION::LEFT      ||
		_playerDirection == PLAYERDIRECTION::LEFTUP    ||
		_playerDirection == PLAYERDIRECTION::LEFTDOWN  )
	{
		_isStateCheck.set(0);
	}
	else _isStateCheck.reset(0);



#pragma region 캐릭터 임시 카운트-프레임
	// 임시 카운트 - 프레임
	if (_isStateCheck.test(0))
	{
		_tempFrameY = 0;
	}
	else _tempFrameY = 1;

	if (_tempCount % 10 == 0)
	{
		if (_isStateCheck.test(0))
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
	if (_isStateCheck.test(2)) // 공격시임시프레임
	{
		if (_tempCount % 15 == 0)
			_tempFrameX++;
		if (_tempFrameX >= 2) _tempFrameX = 0;
	}
#pragma endregion


}




