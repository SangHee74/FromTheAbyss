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


	// ���̽� �δ����� �������� �����Ű�����..
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


	// �������� 
	// �ʱ⿡�� �����·� ����
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
	// setState �Լ� ����� ���� ���¸� �켱 Ż���ϵ��� �����߽��ϴ�
	if (_pStatePattern)_pStatePattern->exitState();

	_playerState = state;

	// �� ���¿� ���� ��ü ����
	switch (state)
	{ 
	case PLAYERSTATE::IDLE:
		_pStatePattern = new Idle;	break;
	case PLAYERSTATE::MOVE:
		_pStatePattern = new Move;	break;
	}
	_pStatePattern->linkMemberAdress(this);
		// ������ ���¿��� �ٸ� ���·� �ű涧 ����� ������ ��ũ

	_pStatePattern->enterState();
		// ���� �Ϸ��� ������ ���� �� �ش� ���¿� ����
}


//���¿� ���� �̹����� ã�� ������ִ� �Լ�
void Player::stateUpdate2()
{
	//_count++;
	//if (_count % 5 == 0)
	{
		switch (_playerState)
		{
		case PLAYERSTATE::IDLE:
			// ������ ������ �̹����� ���⿡ ���� ����� �����ִ� �ε��� ������ ���� Ȥ�� �����ϰ�,
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


// ���� ����

// ���� ����



// �ൿ ����






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


// ���� ����
void Player::setPlayerState(STATE* state)
{
	this->_pStatePattern = state;
}

// �ൿ ����
void Player::stateUpdate()
{
	_pStatePattern->stateInit(this);
	_pStatePattern->stateUpdate(this);

	_width = _playerImg->getWidth();
	_height = _playerImg->getHeight();

	_rcPlayer = RectMakeCenter(_pos.x, _pos.y, _width, _height);


#pragma region ĳ���� �ӽ� ī��Ʈ-������
	// �ӽ� ī��Ʈ - ������
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
	if (_isStateCheck.test(2)) // ���ݽ��ӽ�������
	{
		if (_tempCount % 15 == 0)
			_tempFrameX++;
		if (_tempFrameX >= 2) _tempFrameX = 0;
	}
#pragma endregion


}

#endif // STATEPATTERN


