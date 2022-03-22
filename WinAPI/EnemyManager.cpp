#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Rocket.h"

HRESULT EnemyManager::init(void)
{

	IMAGEMANAGER->addFrameImage("적비행기", "Resources/Images/Object/yellow.bmp",
		0.0f, 0.0f, 763,41, 16, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("적 미사일", "Resources/Images/Object/Bullet.bmp",
		7 * 2, 7 * 2, true, RGB(255, 0, 255));

	//미니언 생성
	setMinion();


	_bullet = new Bullet;
	_bullet->init("적 미사일", 30, 1000);

	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}

	_bullet->release();
	SAFE_DELETE(_bullet);
}

void EnemyManager::update(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	minionBulletFire();

	_bullet->update();

	//collision();
}

void EnemyManager::render(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
}

void EnemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion;
			jellyFish->init("적비행기", PointMake(100 + j * 100, 100 + i * 100));
			_vMinion.push_back(jellyFish);
		}
	}
}

void EnemyManager::removeMinion(int arrNum)
{

	// at(arrNum)을 안쓰는 이유는 끝까지 하나하나 찾고
	// 배열은 뒤는 안보고 숫자까지만 돔 
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void EnemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();

			//받아들이는데 시간이 필요할 것 같다..
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2,
					_rocket->getPosition().x,
					_rocket->getPosition().y),
				RND->getFromFloatTo(2.0f, 4.0f));
		}
	}
}

void EnemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
			&_rocket->getRect()))
		{
			_bullet->removeBullet(i);
			_rocket->hitDamage(0.05f);
		}
	}
}


