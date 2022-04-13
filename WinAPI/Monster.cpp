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
	_monster.speed = 0.0f;


	_monster.moveRc = RectMakeCenter(position.x, position.y,
		_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
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
	_monster.frameX = 0;
	_monster.frameY = 0;

	_monster.movePosX = position.x;
	_monster.movePosY = position.y;
	_monster.speed = 0.0f;

	_monster.moveRc = RectMakeCenter(position.x, position.y,
		_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
	return S_OK;
}

void Monster::release(void)
{
}

void Monster::update(void)
{
	move();


	if (_state == MONSTERSTATE::DEF)
	{
		timeCount += TIMEMANAGER->getElapsedTime();

		if (timeCount >= 1.0f)
		{
			timeCount = 0;
			_state = MONSTERSTATE::IDLE;
		}
	}


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
	// 피격렉트
	Rectangle(getMemDC(),
		_collision.defRc.left - CAM->getScreenRect().left,
		_collision.defRc.top - CAM->getScreenRect().top,
		_collision.defRc.right - CAM->getScreenRect().left,
		_collision.defRc.bottom - CAM->getScreenRect().top
	);

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

void Monster::setAttackRc()
{
	// 오버라이딩
}


