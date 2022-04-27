#include "Stdafx.h"
#include "Monster.h"

Monster::Monster(): _maxHp(0), _curHp(0), _curAtt(0),
					_dropExp(0), _dropLufia(0), _dropItemIndex(0),
					_moveRc(RectMake(0,0,0,0)), 
					_recognitionRc(RectMake(0, 0, 0, 0)),
					_movePosX(0), _movePosY(0),
					_frameX(0), _frameY(0), _atkRange(0),
					_speed(0.0f), _distance(0.0f), _angle(0.0f),
					_rndTimeCount(0.0f), _worldTimeCount(0.0f), _atkCoolTime(0.0f), _atkTimeCount(0.0f),
					_playerCheck(false), _atkStart(false), _backToPos(false),
					_image(nullptr), _count(0), _stateChangeTime(0)
{
}

HRESULT Monster::init(void)
{
	return S_OK;
}

HRESULT Monster::init(POINT position)
{
	// 임시변수 
	timeCount = 0.0f;

	// 이동 및 업데이트 관련 
	_movePosX = position.x;
	_movePosY = position.y;
	_frameX = 0;
	_frameY = 0;
	_speed = 5;
	_distance = 0;
	_angle = 0.0f;

	// 프레임 업데이트, 공격상태 체크 등 
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_worldTimeCount = GetTickCount();
	_atkCoolTime = 0.0f;
	_atkTimeCount = 0.0f;

	// 몬스터의 인식범위에 플레이어가 있는지 체크 
	_playerCheck = false;
	cout << "몬스터 생성자 " << endl;

	// 몬스터cpp에서 세팅된 정보로 위치 세팅
	_moveRc = RectMakeCenter(_movePosX, _movePosY, 30, 30);
	_collision.defRc = RectMakeCenter(_movePosX, _movePosY - 30, _collision.defWidth, _collision.defHeight);
	_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);



	return S_OK;
}

HRESULT Monster::init(const char* imageName, POINT position)
{
	// 임시변수 
	timeCount = 0.0f;

	// 이미지 지정
	_image= IMAGEMANAGER->findImage(imageName);

	// 이동 및 업데이트 관련 
	_movePosX = position.x;
	_movePosY = position.y;
	_frameX = 0;
	_frameY = 0;
	_speed = 5;
	_distance = 0;
	_angle = 0.0f;

	// 프레임 업데이트, 공격상태 체크 등 
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_worldTimeCount = GetTickCount();
	_atkCoolTime = 0.0f;
	_atkTimeCount = 0.0f;

	// 몬스터의 인식범위에 플레이어가 있는지 체크 
	_playerCheck = false;


	return S_OK;
}

void Monster::release(void)
{
}

void Monster::update(void)
{
	_stateChangeTime++;
	//cout << "_stateChangeTime : "<< _stateChangeTime << endl;
	//cout << "_distance : " << _distance << endl;
	//cout << "_atkRange : " << _atkRange << endl;
	
	

	// state Update
	if (_stateChangeTime % 30 == 0 && (_state != MONSTERSTATE::DEAD))
	{
		if (_playerCheck) // 인식함
		{
			//if ( _atkCoolTime > 0) // 쿨타임 중 으로 공격불가
			//{
			//	_state = MONSTERSTATE::IDLE; // 대기
			//}
			if (_atkCoolTime == 0)
			{
				changeState(); // 상태 변경
			}
		}
		else // 인식안함
		{
			if (_stateChangeTime % 180 == 0) // 일정주기마다
			{
				_stateChangeTime = 0;
				changeState(); // 상태 변경
			}
		}
	}

	

	// ================================================================================================
	// state
	// ================================================================================================

	switch (_state)
	{
	case MONSTERSTATE::IDLE:
		if (_stateChangeTime % 30 == 0) changeState();
	
		cout << "mon  - IDLE" << endl;
		break;
	case MONSTERSTATE::MOVE:
		move();
		cout << "mon  - MOVE" << endl;

		break;
	case MONSTERSTATE::DEF:
		//cout << "몬스터 피격 후 타임카운트 : " << timeCount << endl;
		timeCount += TIMEMANAGER->getElapsedTime();

		if (timeCount >= 1.0f)
		{
			timeCount = 0;
			_state = MONSTERSTATE::IDLE;
		}
		cout << "mon  - DEF" << endl;

		break;
	case MONSTERSTATE::DEAD:
		if (_image->getFrameX() > _image->getMaxFrameX())
		{
			_collision.defWidth = _collision.defHeight = 0;
			_collision.defRc = RectMakeCenter(_movePosX, _movePosY, _collision.atkWidth, _collision.atkHeight);
		}
		_collision.atkWidth = _collision.atkHeight = 0;
		_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
		cout << "mon  - DEAD" << endl;

		break;
	case MONSTERSTATE::ATK:
		cout << "mon  - ATK" << endl;

		attack();
		break;

	}


	// 공격이 아니고 쿨타임이 남아있으면
	if (_state != MONSTERSTATE::ATK && _atkCoolTime > 0)
	{
		_atkCoolTime -= TIMEMANAGER->getElapsedTime();
		if (_atkCoolTime <= 0)_atkCoolTime = _atkCoolTime > 0;
	}
	cout << "monster - _atkCoolTime : " << _atkCoolTime << endl;


	
	pixelCollision(); // 픽셀충돌
	rectUpdate();	  // 타격, 피격 렉트 업데이트 


	// ================================================================================================
	// frame Update 
	// ================================================================================================

	if (! _atkStart ) 
	{
	//	cout << "공격 시작함 XXXXXXX " << endl;
		if (_stateChangeTime % 20 == 0)
		{
			_frameX++;
			if (_image->getMaxFrameX() < _frameX)
			{
				_frameX = 0;
			}
			setDirection(); // 일정 주기로 방향 변경
		}
	}

	if (_state == MONSTERSTATE::IDLE || _state == MONSTERSTATE::MOVE) 
	{
		_frameY = static_cast<int>(_direction);
	}

		if (_atkStart) cout << "공격 시작함 " << endl;

	
}

void Monster::render(void)
{
	draw();
}


void Monster::setDirection(void)
{

	if (_angle >= 45 * DTR && _angle < 135 * DTR)
	{
		_direction = MONSTERDIRECTION::UP;
	}
	if (_angle >= 135 * DTR	&& _angle < 225 * DTR)
	{
		_direction = MONSTERDIRECTION::LEFT;
	}
	if (_angle >= 225 * DTR	&& _angle < 315 * DTR)
	{
		_direction = MONSTERDIRECTION::DOWN;
	}
	if (_angle >= 315 * DTR || (_angle >= 0 * DTR && _angle < 45 * DTR))
	{
		_direction = MONSTERDIRECTION::RIGHT;
	}

}

// 추적 -> 공격으로 전환
void Monster::monsterMoveToPlayer(void)
{

	switch (_direction)
	{
	//case MONSTERDIRECTION::UP:
	//	if (DATAMANAGER->getPlayer()->getPlayer().drawPosY >= _collision.atkRc.top)
	//	{
	//		if (!_atkStart) // 공격이 시작하지 않았을 때만 공격 상태로.
	//		{
	//			_state = MONSTERSTATE::ATK;
	//		}
	//	}
	//	if (DATAMANAGER->getPlayer()->getPlayer().drawPosY < _collision.atkRc.top)
	//	{
	//		_state = MONSTERSTATE::MOVE;
	//	}
	//	break;

	case MONSTERDIRECTION::DOWN:
		if (DATAMANAGER->getPlayer()->getPlayer().drawPosY <= _collision.atkRc.bottom)
		{
			if (!_atkStart) // 공격이 시작하지 않았을 때만 공격 상태로.
			{
				_state = MONSTERSTATE::ATK;
			}
		}
		if (DATAMANAGER->getPlayer()->getPlayer().drawPosY > _collision.atkRc.bottom)
		{
			_state = MONSTERSTATE::MOVE;
		}

		break;

	/*case MONSTERDIRECTION::LEFT: 
		if (DATAMANAGER->getPlayer()->getPlayer().drawPosX >= _collision.atkRc.left)
		{
			if (!_atkStart)
			{
				_state = MONSTERSTATE::ATK;
			}
		}
		if (DATAMANAGER->getPlayer()->getPlayer().drawPosX < _collision.atkRc.left)
		{
			_state = MONSTERSTATE::MOVE;
		}
		break;

	case MONSTERDIRECTION::RIGHT:
		if (DATAMANAGER->getPlayer()->getPlayer().drawPosX <= _collision.atkRc.right)
		{
			if (!_atkStart)
			{
				_state = MONSTERSTATE::ATK;
			}
		}
		if (DATAMANAGER->getPlayer()->getPlayer().drawPosX > _collision.atkRc.right)
		{
			_state = MONSTERSTATE::MOVE;
		}
		break;
*/
	}

	_frameX = 0;
}

void Monster::pixelCollision()
{
	//탐지
	_pixel.probeUp	  =  _movePosY - _pixel.space.TB;
	_pixel.probeDown  =  _movePosY + _pixel.space.TB;
	_pixel.probeLeft  =  _movePosX - _pixel.space.LR;
	_pixel.probeRight =  _movePosX + _pixel.space.LR;


	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		if (pixelColorCheck(_movePosX, _pixel.probeUp)) _movePosY += _speed;
		break;
	case MONSTERDIRECTION::DOWN:
		if (pixelColorCheck(_movePosX, _pixel.probeUp)) _movePosY -= _speed;
		break;
	case MONSTERDIRECTION::LEFT:
		if (pixelColorCheck(_pixel.probeLeft, _pixel.probeDown)) _movePosX += _speed;
		break;
	case MONSTERDIRECTION::RIGHT:
		if (pixelColorCheck(_pixel.probeRight, _pixel.probeDown)) _movePosX -= _speed;
		break;
	}

}

bool Monster::pixelColorCheck(int getPixelX, int getPixelY)
{
	DATAMANAGER->getMapData().pixelMap->getMemDC();

	COLORREF color = GetPixel(DATAMANAGER->getMapData().pixelMap->getMemDC(), getPixelX, getPixelY);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);


	if (!(r == 255 && g == 0 && b == 255))
	{
		// 마젠타가 아니면, 픽셀 충돌임.
		return true;
	}
	else return false;

}

void Monster::changeState()
{
	if (_playerCheck) // 플레이어 인식O
	{
		if (_state != MONSTERSTATE::ATK) monsterMoveToPlayer();
	}
	else // 플레이어 인식X
	{
		int rndState = 0;
		int rndDirection = 0;
		
		rndState = RND->getInt(2);
		rndDirection = RND->getInt(4);

		cout << "rndState : " << rndState << endl;
		cout << "rndDirection : " << rndDirection << endl;

		if (rndState == 0)
		{
			_state = MONSTERSTATE::IDLE;
		}
		if (rndState == 1)
		{
			_state = MONSTERSTATE::MOVE;
			move();
		}

		switch (rndDirection)
		{
		case 0: 
			_direction = MONSTERDIRECTION::UP;
			break;
		case 1:
			_direction = MONSTERDIRECTION::DOWN;
			break;
		case 2:
			_direction = MONSTERDIRECTION::LEFT;
			break;
		case 3:
			_direction = MONSTERDIRECTION::RIGHT;
			break;
		}
	}
}



// 오버라이딩 함수
void Monster::move(void)
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_movePosY -= _speed;
		break;

	case MONSTERDIRECTION::DOWN:
		_movePosY += _speed;
		break;

	case MONSTERDIRECTION::LEFT:
		_movePosX -= _speed;
		break;

	case MONSTERDIRECTION::RIGHT:
		_movePosX += _speed;
		break;
	}

	_moveRc = RectMakeCenter(_movePosX, _movePosY, _image->getFrameWidth(), _image->getFrameHeight());
}

void Monster::attack(void){
}

void Monster::imgUpdate(void){
}

void Monster::rectUpdate(void){
}

void Monster::draw(void)
{
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		//인식렉트
		//Rectangle(getMemDC(),
		//_recognitionRc.left - CAM->getScreenRect().left,
		//_recognitionRc.top - CAM->getScreenRect().top,
		//_recognitionRc.right - CAM->getScreenRect().left,
		//_recognitionRc.bottom - CAM->getScreenRect().top
		//);

		 //이동렉트
		//Rectangle(getMemDC(),
		//	_moveRc.left - CAM->getScreenRect().left,
		//	_moveRc.top - CAM->getScreenRect().top,
		//	_image->getFrameWidth() + _moveRc.left - CAM->getScreenRect().left,
		//	_image->getFrameHeight() + _moveRc.top - CAM->getScreenRect().top
		//);

		 //피격렉트
		Rectangle(getMemDC(),
			_collision.defRc.left - CAM->getScreenRect().left,
			_collision.defRc.top - CAM->getScreenRect().top,
			_collision.defRc.right - CAM->getScreenRect().left,
			_collision.defRc.bottom - CAM->getScreenRect().top
		);

		// 타격렉트(이펙트 범위)
		Rectangle(getMemDC(),
			_collision.atkRc.left - CAM->getScreenRect().left,
			_collision.atkRc.top - CAM->getScreenRect().top,
			_collision.atkRc.right - CAM->getScreenRect().left,
			_collision.atkRc.bottom - CAM->getScreenRect().top
		);

		//임시 플레이어 드로우렉트
		Rectangle(getMemDC(),
			DATAMANAGER->getPlayer()->getPlayer().drawRc.left - CAM->getScreenRect().left,
			DATAMANAGER->getPlayer()->getPlayer().drawRc.top - CAM->getScreenRect().top,
			DATAMANAGER->getPlayer()->getPlayer().drawRc.right - CAM->getScreenRect().left,
			DATAMANAGER->getPlayer()->getPlayer().drawRc.bottom - CAM->getScreenRect().top
		);

		RECT tempPos, tempPos2, tempPos3, tempPos4, tempPos5;
		tempPos = RectMakeCenter(_movePosX, _movePosY, 4, 4);
		Rectangle(getMemDC(), tempPos.left - CAM->getScreenRect().left, tempPos.top - CAM->getScreenRect().top,
			tempPos.left - CAM->getScreenRect().left + 4, tempPos.top - CAM->getScreenRect().top + 4);

		// 픽셀충돌 아래 - 를 좌우로 뿌리기 
		tempPos2 = RectMakeCenter(_movePosX, _pixel.probeUp, 4, 4);
		Rectangle(getMemDC(), tempPos2.left - CAM->getScreenRect().left, tempPos2.top - CAM->getScreenRect().top,
			tempPos2.left - CAM->getScreenRect().left + 4, tempPos2.top - CAM->getScreenRect().top + 4);

		tempPos3 = RectMakeCenter(_movePosX, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos3.left - CAM->getScreenRect().left, tempPos3.top - CAM->getScreenRect().top,
			tempPos3.left - CAM->getScreenRect().left + 4, tempPos3.top - CAM->getScreenRect().top + 4);
		// 픽셀충돌 좌
		tempPos4 = RectMakeCenter(_pixel.probeLeft, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos4.left - CAM->getScreenRect().left, tempPos4.top - CAM->getScreenRect().top,
			tempPos4.left - CAM->getScreenRect().left + 4, tempPos4.top - CAM->getScreenRect().top + 4);
		// 픽셀충돌 우
		tempPos5 = RectMakeCenter(_pixel.probeRight, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos5.left - CAM->getScreenRect().left, tempPos5.top - CAM->getScreenRect().top,
			tempPos5.left - CAM->getScreenRect().left + 4, tempPos5.top - CAM->getScreenRect().top + 4);
	}

	_image->frameRender(getMemDC(),
		_moveRc.left - CAM->getScreenRect().left,
		_moveRc.top - CAM->getScreenRect().top,
		_frameX, _frameY);
}

