#include "Stdafx.h"
#include "Player.h"
#include "STATE.h"
#include "StateBase.h"
#include "StateAttack.h"

HRESULT Player::init(void)
{
#pragma region �÷��̾� ������ ����� ���� 
	// �ε� ������ �ϱ�.....
	_player.face = IMAGEMANAGER->findImage("p_face"); 

	// ���̽� �δ����� �������� �����Ű�����..
	_status.curHp = 100;
	_status.curSp = 100;
	_status.curExp = 0;
	_status.maxHp = _status.curHp;
	_status.maxSp = _status.curSp;
	_status.maxExp = 16;
	_status.lv = 1;
	_status.iAtt = 10;
	_status.iDef = 12;
	_status.iInt = 7;
	_status.iMen = 10;
	_status.iAgi = 8;
	_status.iLuk = 9;
	_status.iStatusPoint = 0; 
	_status.lufia = 300;
	// �� ���� �߰� �ʿ�
	_abyss.abyss = 1;
	_abyss.stage = 1;

#pragma endregion

	_shadowAlpha = 120;
	_player.speed = 10;
	_collision.defWidth = 40;
	_collision.defHeight = 80;
	_collision.attWidth = 0;
	_collision.attHeight = 0;
	_collision.attEffectImg = nullptr;
	_collision.attEffFrameX = 0;
	_collision.attEffFrameY = 0;



	return S_OK;
}

void Player::release(void)
{
	//_pStatePattern->stateRelease();
}

void Player::update(void)
{

	// weapon pos+frame setting(idle)
	inStageWeaponSetting();

	// state pattern update
	stateUpdate();
	
	// def,dead �����϶��� Y������ ���� ����.
	if (_state == PLAYERSTATE::DEF || _state == PLAYERSTATE::DEAD) {}
	else _player.frameY = static_cast<int>(_direction);


	// �ܺο��� ���� ����ǰݸ������ �ٲٱ� 
	if (_state == PLAYERSTATE::DEF)
	{
		_pStatePattern = DefState::getInstance();
		setPlayerState(_pStatePattern);
	}



}

void Player::render(void)
{
	// ĳ����, ���� ī�޶� ����
	_camera.playerLeft = _player.drawRc.left - _camera.rc.left;
	_camera.playerTop = _player.drawRc.top - _camera.rc.top;
	_camera.weaponLeft = _weapon.drawRc.left - _camera.rc.left;
	_camera.weaponTop = _weapon.drawRc.top - _camera.rc.top;

	IMGAR("p_shadow", getMemDC(), _camera.playerLeft+20, _camera.playerTop +100 ,_shadowAlpha);

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


	//=======================================================================================================
	// # �ǰݹ���, �ȼ��浹üũ ���κ� ���� ���Ű
	//=======================================================================================================
#pragma region ���̵� ���� ���Ű
	if (KEYTOG(VK_F2))
	{
		// ���μ��� 4px �簢�� / ���� + �ȼ��浹 ��ġ ���
		// ���̵� Toggle
		RECT tempPos, tempPos2, tempPos3, tempPos4, tempPos5;
		tempPos = RectMakeCenter(_player.movePosX, _player.movePosY, 4, 4);
		Rectangle(getMemDC(), tempPos.left - _camera.rc.left, tempPos.top - _camera.rc.top,
			tempPos.left - _camera.rc.left + 4, tempPos.top - _camera.rc.top + 4);

		// �ǰݹ��� ���� 
		Rectangle(getMemDC(), _collision.defRc.left - _camera.rc.left, _collision.defRc.top - _camera.rc.top,
			_collision.defRc.left - _camera.rc.left + _collision.defWidth, _collision.defRc.top - _camera.rc.top + _collision.defHeight);

		if (_isStateCheck.test(5))
		{
			_player.image->frameRender(getMemDC(), _camera.playerLeft, _camera.playerTop, _player.frameX, _player.frameY);
			_weapon.image->frameRender(getMemDC(), _camera.weaponLeft, _camera.weaponTop, _weapon.frameX, _weapon.frameY);
		}
		if (!_isStateCheck.test(5))
		{
			_weapon.image->frameRender(getMemDC(), _camera.weaponLeft, _camera.weaponTop, _weapon.frameX, _weapon.frameY);
			_player.image->frameRender(getMemDC(), _camera.playerLeft, _camera.playerTop, _player.frameX, _player.frameY);
		}

		// Ÿ�ݹ��� ����
		Rectangle(getMemDC(), _collision.attRc.left - _camera.rc.left, _collision.attRc.top - _camera.rc.top,
							  _collision.attRc.left - _camera.rc.left + _collision.attWidth,
							  _collision.attRc.top  - _camera.rc.top  + _collision.attHeight );


		// �ȼ��浹 �Ʒ� - �� �¿�� �Ѹ��� 
		tempPos2 = RectMakeCenter(_player.movePosX, _pixel.probeUp, 4, 4);
		Rectangle(getMemDC(), tempPos2.left - _camera.rc.left, tempPos2.top - _camera.rc.top,
			tempPos2.left - _camera.rc.left + 4, tempPos2.top - _camera.rc.top + 4);

		tempPos3 = RectMakeCenter(_player.movePosX, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos3.left - _camera.rc.left, tempPos3.top - _camera.rc.top,
			tempPos3.left - _camera.rc.left + 4, tempPos3.top - _camera.rc.top + 4);
		// �ȼ��浹 ��
		tempPos4 = RectMakeCenter(_pixel.probeLeft, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos4.left - _camera.rc.left, tempPos4.top - _camera.rc.top,
			tempPos4.left - _camera.rc.left + 4, tempPos4.top - _camera.rc.top + 4);
		// �ȼ��浹 ��
		tempPos5 = RectMakeCenter(_pixel.probeRight, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos5.left - _camera.rc.left, tempPos5.top - _camera.rc.top,
			tempPos5.left - _camera.rc.left + 4, tempPos5.top - _camera.rc.top + 4);

		//rcMake(getMemDC(), _player.defRc);
		//rcMake(getMemDC(), _weapon.attRc);
	}

#pragma endregion



}

void Player::inStageWeaponSetting()
{
	// ����ѹ��� ���� �����Ʈ���� ������ ������Ʈ
	_weapon.frameY = itemNum;
	
	// �̵���ǥ, ������ǥ ������Ʈ 
	_player.drawPosX = _player.movePosX;
	_player.drawPosY = _player.movePosY;

	// ���� ���� �Ǵ� ���� ���� �� (���)
	// ��� :�÷��̾� �̹���,  ����-> ���� -> ������ ������Ʈ + ������ǥ ����
#pragma region ��ǥ ����
	if (_weapon.type == WEAPONTYPE::SWORD && _state == PLAYERSTATE::IDLE)
	{
		_player.image = IMG("p_idle_oneHand");
		_weapon.image = IMG("weapon_sword");
		_weapon.frameX = 1;
		switch (_direction)
		{
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
		_player.image = IMG("p_idle_twoHand");
		_weapon.image = IMG("weapon_spear");
		switch (_direction)
		{
		case PLAYERDIRECTION::UP:
			_weapon.frameX = 4;
			_player.drawPosX = _player.movePosX - 2;
			_weapon.drawPosX = _weapon.movePosX - 40;
			_weapon.drawPosY = _weapon.movePosY - 70;
			break;
		case PLAYERDIRECTION::DOWN:
			_weapon.frameX = 5;
			_player.drawPosX = _player.movePosX + 2;
			_weapon.drawPosX = _weapon.movePosX - 19;
			_weapon.drawPosY = _weapon.movePosY - 68;
			break;
		case PLAYERDIRECTION::LEFT:
			_weapon.frameX = 12;
			_weapon.drawPosX = _weapon.movePosX - 78;
			_weapon.drawPosY = _weapon.movePosY - 79;
			break;
		case PLAYERDIRECTION::RIGHT:
			_weapon.frameX = 13;
			_weapon.drawPosX = _weapon.movePosX + 8;
			_weapon.drawPosY = _weapon.movePosY - 79;
			break;
		case PLAYERDIRECTION::LEFTUP:
			_weapon.frameX = 4;
			_weapon.drawPosX = _weapon.movePosX - 53;
			_weapon.drawPosY = _weapon.movePosY - 70;
			break;
		case PLAYERDIRECTION::RIGHTUP:
			_weapon.frameX = 5;
			_player.drawPosX = _player.movePosX - 2;
			_weapon.drawPosX = _weapon.movePosX - 15;
			_weapon.drawPosY = _weapon.movePosY - 67;
			break;
		case PLAYERDIRECTION::LEFTDOWN:
			_weapon.frameX = 5;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 68;
			break;
		case PLAYERDIRECTION::RIGHTDOWN:
			_weapon.frameX = 4;
			_player.drawPosX = _player.movePosX - 2;
			_weapon.drawPosX = _weapon.movePosX - 48;
			_weapon.drawPosY = _weapon.movePosY - 71;
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

	// �÷��̾� + ���� ��ġ ������Ʈ
	_player.moveRc = RectMakeCenter(_player.movePosX, _player.movePosY, _player.width, _player.height);
	_player.drawRc = RectMakeCenter(_player.drawPosX, _player.drawPosY, _player.width, _player.height);
	_weapon.moveRc = RectMakeCenter(_weapon.movePosX, _weapon.movePosY, _weapon.width, _weapon.height);
	_weapon.drawRc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _weapon.width, _weapon.height);
	
	// ĳ���� �ǰ�/Ÿ�� ���� ������Ʈ
	_collision.defRc = RectMakeCenter(_player.drawPosX, _player.drawPosY+10, _collision.defWidth, _collision.defHeight);
	_collision.attRc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _collision.attWidth, _collision.attHeight);


}

// �ൿ ����
void Player::stateRender()
{
	_pStatePattern->stateRender(this);
}



// �������� �̴ֿ� 
void Player::playerInStageSetting(int playerX, int playerY, PLAYERDIRECTION direction)
{

	_player.movePosX = _player.drawPosX = playerX;
	_player.movePosY = _player.drawPosY = playerY;
	_state = PLAYERSTATE::IDLE;
	_direction = direction;

	// �ӽ� �����۳ѹ�(�����������̹��� ��Ʈ���� y������)
	itemNum = 0;
	if (itemNum == 0)
	{
		_weapon.image = IMG("weapon_sword"); _weapon.type = WEAPONTYPE::SWORD;
	}
	if (itemNum == 1)
	{
		_weapon.image = IMG("weapon_ax"); _weapon.type = WEAPONTYPE::AX;
	}
	if (itemNum == 2)
	{
		_weapon.image = IMG("weapon_spear");  _weapon.type = WEAPONTYPE::SPEAR;
	}

	if (_weapon.type == WEAPONTYPE::SPEAR) _player.image = IMG("p_idle_twoHand");
	else _player.image = IMG("p_idle_oneHand");

	_player.frameX = 0;
	_player.frameY = static_cast<int>(_direction);
	_player.width = _player.image->getFrameWidth();
	_player.height = _player.image->getFrameHeight();
	_player.moveRc = RectMakeCenter(_player.movePosX, _player.movePosY, _player.width, _player.height);

	_weapon.movePosX = _weapon.drawPosX = _player.movePosX;
	_weapon.movePosY = _weapon.drawPosY = _player.movePosY;
	_weapon.width = _weapon.image->getFrameWidth();
	_weapon.height = _weapon.image->getFrameHeight();
	_weapon.moveRc = RectMakeCenter(_weapon.movePosX, _weapon.movePosY, _weapon.width, _weapon.height);

	// bitset setting - isLive
	_isStateCheck.reset();
	_isStateCheck.set(4);

	// �������� (�����·� ����)
	// ĳ���� ����, ����Ÿ��, �����ȣ(itemNum)
	_pStatePattern = IdleState::getInstance();
	setPlayerState(_pStatePattern);

	// �ȼ��浹 - Ž��
	_pixel.probeDown = _player.movePosY + _player.image->getHeight() / 2;
	_pixel.probeLeft = _player.movePosX - _player.image->getWidth() / 2;
	_pixel.probeRight = _player.movePosX + _player.image->getWidth() / 2;
}


void Player::setPlayerCollisionAttRc(int posX, int posY, int width, int height )
{
	_collision.attPosX = posX;
	_collision.attPosY = posY;
	_collision.attWidth = width;
	_collision.attHeight = height;

	_collision.attRc =
		RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
}



