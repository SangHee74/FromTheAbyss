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
	_weapon.type = WEAPONTYPE::AX;

	_tempIMG = IMG("skill_utill_Icon");

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
	_player.moveRc = RectMakeCenter(_player.movePosX, _player.movePosY, _player.width, _player.height);

	_camera.playerLeft = _camera.playerTop = 0;
	_camera.weaponLeft = _camera.weaponTop = 0;

	// Down-Idle
	// ���� ������ ������Ʈ
	// ���� ���� ���⿡ �°� ����
	_weapon.movePosX = _weapon.drawPosX = _player.movePosX;
	_weapon.movePosY = _weapon.drawPosY = _player.movePosY ;

	_weapon.width  = _weapon.image->getFrameWidth();
	_weapon.height = _weapon.image->getFrameHeight();
	_weapon.moveRc = RectMakeCenter(_weapon.movePosX, _weapon.movePosY, _weapon.width, _weapon.height);
	_weapon.drawRc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _weapon.width, _weapon.height);


	// bitset setting - isLive
	_isStateCheck.reset();
	_isStateCheck.set(4);

	// �������� (�����·� ����)
	// ĳ���� ����, ����Ÿ��, �����ȣ(itemNum)
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
	if (_state == PLAYERSTATE::HIT || _state == PLAYERSTATE::DEAD) {}
	else _player.frameY = static_cast<int>(_direction);
	
}

void Player::render(void)
{
	// ĳ����, ���� ī�޶� ����
	_camera.playerLeft = _player.drawRc.left - _camera.rc.left;
	_camera.playerTop = _player.drawRc.top - _camera.rc.top;
	_camera.weaponLeft = _weapon.drawRc.left - _camera.rc.left;
	_camera.weaponTop = _weapon.drawRc.top - _camera.rc.top;


	if (_isStateCheck.test(5))
	{
		_player.image->frameRender(getMemDC(), _camera.playerLeft, _camera.playerTop, _player.frameX, _player.frameY);
		_weapon.image->frameRender(getMemDC(), _camera.weaponLeft, _camera.weaponTop, _weapon.frameX, _weapon.frameY);
	}
	if (! _isStateCheck.test(5))
	{
		_weapon.image->frameRender(getMemDC(), _camera.weaponLeft, _camera.weaponTop, _weapon.frameX, _weapon.frameY);
		_player.image->frameRender(getMemDC(), _camera.playerLeft, _camera.playerTop, _player.frameX, _player.frameY);
	}

	if(KEYOKD('P'))
	{
	//cout << " ���� Y ������ : " << _player.frameY << endl;
	}
	//rcMake(getMemDC(), _player.moveRc);
	//rcMake(getMemDC(), _weapon.moveRc);


	//���μ��� 4px �簢��
	RECT tempPos;
	tempPos = RectMakeCenter(_player.movePosX, _player.movePosY, 4,4);
	Rectangle(getMemDC(), tempPos.left - _camera.rc.left, tempPos.top - _camera.rc.top,
		tempPos.left - _camera.rc.left + 4, tempPos.top - _camera.rc.top + 4);

}

void Player::inStageWeaponSetting()
{
	// ����ѹ��� ���� �����Ʈ���� ������ ������Ʈ
	_weapon.frameY = itemNum;
	//if(_)


	// ���� ���� �Ǵ� ���� ���� �� (���)
	// ��� :�÷��̾� �̹���,  ����-> ���� -> ������ ������Ʈ + ������ǥ ����
	if (_weapon.type == WEAPONTYPE::SWORD && _state == PLAYERSTATE::IDLE)
	{
		_player.drawPosX = _player.movePosX;
		_player.drawPosY = _player.movePosY;
		_player.image = IMG("p_idle_oneHand");
		_weapon.image = IMG("weapon_sword");
		_weapon.frameX = 1;
		switch (_direction)
		{
#pragma region ��ǥ ����
		case PLAYERDIRECTION::UP:
			_weapon.drawPosX = _weapon.movePosX + 19;
			_weapon.drawPosY = _weapon.movePosY - 31;
			break;
		case PLAYERDIRECTION::DOWN:
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		case PLAYERDIRECTION::LEFT:
			_weapon.drawPosX = _weapon.movePosX - 20;
			_weapon.drawPosY = _weapon.movePosY - 36;
			break;
		case PLAYERDIRECTION::RIGHT:
			_weapon.drawPosX = _weapon.movePosX + 13;
			_weapon.drawPosY = _weapon.movePosY - 36;
			break;
		case PLAYERDIRECTION::LEFTUP:
			_weapon.drawPosX = _weapon.movePosX + 8;
			_weapon.drawPosY = _weapon.movePosY - 40;
			break;
		case PLAYERDIRECTION::RIGHTUP:
			_weapon.drawPosX = _weapon.movePosX - 14;
			_weapon.drawPosY = _weapon.movePosY - 40;
			break;
		case PLAYERDIRECTION::LEFTDOWN:
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 28;
			break;
		case PLAYERDIRECTION::RIGHTDOWN:
			_weapon.drawPosX = _weapon.movePosX + 16;
			_weapon.drawPosY = _weapon.movePosY - 28;
			break;
		}
	}
	if (_weapon.type == WEAPONTYPE::AX && _state == PLAYERSTATE::IDLE)
	{
		_player.drawPosX = _player.movePosX;
		_player.drawPosY = _player.movePosY;
		_player.image = IMG("p_idle_oneHand");
		_weapon.image = IMG("weapon_ax");
		switch (_direction)
		{

		case PLAYERDIRECTION::UP:
			_weapon.frameX = 14;
			_weapon.drawPosX = _weapon.movePosX + 14;
			_weapon.drawPosY = _weapon.movePosY - 31;
			break;
		case PLAYERDIRECTION::DOWN:
			_weapon.frameX = 14;
			_weapon.drawPosX = _weapon.movePosX - 29;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		case PLAYERDIRECTION::LEFT:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX - 19;
			_weapon.drawPosY = _weapon.movePosY - 36;
			break;
		case PLAYERDIRECTION::RIGHT:
			_weapon.frameX = 26;
			_weapon.drawPosX = _weapon.movePosX + 12;
			_weapon.drawPosY = _weapon.movePosY - 36;
			break;
		case PLAYERDIRECTION::LEFTUP:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX + 8;
			_weapon.drawPosY = _weapon.movePosY - 40;
			break;
		case PLAYERDIRECTION::RIGHTUP:
			_weapon.frameX = 26;
			_weapon.drawPosX = _weapon.movePosX - 14;
			_weapon.drawPosY = _weapon.movePosY - 40;
			break;
		case PLAYERDIRECTION::LEFTDOWN:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 28;
			break;
		case PLAYERDIRECTION::RIGHTDOWN:
			_weapon.frameX = 26;
			_weapon.drawPosX = _weapon.movePosX + 13;
			_weapon.drawPosY = _weapon.movePosY - 28;

		}
	}
#pragma endregion
	if (_weapon.type == WEAPONTYPE::SPEAR && _state == PLAYERSTATE::IDLE)
	{
		_player.drawPosX = _player.movePosX;
		_player.drawPosY = _player.movePosY;
		_player.image = IMG("p_idle_twoHand");
		_weapon.image = IMG("weapon_spear");
		switch (_direction)
		{
		case PLAYERDIRECTION::UP:
			_weapon.frameX = 3;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		case PLAYERDIRECTION::DOWN:
			_weapon.frameX = 4;
			_weapon.drawPosX = _weapon.movePosX - 19;
			_weapon.drawPosY = _weapon.movePosY - 68;
			break;
		case PLAYERDIRECTION::LEFT:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		case PLAYERDIRECTION::RIGHT:
			_weapon.frameX = 26;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		case PLAYERDIRECTION::LEFTUP:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		case PLAYERDIRECTION::RIGHTUP:
			_weapon.frameX = 26;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		case PLAYERDIRECTION::LEFTDOWN:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		case PLAYERDIRECTION::RIGHTDOWN:
			_weapon.frameX = 26;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 27;
			break;
		}
	}
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
	/*switch (_state)
	{
	case PLAYERSTATE::HIT:
		_player.image->setFrameX(_player.frameX);
		if(_isStateCheck.test(0)) _player.image->setFrameY(0);
		else _player.image->setFrameY(1);

		break;
	case PLAYERSTATE::DEAD:
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
*/
	
	// �÷��̾� + ���� ��ġ ������Ʈ
	_player.moveRc = RectMakeCenter(_player.movePosX, _player.movePosY, _player.width, _player.height);
	_player.drawRc = RectMakeCenter(_player.drawPosX, _player.drawPosY, _player.width, _player.height);
	_weapon.moveRc = RectMakeCenter(_weapon.movePosX, _weapon.movePosY, _weapon.width, _weapon.height);
	_weapon.drawRc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _weapon.width, _weapon.height);

}

// �ൿ ����
void Player::stateRender()
{
	_pStatePattern->stateRender(this);
}






