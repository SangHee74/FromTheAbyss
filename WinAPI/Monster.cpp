#include "Stdafx.h"
#include "Monster.h"

Monster::Monster() : _moveRc(RectMake(0, 0, 0, 0)),
					 _movePosX(0.0f),
					 _movePosY(0.0f),
					 _frameX(0),
					 _frameY(0),
					 _rndTimeCount(0.0f),
					 _worldTimeCount(0.0f)
{
}

HRESULT Monster::init(void)
{
	return S_OK;
}

HRESULT Monster::init(POINT position)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);

	_moveRc = RectMakeCenter(position.x, position.y,
		_image->getFrameWidth(), _image->getFrameHeight());

	_movePosX = position.x;
	_movePosY = position.y;
	_speed = 0.0f;

	return S_OK;
}

HRESULT Monster::init(const char * imageName, POINT position)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);

	_image = IMAGEMANAGER->findImage(imageName);
	_moveRc = RectMakeCenter(position.x, position.y,
		_image->getFrameWidth(), _image->getFrameHeight());

	_movePosX = position.x;
	_movePosY = position.y;
	_speed = 0.0f;

	return S_OK;
}

void Monster::release(void)
{
}

void Monster::update(void)
{
	move();
}

void Monster::render(void)
{
	draw();
	animation();
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
	_image->frameRender(getMemDC(), _moveRc.left, _moveRc.top,
		_frameX, _frameY);
}

void Monster::animation(void)
{
	if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		_frameX++;
		if (_image->getMaxFrameX() < _frameX)
		{
			_frameX = 0;
		}
	}

}


