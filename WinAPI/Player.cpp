#include "Stdafx.h"
#include "Player.h"
#include "STATE.h"
#include "StateBase.h"
#include "StateAttack.h"


HRESULT Player::init(void)
{
#pragma region �÷��̾� ������ ����� ���� 
	// �ε� ������ �ϱ�.....
	_player.face = IMG("p_face");
	_state = PLAYERSTATE::IDLE;
	_direction = PLAYERDIRECTION::DOWN;
	_weapon.type = WEAPONTYPE::SWORD;

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

	// �� ���� �߰� �ʿ�
	_abyss.abyss = 1;
	_abyss.stage = 1;

	// �ӽ� �����۳ѹ�(�����������̹��� ��Ʈ���� y������)
	itemNum = 0;

	// ������, ����-�������� �Ա��� �°� ���� �����ϴ� �Լ�
	// ���� �� ������ ����� �ٲ㵵 ������ �� 
	// �ʿ��� ���� : ����Ÿ��, �����ȣ, ĳ���͹���
	inStageWeaponSetting();

#pragma endregion

	_player.speed = 10;
	if (_weapon.type == WEAPONTYPE::SPEAR) _player.image=IMG("p_idle_twoHand");
	else _player.image = IMG("p_idle_oneHand");
		
	// �÷��̾��� ���� �޾Ƽ�
	_player.frameX = 0;
	_player.frameY = static_cast<int>(_direction);
	_player.movePosX = _player.drawPosX = LSCENTER_X;
	_player.movePosY = _player.drawPosY = CENTER_Y;
	_player.width  = _player.image->getFrameWidth();
	_player.height = _player.image->getFrameHeight();
	// ���� üũ �� ��. 
	_player.rc = RectMakeCenter(_player.movePosX, _player.movePosY, _player.width, _player.height);
	//_player.rc = RectMakeCenter(_player.drawPosX, _player.drawPosY, _player.width, _player.height);

	_camera.playerLeft = _camera.playerTop = 0;
	_camera.weaponLeft = _camera.weaponTop = 0;

	// Down-Idle
	// ���� ������ ������Ʈ
	// ���� ���� ���⿡ �°� ����
	_weapon.movePosX = _weapon.drawPosX = _player.movePosX;
	_weapon.movePosY = _weapon.drawPosY = _player.movePosY ;

	_weapon.width  = _weapon.image->getFrameWidth();
	_weapon.height = _weapon.image->getFrameHeight();
	_weapon.rc = RectMakeCenter(_weapon.movePosX, _weapon.movePosY, _weapon.width, _weapon.height);
	//_weapon.rc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _weapon.width, _weapon.height);



	// bitset setting - isLive
	_isStateCheck.reset();
	_isStateCheck.set(4);

	// �������� (�����·� ����)
	_pStatePattern = IdleState::getInstance();
	setPlayerState(_pStatePattern);
	

	return S_OK;
}

void Player::release(void)
{
	_pStatePattern->stateRelease();
}

void Player::update(void)
{

	inStageWeaponSetting();

	// state pattern update
	stateUpdate();
	
	// hit,dead �����϶��� Y������ ���� ����.
	if (_state == PLAYERSTATE::BEHIT || _state == PLAYERSTATE::DEAD) {}
	else _player.frameY = static_cast<int>(_direction);
	


}

void Player::render(void)
{
	// ĳ����, ���� ī�޶� ����
	_camera.playerLeft = _player.rc.left - _camera.rc.left;
	_camera.playerTop  = _player.rc.top  - _camera.rc.top;
	_camera.weaponLeft = _weapon.rc.left - _camera.rc.left;
	_camera.weaponTop  = _weapon.rc.top  - _camera.rc.top;



	// ���¿� ���� ����
	//stateRender();

	_player.image->frameRender(getMemDC(), _camera.playerLeft, _camera.playerTop, _player.frameX, _player.frameY);
	_weapon.image->frameRender(getMemDC(), _camera.weaponLeft, _camera.weaponTop, _weapon.frameX, _weapon.frameY);

	if(KEYOKD('P'))
	{
	cout <<  " ���� X ������ : " << _player.frameX << endl;
	cout << " ���� Y ������ : " << _player.frameY << endl;
	}
	//rcMake(getMemDC(), _rcPlayer);
	//rcMake(getMemDC(), _weapon.rc);

}

void Player::inStageWeaponSetting( )
{
	// ���� ���� �Ǵ� ���� ���� �� 
	switch (_weapon.type)
	{
	case  WEAPONTYPE::SWORD:
		_weapon.image = IMG("weapon_sword");
		_weapon.frameX = 1;
		break;
	case  WEAPONTYPE::AX:
		_weapon.image = IMG("weapon_ax");
		if (   _direction == PLAYERDIRECTION::UP
			|| _direction == PLAYERDIRECTION::DOWN)
		{
			_weapon.frameX = 14;
		}
		if (   _direction == PLAYERDIRECTION::LEFT
			|| _direction == PLAYERDIRECTION::LEFTUP
			|| _direction == PLAYERDIRECTION::LEFTDOWN)
		{
			_weapon.frameX = 1;
		}
		if (_direction == PLAYERDIRECTION::RIGHT
			|| _direction == PLAYERDIRECTION::RIGHTUP
			|| _direction == PLAYERDIRECTION::RIGHTDOWN)
		{
			_weapon.frameX = 26;
		}
		break;
	case  WEAPONTYPE::SPEAR:
		_weapon.image = IMG("weapon_spear");
		break;
	}

	// ����ѹ��� ���� �����Ʈ���� ������ ������Ʈ
	_weapon.frameY = itemNum;

}


// ���� ����
void Player::setPlayerState(STATE* state)
{
	// �ڵ����� ����
	this->_pStatePattern = state;
	_pStatePattern->stateInit(this);
}

// �ൿ ����
void Player::stateUpdate()
{
	// ������ ��� üũ 
	if (_direction == PLAYERDIRECTION::LEFT 
		|| _direction == PLAYERDIRECTION::LEFTUP 
		|| _direction == PLAYERDIRECTION::LEFTDOWN)
	{
		_isStateCheck.set(0);
	}
	else _isStateCheck.reset(0);

	// playerDirection = DOWN : �÷��̾ ���� �Ʒ��� ����
	if (_direction == PLAYERDIRECTION::DOWN
		|| _direction == PLAYERDIRECTION::LEFTDOWN
		|| _direction == PLAYERDIRECTION::RIGHTDOWN)
	{
		_isStateCheck.set(5);
	}
	else _isStateCheck.reset(5);

	// �������� ������Ʈ 
	_pStatePattern->stateUpdate(this);

	// ���¿� ���� �÷��̾� �̹��� ������Ʈ 
	switch (_state)
	{
	case PLAYERSTATE::IDLE:
		//if		(_weapon.type == WEAPONTYPE::SWORD)		_player.image = IMG("p_idle_oneHand");
		//else if (_weapon.type == WEAPONTYPE::AX)	    _player.image = IMG("p_idle_oneHand");
		//else if (_weapon.type == WEAPONTYPE::SPEAR)		_player.image = IMG("p_idle_twoHand");
		//_player.image->setFrameX(itemNum);
		break;
	case PLAYERSTATE::MOVE:
		_player.image = IMG("p_move");
		_weapon.image = IMG("weapon_none");
		break;
	case PLAYERSTATE::BEHIT:
		_player.image = IMG("p_hit");
		_weapon.image = IMG("weapon_none");
		_player.image->setFrameX(_player.frameX);
		if(_isStateCheck.test(0)) _player.image->setFrameY(0);
		else _player.image->setFrameY(1);

		break;
	case PLAYERSTATE::DEAD:
		_player.image = IMG("p_dead");
		_weapon.image = IMG("weapon_none");
		_player.image->setFrameX(_player.frameX);
		if (_isStateCheck.test(0)) _player.image->setFrameY(0);
		else _player.image->setFrameY(1);

		break;
	case PLAYERSTATE::ONEHANDCOMBO_ONE:
		_player.image = IMG("p_oneHandCombo_01");
		if (_weapon.type == WEAPONTYPE::SWORD) _weapon.image= IMG("weapon_sword");
		else if (_weapon.type == WEAPONTYPE::AX) _weapon.image = IMG("weapon_ax");
		break;
	case PLAYERSTATE::ONEHANDCOMBO_TWO:
		_player.image = IMG("p_oneHandCombo_02");
		if (_weapon.type == WEAPONTYPE::SWORD) _weapon.image = IMG("weapon_sword");
		else if (_weapon.type == WEAPONTYPE::AX) _weapon.image = IMG("weapon_ax");

		break;
	case PLAYERSTATE::ONEHANDCOMBO_THREE:
		_player.image = IMG("p_oneHandCombo_03");
		if (_weapon.type == WEAPONTYPE::SWORD) _weapon.image = IMG("weapon_sword");
		else if (_weapon.type == WEAPONTYPE::AX) _weapon.image = IMG("weapon_ax");

		break;
	case PLAYERSTATE::TWOHANDCOMBO_ONE:
		_player.image = IMG("p_twoHandCombo_01");
		if (_weapon.type == WEAPONTYPE::SPEAR) _weapon.image = IMG("weapon_spear");

		break;
	case PLAYERSTATE::TWOHANDCOMBO_TWO:
		_player.image = IMG("p_twoHandCombo_02");
		if (_weapon.type == WEAPONTYPE::SPEAR) _weapon.image = IMG("weapon_spear");


		break;
	case PLAYERSTATE::SKILL_SOULCAPTURE:
		break;
	case PLAYERSTATE::SKILL_SPEARSTRIKE:
		break;

	}

	// �÷��̾� ī�޶� �Ⱥ��� !!!!!
	// �÷��̾� + ���� ��ġ ������Ʈ (���·� �̰��� �� )
	_weapon.rc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _weapon.width, _weapon.height);



	// ���·� �̰�
//	_timeCount++;
//	if (_timeCount % 10 == 0) _player.frameX++;
	if (_state == PLAYERSTATE::MOVE)
	{
	//	if(_player.frameX >= 3) _player.frameX = 0;
	}
	else if (_state == PLAYERSTATE::BEHIT || _state == PLAYERSTATE::DEAD)
	{
		_player.frameX = 0;
	}
	else if (_state == PLAYERSTATE::SKILL_SOULCAPTURE)
	{
		if (_player.frameX >= 2) _player.frameX = 0;
	}
	else
	{
		if (_player.frameX >= 1) _player.frameX = 0;
	}



}

// �ൿ ����
void Player::stateRender()
{
	_pStatePattern->stateRender(this);
}






