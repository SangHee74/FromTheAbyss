#include "Stdafx.h"
#include "Player.h"
#include "STATE.h"
#include "StateBase.h"
#include "StateAttack.h"

HRESULT Player::init(void)
{
#pragma region 플레이어 데이터 입출력 영역 
	// 로드 데이터 하기.....
	_player.face = IMAGEMANAGER->findImage("p_face"); 

	// 제이슨 로더에서 가져오면 좋을거같은데..
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
	// 블럭 정보 추가 필요
	_abyss.abyss = 1;
	_abyss.stage = 1;

#pragma endregion

	_shadowAlpha = 120;
	_player.speed = 10;
	_collision.defWidth = 40;
	_collision.defHeight = 80;
	_collision.attWidth = 0;
	_collision.attHeight = 0;


	return S_OK;
}

void Player::release(void)
{
	//_pStatePattern->stateRelease();
}

void Player::update(void)
{

	// weapon pos+frame setting(idle)
	weaponinStageSetting();

	// state pattern update
	stateUpdate();
	
	// def,dead 상태일때는 Y프레임 세팅 제외.
	if (_state == PLAYERSTATE::DEF || _state == PLAYERSTATE::DEAD) {}
	else _player.frameY = static_cast<int>(_direction);


	// 외부에서 맞은 경우 피격모션으로 바꾸기 
	if (_state == PLAYERSTATE::DEF)
	{
		_pStatePattern = DefState::getInstance();
		setPlayerState(_pStatePattern);
	}


}

void Player::render(void)
{
	// 캐릭터, 무기 카메라 보정
	_camera.playerLeft = _player.drawRc.left - _camera.rc.left;
	_camera.playerTop = _player.drawRc.top - _camera.rc.top;
	_camera.weaponLeft = _weapon.drawRc.left - _camera.rc.left;
	_camera.weaponTop = _weapon.drawRc.top - _camera.rc.top;
	_camera.effectLeft = _collision.attRc.left - _camera.rc.left;
	_camera.effectTop = _collision.attRc.top - _camera.rc.top;

	IMGAR("p_shadow", getMemDC(), _camera.playerLeft+20, _camera.playerTop +100 ,_shadowAlpha);
	// 타격범위 렌더
	//Rectangle(getMemDC(), _collision.attRc.left - _camera.rc.left, _collision.attRc.top - _camera.rc.top,
	//	_collision.attRc.left - _camera.rc.left + _collision.attWidth,
	//	_collision.attRc.top - _camera.rc.top + _collision.attHeight);

	if (_isStateCheck.test(5))
	{
		_player.image->frameRender(getMemDC(), _camera.playerLeft, _camera.playerTop, _player.frameX, _player.frameY);
		_weapon.image->frameRender(getMemDC(), _camera.weaponLeft, _camera.weaponTop, _weapon.frameX, _weapon.frameY);
		if ( _state == PLAYERSTATE::ATT_ONEHANDCOMBO)
		{
			_collision.attEffectImg->frameRender(getMemDC(), _camera.effectLeft, _camera.effectTop, _collision.attEffFrameX, _collision.attEffFrameY);
		}
	}
	if (! _isStateCheck.test(5))
	{
		if (_state == PLAYERSTATE::ATT_ONEHANDCOMBO)
		{
			_collision.attEffectImg->frameRender(getMemDC(), _camera.effectLeft, _camera.effectTop, _collision.attEffFrameX, _collision.attEffFrameY);
		}		
		_weapon.image->frameRender(getMemDC(), _camera.weaponLeft, _camera.weaponTop, _weapon.frameX, _weapon.frameY);
		_player.image->frameRender(getMemDC(), _camera.playerLeft, _camera.playerTop, _player.frameX, _player.frameY);
	}


	//=======================================================================================================
	// # 피격범위, 픽셀충돌체크 프로비 범위 토글키
	//=======================================================================================================
#pragma region 가이드 라인 토글키
	if (KEYTOG(VK_F2))
	{
		// 가로세로 4px 사각형 / 중점 + 픽셀충돌 위치 계산
		// 가이드 Toggle
		RECT tempPos, tempPos2, tempPos3, tempPos4, tempPos5;
		tempPos = RectMakeCenter(_player.movePosX, _player.movePosY, 4, 4);
		Rectangle(getMemDC(), tempPos.left - _camera.rc.left, tempPos.top - _camera.rc.top,
			tempPos.left - _camera.rc.left + 4, tempPos.top - _camera.rc.top + 4);

		// 피격범위 렌더 
		//Rectangle(getMemDC(), _collision.defRc.left - _camera.rc.left, _collision.defRc.top - _camera.rc.top,
		//	_collision.defRc.left - _camera.rc.left + _collision.defWidth, _collision.defRc.top - _camera.rc.top + _collision.defHeight);

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

		// 무기이미지 렌더
		//Rectangle(getMemDC(), _camera.weaponLeft, _camera.weaponTop,
		//	_weapon.drawRc.left - _camera.rc.left + _weapon.width,
		//	_weapon.drawRc.top - _camera.rc.top + _weapon.height);


		// 타격범위 렌더
		//Rectangle(getMemDC(), _collision.attRc.left - _camera.rc.left, _collision.attRc.top - _camera.rc.top,
		//					  _collision.attRc.left - _camera.rc.left + _collision.attWidth,
		//					  _collision.attRc.top  - _camera.rc.top  + _collision.attHeight );


		// 픽셀충돌 아래 - 를 좌우로 뿌리기 
		tempPos2 = RectMakeCenter(_player.movePosX, _pixel.probeUp, 4, 4);
		Rectangle(getMemDC(), tempPos2.left - _camera.rc.left, tempPos2.top - _camera.rc.top,
			tempPos2.left - _camera.rc.left + 4, tempPos2.top - _camera.rc.top + 4);

		tempPos3 = RectMakeCenter(_player.movePosX, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos3.left - _camera.rc.left, tempPos3.top - _camera.rc.top,
			tempPos3.left - _camera.rc.left + 4, tempPos3.top - _camera.rc.top + 4);
		// 픽셀충돌 좌
		tempPos4 = RectMakeCenter(_pixel.probeLeft, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos4.left - _camera.rc.left, tempPos4.top - _camera.rc.top,
			tempPos4.left - _camera.rc.left + 4, tempPos4.top - _camera.rc.top + 4);
		// 픽셀충돌 우
		tempPos5 = RectMakeCenter(_pixel.probeRight, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos5.left - _camera.rc.left, tempPos5.top - _camera.rc.top,
			tempPos5.left - _camera.rc.left + 4, tempPos5.top - _camera.rc.top + 4);

		//rcMake(getMemDC(), _player.defRc);
		//rcMake(getMemDC(), _weapon.attRc);
	}


#pragma endregion



}

#pragma region 상태관련 

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

	// 플레이어 + 무기 위치 업데이트
	_player.moveRc = RectMakeCenter(_player.movePosX, _player.movePosY, _player.width, _player.height);
	_player.drawRc = RectMakeCenter(_player.drawPosX, _player.drawPosY, _player.width, _player.height);
	_weapon.moveRc = RectMakeCenter(_weapon.movePosX, _weapon.movePosY, _weapon.width, _weapon.height);
	_weapon.drawRc = RectMakeCenter(_weapon.drawPosX, _weapon.drawPosY, _weapon.width, _weapon.height);
	
	// 캐릭터 피격/타격 범위 업데이트
	_collision.defRc = RectMakeCenter(_player.drawPosX, _player.drawPosY+10, _collision.defWidth, _collision.defHeight);
	_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);


}

// 행동 렌더
void Player::stateRender()
{
	_pStatePattern->stateRender(this);
}

#pragma endregion 

// 스테이지 이닛용 
void Player::playerInStageSetting(int playerX, int playerY, PLAYERDIRECTION direction)
{

	_player.movePosX = _player.drawPosX = playerX;
	_player.movePosY = _player.drawPosY = playerY;
	_state = PLAYERSTATE::IDLE;
	_direction = direction;

	// 임시 아이템넘버(무기프레임이미지 시트에서 y프레임)
	itemNum = 1;
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

	// 상태패턴 (대기상태로 시작)
	// 캐릭터 방향, 무기타입, 무기번호(itemNum)
	_pStatePattern = IdleState::getInstance();
	setPlayerState(_pStatePattern);

	// 픽셀충돌 - 탐색
	_pixel.probeDown = _player.movePosY + _player.image->getHeight() / 2;
	_pixel.probeLeft = _player.movePosX - _player.image->getWidth() / 2;
	_pixel.probeRight = _player.movePosX + _player.image->getWidth() / 2;


}

// 던전 진입 또는 무기 변경 시 (대기상태)
void Player::weaponinStageSetting()
{
	// 무기넘버에 따라 무기시트에서 프레임 업데이트
	_weapon.frameY = itemNum;
	if (_weapon.type == WEAPONTYPE::AX)  _weapon.frameY = 0;

	// 이동좌표, 렌더좌표 업데이트 
	_player.drawPosX = _player.movePosX;
	_player.drawPosY = _player.movePosY;

	// 대기 :플레이어 이미지,  무기-> 방향 -> 프레임 업데이트 + 렌더좌표 수정
#pragma region 좌표 맞춤
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
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX + 12;
			_weapon.drawPosY = _weapon.movePosY - 36;
			break;
		case PLAYERDIRECTION::LEFTUP:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX + 8;
			_weapon.drawPosY = _weapon.movePosY - 40;
			break;
		case PLAYERDIRECTION::RIGHTUP:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX - 14;
			_weapon.drawPosY = _weapon.movePosY - 40;
			break;
		case PLAYERDIRECTION::LEFTDOWN:
			_weapon.frameX = 1;
			_weapon.drawPosX = _weapon.movePosX - 23;
			_weapon.drawPosY = _weapon.movePosY - 28;
			break;
		case PLAYERDIRECTION::RIGHTDOWN:
			_weapon.frameX = 1;
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

// 공격 시 캐릭터 위치, 무기위치 이펙트 위치 , 무기프레임 업데이트 
void Player::playerAttSetting(bitset<3> combo)
{

	// 무기타입 -> 캐릭터 방향 -> 콤보단계 -> 캐릭터 프레임X 
	// 캐릭터 프레임X가 두번째가 되면, 바라보는 방향으로 약간 이동.
	int tempMoveMax;
	if (_weapon.type == WEAPONTYPE::AX)
	{
		switch (_direction)
		{
		case PLAYERDIRECTION::UP:
			if (combo.test(0))
			{
				if (_player.frameX = 0)
				{
					_weapon.frameX = 9;
					_weapon.drawPosX = _weapon.movePosX - 50;
					_weapon.drawPosY = _weapon.movePosY - 50;
					_collision.attPosX = _weapon.drawPosX - 25;
					_collision.attPosY = _weapon.drawPosY + 16;
					_collision.attWidth = 122;
					_collision.attHeight = 113;
				}
				else
				{
					_weapon.frameX = 10; 
					_weapon.drawPosX = _weapon.movePosX - 50;
					_weapon.drawPosY = _weapon.movePosY + 50;
					_collision.attPosX = _weapon.drawPosX - 25;
					_collision.attPosY = _weapon.drawPosY + 16;
					_collision.attWidth = 122;
					_collision.attHeight = 113;
					
					for (tempMoveMax = 1 ; tempMoveMax < 5 ; tempMoveMax++)
					{
						cout << "콤보 X프레임 2nd : 이동 " << endl;
					//	_player.movePosY -= tempMoveMax; // 일정구간 이동. 이동이안되면 콤보부분으로 이관
					}
				}
			}
			if (combo.test(1))
			{
				if (_player.frameX = 0) _weapon.frameX = 6;
				else _weapon.frameX = 3;
			}	
			if (combo.test(2))
			{
				if (_player.frameX = 0) _weapon.frameX = 3;
				else _weapon.frameX = 2;
			}
			break;
		case PLAYERDIRECTION::DOWN:
			break;
		case PLAYERDIRECTION::LEFT:
			break;
		case PLAYERDIRECTION::RIGHT:
			break;
		case PLAYERDIRECTION::LEFTUP:
			break;
		case PLAYERDIRECTION::RIGHTUP:
			break;
		case PLAYERDIRECTION::LEFTDOWN:
			break;
		case PLAYERDIRECTION::RIGHTDOWN:
			if (combo.test(0))
			{
				if (_player.frameX = 0)
				{
					_weapon.frameX = 25;
					_weapon.drawPosX = _weapon.movePosX - 50;
					_weapon.drawPosY = _weapon.movePosY + 50;
					_collision.attPosX = _weapon.drawPosX - 20;
					_collision.attPosY = _weapon.drawPosY + 56;
					_collision.attWidth = 116;
					_collision.attHeight = 43;
				}
				else // OK!
				{
					_weapon.frameX = 4; // 프레임이 끝날때까지 
					_weapon.drawPosX = _weapon.movePosX - 50;
					_weapon.drawPosY = _weapon.movePosY + 50;
					_collision.attPosX = _weapon.drawPosX + 95;
					_collision.attPosY = _weapon.drawPosY - 30;
					_collision.attWidth = 116;
					_collision.attHeight = 43;

					for (tempMoveMax = 1; tempMoveMax < 5; tempMoveMax++)
					{
						//_player.movePosY += tempMoveMax; // 일정구간 이동
					}
				}
			}
			break;
		}
	}


	_collision.attRc =
		RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
	
}

int Player::playerDamage()
{
	int damage = 0;



	return damage;
}

