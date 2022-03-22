#include "Stdafx.h"
#include "Enemy.h"


Enemy::Enemy() :_rc(RectMake(0, 0, 0, 0)),
_currentFrameX(0),
_currentFrameY(0),
_x(0.0f),
_y(0.0f),
_rndTimeCount(0.0f),
_worldTimeCount(0.0f),
_bulletFireCount(0.0f)
{
}

HRESULT Enemy::init(void)
{
	// Do Nothing!
	return S_OK;
}


HRESULT Enemy::init(const char * imageName, POINT position)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);


	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void Enemy::release(void)
{
}

void Enemy::update(void)
{
	move();
}

void Enemy::render(void)
{
	draw();
	animation();
}

//´Ë
void Enemy::move(void)
{
}

void Enemy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
}

void Enemy::animation(void)
{
	//¹¬¾ð ¼öÇà
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
}

bool Enemy::bulletCountFire(void)
{
	if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);

		return true;
	}

	return false;
}

