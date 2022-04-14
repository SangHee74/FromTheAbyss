#include "Stdafx.h"
#include "Monster.h"

Monster::Monster(): _maxHp(0), _curHp(0), _curAtt(0),
					_dropExp(0), _dropLufia(0), _dropItemIndex(0),
					_moveRc(RectMake(0,0,0,0)), 
					_recognitionRc(RectMake(0, 0, 0, 0)),
					_movePosX(0), _movePosY(0),
					_frameX(0), _frameY(0),
					_speed(0), _distance(0), _angle(0),
					_rndTimeCount(0), _worldTimeCount(0),
					_playerCheck(false) , _image(nullptr)
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

	// 스테이터스 관련
	_maxHp = 0;
	_curHp = 0;
	_curAtt = 0;
	_dropExp = 0;
	_dropLufia = 0;
	_dropItemIndex = 0;

	// 이동 및 업데이트 관련 
	_movePosX = position.x;
	_movePosY = position.y;
	_frameX = 0;
	_frameY = 0;
	_speed = 5;
	_distance = 0;
	_angle = 0.0f;

	// 렉트 초기화
	// 이동렉트(프레임렌더), 인식렉트, 타격범위렉트, 피격범위렉트 
	_moveRc = RectMakeCenter(_movePosX, _movePosY, 30, 30);
	_recognitionRc = RectMakeCenter(_movePosX, _movePosY, 100, 100);
	_collision.attRc = RectMakeCenter(_movePosX, _movePosY, 20, 20);
	//_collision.defRc; // 몬스터는 이동렉트와 피격범위 함께 사용.

	// 프레임 업데이트, 공격상태 체크 등 
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_worldTimeCount = GetTickCount();
	_attCoolTime = 0.0f;

	// 몬스터의 인식범위에 플레이어가 있는지 체크 
	_playerCheck = false;



	return S_OK;
}

HRESULT Monster::init(const char* imageName, POINT position)
{
	// 임시변수 
	timeCount = 0.0f;

	// 이미지 지정
	_image= IMAGEMANAGER->findImage(imageName);

	// 스테이터스 관련
	_maxHp = 0;
	_curHp = 0;
	_curAtt = 0;
	_dropExp = 0;
	_dropLufia = 0;
	_dropItemIndex = 0;

	// 이동 및 업데이트 관련 
	_movePosX = position.x;
	_movePosY = position.y;
	_frameX = 0;
	_frameY = 0;
	_speed = 5;
	_distance = 0;
	_angle = 0.0f;

	// 렉트 초기화
	// 이동렉트(프레임렌더), 인식렉트, 타격범위렉트, 피격범위렉트 
	_moveRc = RectMakeCenter(_movePosX, _movePosY, 30, 30);
	_recognitionRc = RectMakeCenter(_movePosX, _movePosY, 100, 100);
	_collision.attRc = RectMakeCenter(_movePosX, _movePosY, 20, 20);
	//_collision.defRc; // 몬스터는 이동렉트와 피격범위 함께 사용.

	// 프레임 업데이트, 공격상태 체크 등 
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_worldTimeCount = GetTickCount();
	_attCoolTime = 0.0f;

	// 몬스터의 인식범위에 플레이어가 있는지 체크 
	_playerCheck = false;


	return S_OK;
}

void Monster::release(void)
{
}

void Monster::update(void)
{

	// 이동
	move();

	// 픽셀충돌
	pixelCollision();

	// 방향전환 + 렉트 초기화
	setDirection();
	rcUpdate();

	// 공격
	if (_state == MONSTERSTATE::ATT) attack();

	// 피격
	if (_state == MONSTERSTATE::DEF)
	{
		cout << "몬스터 피격 후 타임카운트 : " << timeCount << endl;
		timeCount += TIMEMANAGER->getElapsedTime();

		if (timeCount >= 1.0f)
		{
			timeCount = 0;
			_state = MONSTERSTATE::IDLE;
		}
	}

	// 대기, 이동 중 방향에 따라 프레임Y 변경
	if (_state == MONSTERSTATE::IDLE || _state == MONSTERSTATE::MOVE)
	{
		_frameY = static_cast<int>(_direction);
	}

	// 죽은 경우 충돌 범위 초기화
	if (_state == MONSTERSTATE::DEAD)
	{
		_collision.defWidth = _collision.defHeight = 0;
		_collision.defRc = RectMakeCenter(_movePosX, _movePosY, _collision.attWidth, _collision.attHeight);

		_collision.attWidth = _collision.attHeight = 0;
		_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
	}
}

void Monster::render(void)
{
	draw();
	animation();
	drawEffect();
}

void Monster::move(void)
{
	// 오버라이딩
}

void Monster::attack(void)
{
	// 오버라이딩
}

void Monster::draw(void)
{
	//인식렉트
	//Rectangle(getMemDC(),
	//	_monster.recognitionRc.left - CAM->getScreenRect().left,
	//	_monster.recognitionRc.top - CAM->getScreenRect().top,
	//	_monster.recognitionRc.right - CAM->getScreenRect().left,
	//	_monster.recognitionRc.bottom - CAM->getScreenRect().top
	//);

	// 피격렉트
	Rectangle(getMemDC(),
		_collision.defRc.left - CAM->getScreenRect().left,
		_collision.defRc.top - CAM->getScreenRect().top,
		_collision.defRc.right - CAM->getScreenRect().left,
		_collision.defRc.bottom - CAM->getScreenRect().top
	);

	// 타격렉트
	Rectangle(getMemDC(),
		_collision.attRc.left - CAM->getScreenRect().left,
		_collision.attRc.top - CAM->getScreenRect().top,
		_collision.attRc.right - CAM->getScreenRect().left,
		_collision.attRc.bottom - CAM->getScreenRect().top
	);

		// 이동렉트
	//Rectangle(getMemDC(),
	//	_monster.moveRc.left - CAM->getScreenRect().left,
	//	_monster.moveRc.top - CAM->getScreenRect().top,
	//	_monster.image->getFrameWidth() + _monster.moveRc.left - CAM->getScreenRect().left,
	//	_monster.image->getFrameHeight() + _monster.moveRc.top - CAM->getScreenRect().top
	//);




	_monster.image->frameRender(getMemDC(),
		_monster.moveRc.left-CAM->getScreenRect().left,
		_monster.moveRc.top - CAM->getScreenRect().top,
		_monster.frameX, _monster.frameY);

	//rcMake(getMemDC(), _moveRc);
}

void Monster::animation(void)
{
	if (_monster.rndTimeCount + _monster.worldTimeCount <= GetTickCount())
	{
		_monster.worldTimeCount = GetTickCount();
		_monster.frameX++;
		if (_monster.image->getMaxFrameX() < _monster.frameX)
		{
			_monster.frameX = 0;
		}
	}

}

void Monster::setDirection(void)
{
	
	if (_monster.playerCheck && _state != MONSTERSTATE::ATT)
	{
		// 플레이어 각도에 따라 방향 전환
		if (_monster.angle >= 45 * DTR && _monster.angle < 135 * DTR)
		{
			_direction = MONSTERDIRECTION::UP;
		}
		if (_monster.angle >= 135 * DTR	&& _monster.angle < 225 * DTR)
		{
			_direction = MONSTERDIRECTION::LEFT;
		}
		if (_monster.angle >= 225 * DTR	&& _monster.angle < 315 * DTR)
		{
			_direction = MONSTERDIRECTION::DOWN;
		}
		if (_monster.angle >= 315 * DTR || (_monster.angle >= 0 * DTR && _monster.angle < 45 * DTR))
		{
			_direction = MONSTERDIRECTION::RIGHT;
		}
	}
 
	if (_monster.image != nullptr)
	{
		_monster.moveRc = RectMakeCenter(_monster.movePosX, _monster.movePosX,
			_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
	}
}

void Monster::rcUpdate()
{
	// 오버라이딩
	// 방향별 타격, 피격 범위 재조정
}

void Monster::drawEffect(void)
{
	// 오버라이딩
}



void Monster::pixelCollision()
{
	//탐지
	_pixel.probeUp    = (_monster.movePosY + _monster.image->getFrameHeight() / 2) - 16;
	_pixel.probeDown  = (_monster.movePosY + _monster.image->getFrameHeight() / 2) - 8;
	_pixel.probeLeft  = _monster.movePosX - 20;
	_pixel.probeRight = _monster.movePosX + 20;

	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		if (pixelColorCheck(_monster.movePosX, _pixel.probeUp)) _monster.movePosY += _monster.speed;
		break;
	case MONSTERDIRECTION::DOWN:
		if (pixelColorCheck(_monster.movePosX, _pixel.probeUp)) _monster.movePosY -= _monster.speed;
		break;
	case MONSTERDIRECTION::LEFT:
		if (pixelColorCheck(_pixel.probeLeft, _pixel.probeDown)) _monster.movePosX += _monster.speed;
		break;
	case MONSTERDIRECTION::RIGHT:
		if (pixelColorCheck(_pixel.probeRight, _pixel.probeDown)) _monster.movePosX -= _monster.speed;
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

// 몬스터 수정 전 
#if 0

HRESULT Monster::init(void)
{
	return S_OK;
}

HRESULT Monster::init(POINT position)
{
	timeCount = 0.0f;

	_monster.worldTimeCount = GetTickCount();
	_monster.rndTimeCount = RND->getFromFloatTo(50, 150);

	_monster.movePosX = position.x;
	_monster.movePosY = position.y;
	_monster.frameX = 0;
	_monster.frameY = 0;
	_monster.speed = 2;
	_monster.distance = 0;
	_monster.angle = 0.0f;
	_monster.playerCheck = false;
	_monster.attCoolTime = 0.0f;

	_monster.moveRc = RectMakeCenter(position.x, position.y,
		_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
	//_monster.recognitionRc = RectMakeCenter(position.x, position.y,
	//	_monster.image->getFrameHeight()*3, _monster.image->getFrameHeight()*3);
	_collision.defRc = CollisionAreaResizing(_monster.moveRc, 40, 40);

	//RectMakeCenter(position.x, position.y,
	//_monster.image->getFrameWidth()-40, _monster.image->getFrameHeight()-40);
	return S_OK;
}

HRESULT Monster::init(const char* imageName, POINT position)
{
	_monster.worldTimeCount = GetTickCount();
	_monster.rndTimeCount = RND->getFromFloatTo(50, 150);

	_monster.image = IMAGEMANAGER->findImage(imageName);

	_monster.movePosX = position.x;
	_monster.movePosY = position.y;
	_monster.frameX = 0;
	_monster.frameY = 0;
	_monster.speed = 2;
	_monster.distance = 0;
	_monster.angle = 0.0f;
	_monster.playerCheck = false;
	_monster.attCoolTime = 0.0f;

	_monster.moveRc = RectMakeCenter(position.x, position.y,
		_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
	//_monster.recognitionRc = RectMakeCenter(position.x, position.y,
	//	_monster.image->getFrameHeight() * 3, _monster.image->getFrameHeight() * 3);
	_collision.defRc = CollisionAreaResizing(_monster.moveRc, 40, 40);


	return S_OK;
}

void Monster::release(void)
{
}

void Monster::update(void)
{
	move();
	setDirection();
	pixelCollision();
	if (_state == MONSTERSTATE::ATT) attack();  // 미작성

	if (_state == MONSTERSTATE::DEF)
	{
		timeCount += TIMEMANAGER->getElapsedTime();

		if (timeCount >= 1.0f)
		{
			timeCount = 0;
			_state = MONSTERSTATE::IDLE;
		}
	}

	if (_state == MONSTERSTATE::IDLE || _state == MONSTERSTATE::MOVE)
	{
		_monster.frameY = static_cast<int>(_direction);
	}

	if (_state == MONSTERSTATE::DEAD)
	{
		_collision.attWidth = _collision.attHeight = 0;
		_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
	}


	//cout << "몬스터 업데이트 ! " << endl;
}

void Monster::render(void)
{
	draw();
	animation();
	drawEffect();
}

void Monster::move(void)
{
	// 오버라이딩
}

void Monster::attack(void)
{
	// 오버라이딩
}

void Monster::draw(void)
{
	//인식렉트
	//Rectangle(getMemDC(),
	//	_monster.recognitionRc.left - CAM->getScreenRect().left,
	//	_monster.recognitionRc.top - CAM->getScreenRect().top,
	//	_monster.recognitionRc.right - CAM->getScreenRect().left,
	//	_monster.recognitionRc.bottom - CAM->getScreenRect().top
	//);

	// 피격렉트
	Rectangle(getMemDC(),
		_collision.defRc.left - CAM->getScreenRect().left,
		_collision.defRc.top - CAM->getScreenRect().top,
		_collision.defRc.right - CAM->getScreenRect().left,
		_collision.defRc.bottom - CAM->getScreenRect().top
	);

	// 타격렉트
	Rectangle(getMemDC(),
		_collision.attRc.left - CAM->getScreenRect().left,
		_collision.attRc.top - CAM->getScreenRect().top,
		_collision.attRc.right - CAM->getScreenRect().left,
		_collision.attRc.bottom - CAM->getScreenRect().top
	);

	// 이동렉트
//Rectangle(getMemDC(),
//	_monster.moveRc.left - CAM->getScreenRect().left,
//	_monster.moveRc.top - CAM->getScreenRect().top,
//	_monster.image->getFrameWidth() + _monster.moveRc.left - CAM->getScreenRect().left,
//	_monster.image->getFrameHeight() + _monster.moveRc.top - CAM->getScreenRect().top
//);




	_monster.image->frameRender(getMemDC(),
		_monster.moveRc.left - CAM->getScreenRect().left,
		_monster.moveRc.top - CAM->getScreenRect().top,
		_monster.frameX, _monster.frameY);

	//rcMake(getMemDC(), _moveRc);
}

void Monster::animation(void)
{
	if (_monster.rndTimeCount + _monster.worldTimeCount <= GetTickCount())
	{
		_monster.worldTimeCount = GetTickCount();
		_monster.frameX++;
		if (_monster.image->getMaxFrameX() < _monster.frameX)
		{
			_monster.frameX = 0;
		}
	}

}

void Monster::setDirection(void)
{

	if (_monster.playerCheck && _state != MONSTERSTATE::ATT)
	{
		// 플레이어 각도에 따라 방향 전환
		if (_monster.angle >= 45 * DTR && _monster.angle < 135 * DTR)
		{
			_direction = MONSTERDIRECTION::UP;
		}
		if (_monster.angle >= 135 * DTR	&& _monster.angle < 225 * DTR)
		{
			_direction = MONSTERDIRECTION::LEFT;
		}
		if (_monster.angle >= 225 * DTR	&& _monster.angle < 315 * DTR)
		{
			_direction = MONSTERDIRECTION::DOWN;
		}
		if (_monster.angle >= 315 * DTR || (_monster.angle >= 0 * DTR && _monster.angle < 45 * DTR))
		{
			_direction = MONSTERDIRECTION::RIGHT;
		}
	}

	if (_monster.image != nullptr)
	{
		_monster.moveRc = RectMakeCenter(_monster.movePosX, _monster.movePosX,
			_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
	}
}

void Monster::setCollisionRange()
{
	// 오버라이딩
	// 방향별 타격, 피격 범위 재조정
}

void Monster::drawEffect(void)
{
	// 오버라이딩
}



void Monster::pixelCollision()
{
	//탐지
	_pixel.probeUp = (_monster.movePosY + _monster.image->getFrameHeight() / 2) - 16;
	_pixel.probeDown = (_monster.movePosY + _monster.image->getFrameHeight() / 2) - 8;
	_pixel.probeLeft = _monster.movePosX - 20;
	_pixel.probeRight = _monster.movePosX + 20;

	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		if (pixelColorCheck(_monster.movePosX, _pixel.probeUp)) _monster.movePosY += _monster.speed;
		break;
	case MONSTERDIRECTION::DOWN:
		if (pixelColorCheck(_monster.movePosX, _pixel.probeUp)) _monster.movePosY -= _monster.speed;
		break;
	case MONSTERDIRECTION::LEFT:
		if (pixelColorCheck(_pixel.probeLeft, _pixel.probeDown)) _monster.movePosX += _monster.speed;
		break;
	case MONSTERDIRECTION::RIGHT:
		if (pixelColorCheck(_pixel.probeRight, _pixel.probeDown)) _monster.movePosX -= _monster.speed;
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
#endif