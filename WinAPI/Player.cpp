#include "Stdafx.h"
#include "Player.h"
#include "STATE.h"
#include "StateBase.h"
#include "StateAttack.h"


HRESULT Player::init(void)
{
#pragma region 플레이어 데이터 입출력 영역 
	// 로드 데이터 하기.....
	_player.face = IMG("p_face");
	_state = PLAYERSTATE::IDLE;
	_direction = PLAYERDIRECTION::DOWN;
	_weapon.type = WEAPONTYPE::SWORD;

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

	// 블럭 정보 추가 필요
	_abyss.abyss = 1;
	_abyss.stage = 1;

	// 임시 아이템넘버(무기프레임이미지 시트에서 y프레임)
	itemNum = 0;

	// 장비상태, 던전-스테이지 입구에 맞게 방향 설정하는 함수
	// 던전 내 아이템 변경시 바꿔도 괜찮을 듯 
	// 필요한 정보 : 무기타입, 무기번호, 캐릭터방향
	inStageWeaponSetting();

#pragma endregion

	_player.speed = 10;
	if (_weapon.type == WEAPONTYPE::SPEAR) _player.image=IMG("p_idle_twoHand");
	else _player.image = IMG("p_idle_oneHand");
		
	// 플레이어의 값을 받아서
	_player.frameX = 0;
	_player.frameY = static_cast<int>(_direction);
	_player.movePosX = _player.drawPosX = LSCENTER_X;
	_player.movePosY = _player.drawPosY = CENTER_Y;
	_player.width  = _player.image->getFrameWidth();
	_player.height = _player.image->getFrameHeight();
	// 순서 체크 할 것. 
	_player.rc = RectMakeCenter(_player.movePosX, _player.movePosY, _player.width, _player.height);
	//_player.rc = RectMakeCenter(_player.drawPosX, _player.drawPosY, _player.width, _player.height);

	_camera.playerLeft = _camera.playerTop = 0;
	_camera.weaponLeft = _camera.weaponTop = 0;

	// Down-Idle
	// 무기 데이터 업데이트
	// 이후 던전 방향에 맞게 조정
	_weapon.movePosX = _weapon.drawPosX = _player.movePosX;
	_weapon.movePosY = _weapon.drawPosY = _player.movePosY ;

	_weapon.width  = _weapon.image->getFrameWidth();
	_weapon.height = _weapon.image->getFrameHeight();
	_weapon.rc = RectMakeCenter(_weapon.movePosX, _weapon.movePosY, _weapon.width, _weapon.height);
	//_weapon.rc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _weapon.width, _weapon.height);



	// bitset setting - isLive
	_isStateCheck.reset();
	_isStateCheck.set(4);

	// 상태패턴 (대기상태로 시작)
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
	
	// hit,dead 상태일때는 Y프레임 세팅 제외.
	if (_state == PLAYERSTATE::BEHIT || _state == PLAYERSTATE::DEAD) {}
	else _player.frameY = static_cast<int>(_direction);
	


}

void Player::render(void)
{
	// 캐릭터, 무기 카메라 보정
	_camera.playerLeft = _player.rc.left - _camera.rc.left;
	_camera.playerTop  = _player.rc.top  - _camera.rc.top;
	_camera.weaponLeft = _weapon.rc.left - _camera.rc.left;
	_camera.weaponTop  = _weapon.rc.top  - _camera.rc.top;



	// 상태에 따라 렌더
	//stateRender();

	_player.image->frameRender(getMemDC(), _camera.playerLeft, _camera.playerTop, _player.frameX, _player.frameY);
	_weapon.image->frameRender(getMemDC(), _camera.weaponLeft, _camera.weaponTop, _weapon.frameX, _weapon.frameY);

	if(KEYOKD('P'))
	{
	cout <<  " 현재 X 프레임 : " << _player.frameX << endl;
	cout << " 현재 Y 프레임 : " << _player.frameY << endl;
	}
	//rcMake(getMemDC(), _rcPlayer);
	//rcMake(getMemDC(), _weapon.rc);

}

void Player::inStageWeaponSetting( )
{
	// 던전 진입 또는 무기 변경 시 
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

	// 무기넘버에 따라 무기시트에서 프레임 업데이트
	_weapon.frameY = itemNum;

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
	// 방향은 상시 체크 
	if (_direction == PLAYERDIRECTION::LEFT 
		|| _direction == PLAYERDIRECTION::LEFTUP 
		|| _direction == PLAYERDIRECTION::LEFTDOWN)
	{
		_isStateCheck.set(0);
	}
	else _isStateCheck.reset(0);

	// playerDirection = DOWN : 플레이어가 무기 아래에 렌더
	if (_direction == PLAYERDIRECTION::DOWN
		|| _direction == PLAYERDIRECTION::LEFTDOWN
		|| _direction == PLAYERDIRECTION::RIGHTDOWN)
	{
		_isStateCheck.set(5);
	}
	else _isStateCheck.reset(5);

	// 상태패턴 업데이트 
	_pStatePattern->stateUpdate(this);

	// 상태에 따른 플레이어 이미지 업데이트 
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

	// 플레이어 카메라가 안붙음 !!!!!
	// 플레이어 + 무기 위치 업데이트 (상태로 이관할 것 )
	_weapon.rc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _weapon.width, _weapon.height);



	// 상태로 이관
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

// 행동 렌더
void Player::stateRender()
{
	_pStatePattern->stateRender(this);
}






