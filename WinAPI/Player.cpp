#include "Stdafx.h"
#include "Player.h"
#include "STATE.h"


HRESULT Player::init(void)
{
	// 로드 데이터 하기.....
	_faceImg = IMG("p_face");
	_playerState = PLAYERSTATE::IDLE;
	_playerDirection = PLAYERDIRECTION::DOWN;
	_weaponType = WEAPONTYPE::SWORD;

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


	_speed = 10;

	_tempFrameX = _tempFrameY = _tempCount = 0;


	// 상태패턴 
	// 초기에는 대기상태로 시작
	_pStatePattern = IdleState::getInstance();

	switch (_weaponType)
	{
	case  WEAPONTYPE::SWORD:
		_playerImage = IMG("p_idle_oneHand");
		_weaponimage = IMG("weapon_sword");
		break;
	case  WEAPONTYPE::AX:
		_playerImage = IMG("p_idle_oneHand");
		_weaponimage = IMG("weapon_ax");
		break;
	case  WEAPONTYPE::SPEAR :
		_playerImage = IMG("p_idle_twoHand");
		_weaponimage = IMG("weapon_spear");
		break;
	}

	// 플레이어의 값을 받아서
	_frameX = 0;
	_frameY = static_cast<int>(_playerDirection);
	_pos.x = LSCENTER_X;
	_pos.y = CENTER_Y;
	_width = _playerImage->getFrameWidth();
	_height = _playerImage->getFrameHeight();
	_rcPlayer = RectMakeCenter(_pos.x, _pos.y, _width, _height);



	_playerWeapon.frameX = 0;
	_playerWeapon.frameY = 0;
	_playerWeapon.posX = _pos.x-50; 
	_playerWeapon.posY = _pos.y-40;
	_playerWeapon.rc = RectMakeCenter(_playerWeapon.posX, _playerWeapon.posY, _weaponimage->getFrameWidth(), _weaponimage->getFrameHeight());

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
	
	// 좌
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_pos.x -= _speed;
		_playerDirection = PLAYERDIRECTION::LEFT;

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_playerDirection = PLAYERDIRECTION::LEFTUP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_playerDirection = PLAYERDIRECTION::LEFTDOWN;
		}
	}
	// 우
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isStateCheck.reset(0);

		_pos.x += _speed;
		_playerDirection = PLAYERDIRECTION::RIGHT;

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_playerDirection = PLAYERDIRECTION::RIGHTUP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_playerDirection = PLAYERDIRECTION::RIGHTDOWN;
		}
	}
	// 위
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pos.y -= _speed;
		_playerDirection = PLAYERDIRECTION::UP;

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_playerDirection = PLAYERDIRECTION::LEFTUP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_isStateCheck.reset(0);
			_playerDirection = PLAYERDIRECTION::RIGHTUP;
		}
	}
	// 아래
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_pos.y += _speed;
		_playerDirection = PLAYERDIRECTION::DOWN;

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_playerDirection = PLAYERDIRECTION::LEFTDOWN;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_isStateCheck.reset(0);
			_playerDirection = PLAYERDIRECTION::RIGHTDOWN;
		}
	}




}

void Player::render(void)
{
	float left = _rcPlayer.left - _rcCamera.left;
	float top = _rcPlayer.top - _rcCamera.top;
	float weaponLeft = _playerWeapon.rc.left - _rcCamera.left;
	float weaponTop = _playerWeapon.rc.top - _rcCamera.top;

	_frameY = static_cast<int>(_playerDirection);


		// 플레이어가 무기 위에 렌더
	if (_playerDirection == PLAYERDIRECTION::UP || _playerDirection == PLAYERDIRECTION::LEFTUP
		|| _playerDirection == PLAYERDIRECTION::RIGHTUP)
	{
		// 달리기, 피격, 죽음 상태
		if (_isStateCheck.test(1) || _isStateCheck.test(3) || !_isStateCheck.test(4))
		{		}
		else _weaponimage->frameRender(getMemDC(), weaponLeft, weaponTop, 1, _playerWeapon.frameY);
		
		_playerImage->frameRender(getMemDC(), left, top, _frameX, _frameY);
	}

		// 플레이어가 무기 아래에 렌더
	if (_playerDirection == PLAYERDIRECTION::DOWN || _playerDirection == PLAYERDIRECTION::LEFTDOWN
		|| _playerDirection == PLAYERDIRECTION::RIGHTDOWN)
	{
		_playerImage->frameRender(getMemDC(), left, top, _frameX, _frameY);

		// 달리기, 피격, 죽음 상태
		if (_isStateCheck.test(1) || _isStateCheck.test(3) || !_isStateCheck.test(4))
		{		}
		else _weaponimage->frameRender(getMemDC(), weaponLeft, weaponTop, 1, _playerWeapon.frameY);
	}

	if(KEYOKD('P'))
	{
	cout <<  " 현재 X 프레임 : " << _frameX << endl; 
	cout << " 현재 Y 프레임 : " << _frameY << endl;
	}
	//rcMake(getMemDC(), _rcPlayer);
	//rcMake(getMemDC(), _playerWeapon.rc);
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
	// 자동으로 실행
	this->_pStatePattern = state;
	_pStatePattern->stateInit(this);
}

// 행동 세팅
void Player::stateUpdate()
{
	_pStatePattern->stateUpdate(this);

	// 플레이어 위치 업데이트 
	_width = _playerImage->getFrameWidth();
	_height = _playerImage->getFrameHeight();
	_rcPlayer = RectMakeCenter(_pos.x, _pos.y, _width, _height);

	// 무기 위치 업데이트
	_playerWeapon.posX = _pos.x - 22;
	_playerWeapon.posY = _pos.y - 30;
	_playerWeapon.rc = RectMakeCenter(_playerWeapon.posX, _playerWeapon.posY, _weaponimage->getFrameWidth(), _weaponimage->getFrameHeight());

	// 왼쪽은 상시 체크 
	if (_playerDirection == PLAYERDIRECTION::LEFT      ||
		_playerDirection == PLAYERDIRECTION::LEFTUP    ||
		_playerDirection == PLAYERDIRECTION::LEFTDOWN  )
	{
		_isStateCheck.set(0);
	}
	else _isStateCheck.reset(0);

	
	_timeCount++;
	if (_timeCount % 10 == 0) _frameX++;
	if (_playerState == PLAYERSTATE::MOVE)
	{
		if(_frameX >= 3) _frameX = 0;
	}
	else if (_playerState == PLAYERSTATE::BEHIT || _playerState == PLAYERSTATE::DEAD)
	{
		_frameX = 0;
	}
	else if (_playerState == PLAYERSTATE::SKILL_SOULCAPTURE)
	{
		if (_frameX >= 2) _frameX = 0;
	}
	else
	{
		if (_frameX >= 1) _frameX = 0;
	}



	// 플레이어 이미지 업데이트 
	switch (_playerState)
	{
	case PLAYERSTATE::IDLE:
		if (_weaponType == WEAPONTYPE::SWORD)
		{
			_playerImage = IMG("p_idle_oneHand");
			_weaponimage = IMG("weapon_sword");
		}
		else if (_weaponType == WEAPONTYPE::AX)
		{
			_playerImage = IMG("p_idle_oneHand");
			_weaponimage = IMG("weapon_ax");
		}
		else if (_weaponType == WEAPONTYPE::SPEAR)
		{
			_playerImage = IMG("p_idle_twoHand");
			_weaponimage = IMG("weapon_ax");
		}
		_playerImage->setFrameX(0);
		break;
	case PLAYERSTATE::MOVE:
		_playerImage = IMG("p_move");
		_playerImage->setFrameX(_frameX);
		break;
	case PLAYERSTATE::BEHIT:
		_playerImage = IMG("p_hit");

		break;
	case PLAYERSTATE::DEAD:
		_playerImage = IMG("p_dead");
		break;
	case PLAYERSTATE::ONEHANDCOMBO_ONE:
		_playerImage = IMG("p_oneHandCombo_01");
		break;
	case PLAYERSTATE::ONEHANDCOMBO_TWO:
		_playerImage = IMG("p_oneHandCombo_02");
		break;
	case PLAYERSTATE::ONEHANDCOMBO_THREE:
		_playerImage = IMG("p_oneHandCombo_03");

		break;
	case PLAYERSTATE::TWOHANDCOMBO_ONE:
		_playerImage = IMG("p_twoHandCombo_01");

		break;
	case PLAYERSTATE::TWOHANDCOMBO_TWO:
		_playerImage = IMG("p_twoHandCombo_02");

		break;
	case PLAYERSTATE::SKILL_SOULCAPTURE:
		break;
	case PLAYERSTATE::SKILL_SPEARSTRIKE:
		break;

	}


}






