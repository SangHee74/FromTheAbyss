#include "Stdafx.h"
#include "Effect.h"


Effect::Effect() : _count(0)
{
}

HRESULT Effect::init(void)
{
	return S_OK;
}

HRESULT Effect::init(const char* imageKey, RECT rc)
{
	_image = IMAGEMANAGER->findImage(imageKey);
	_x = rc.left + (rc.right - rc.left) / 2;
	_y = rc.top;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_onEffect = true;

	return S_OK;
}

void Effect::release(void)
{

}

void Effect::update(void)
{
}

void Effect::render(void)
{
	draw();
	animation();
}


void Effect::draw(void)
{
	_image->frameRender(getMemDC(),
		_rc.left - CAM->getScreenRect().left, _rc.top - CAM->getScreenRect().top, _curFrameX, _curFrameY);
}

void Effect::animation(void)
{
	_count++;

	if (_count % 10 == 0)
	{
		if (_curFrameX == _image->getMaxFrameX())
		{
			_curFrameX = 0;
		}
		else
		{
			_curFrameX++;
		}

		if (_image->getMaxFrameY() < _curFrameY)
		{
			_onEffect = false;
		}
	}
}


void Effect::centerDamageEffect(int damage, POINT pos, DAMAGECOLOR color)
{
	// 기본 화이트
	Image* damageFontImg = IMG("Num_W");
	int tempX = 18;
	//int tempY = 0;

	switch (color)
	{
	case DAMAGECOLOR::DAMAGE_RED:
		damageFontImg = IMG("Num_R");
		break;
	case DAMAGECOLOR::DAMAGE_GREEN:
		damageFontImg = IMG("Num_G");
		break;
	case DAMAGECOLOR::DAMAGE_BLUE:
		damageFontImg = IMG("Num_B");
		break;
	}

	// 최대 9999
	if (damage > 999)		 damageFontImg->frameRender(getMemDC(), pos.x - tempX * 2, pos.y, damage / 1000 % 10, 0);
	if (damage > 99)		 damageFontImg->frameRender(getMemDC(), pos.x - tempX, pos.y, damage / 100 % 10, 0);
	if (damage > 9)			 damageFontImg->frameRender(getMemDC(), pos.x, pos.y, damage / 10 % 10, 0);
							 damageFontImg->frameRender(getMemDC(), pos.x + tempX, pos.y, damage % 10, 0);
	if (damage <= 0)		 damageFontImg->frameRender(getMemDC(), pos.x + tempX, pos.y, 0, 0);
}


