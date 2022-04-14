#include "Stdafx.h"
#include "Monster.h"

Monster::Monster()
{
}



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
	if(_state == MONSTERSTATE::ATT) attack();  // 미작성

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