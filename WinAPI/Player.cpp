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


	_isStateCheck.reset();
	_isStateCheck.set(5);

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

	_playerWeapon.image->frameRender(getMemDC(),left,top+20, 1,1); 
	
}


#ifdef STATEPATTERN



void Player::setState(PLAYERSTATE state)
{
	// setState 함수 실행시 기존 상태를 우선 탈출하도록 설정했습니다
	if (_pStatePattern)_pStatePattern->exitState();

	_playerState = state;

	// 각 상태에 따른 객체 생성
	switch (state)
	{ 
	case PLAYERSTATE::IDLE:
		_pStatePattern = new Idle;	break;
	case PLAYERSTATE::MOVE:
		_pStatePattern = new Move;	break;
	}
	_pStatePattern->linkMemberAdress(this);
		// 각각의 상태에서 다른 상태로 옮길때 사용할 참조용 링크

	_pStatePattern->enterState();
		// 위의 일련의 과정이 끝난 후 해당 상태에 돌입
}


//상태에 따라 이미지를 찾고 재생해주는 함수
void Player::stateUpdate2()
{
	//_count++;
	//if (_count % 5 == 0)
	{
		switch (_playerState)
		{
		case PLAYERSTATE::IDLE:
			// 공격을 제외한 이미지는 방향에 따라 재생을 도와주는 인덱스 변수가 증가 혹은 감소하고,
			_playerImg = IMG("p_idle");
			_playerImg->setFrameY(1);
			_playerImg->setFrameX(static_cast<int>(_playerDirection));
			break;
		case PLAYERSTATE::MOVE:


			break;
		}
	}

}

void Player::stateRender()
{
	float left = _rcPlayer.left - _rcCamera.left;
	float top = _rcPlayer.top - _rcCamera.top;

	switch (_playerState)
	{
	case PLAYERSTATE::IDLE:
		IMGFR("p_idle", getMemDC(),left,top, static_cast<int>(_playerDirection), 1);
		//IMGFR("p_idle", getMemDC(), left, top, static_cast<int>(_playerDirection), 1);
		break;
	case PLAYERSTATE::MOVE:
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


// 상태 패턴

// 상태 세팅



// 행동 세팅






#else



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
}

// 행동 세팅
void Player::stateUpdate()
{
	_pStatePattern->stateInit(this);
	_pStatePattern->stateUpdate(this);

	_width = _playerImg->getWidth();
	_height = _playerImg->getHeight();

	_rcPlayer = RectMakeCenter(_pos.x, _pos.y, _width, _height);


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

#endif // STATEPATTERN


