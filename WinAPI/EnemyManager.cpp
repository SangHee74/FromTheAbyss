#include "Stdafx.h"
#include "EnemyManager.h"

HRESULT EnemyManager::init(void)
{
	setMoster();

	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		(*_viMonster)->release();
		SAFE_DELETE(*_viMonster);
	}
}

void EnemyManager::update(void)
{
	_viMonster = _vMonster.begin();
	for (; _viMonster != _vMonster.end(); ++_viMonster)
	{
		(*_viMonster)->update();
	}
}

void EnemyManager::render(void)
{
	_viMonster = _vMonster.begin();
	for (; _viMonster != _vMonster.end(); ++_viMonster)
	{
		(*_viMonster)->render();
	}
}

void EnemyManager::setMoster(void)
{
	for (int i = 0; i < 5 ; i++)
	{
		Monster* dionaea;
		dionaea = new Dionaea;
		
		// 생성자에서 이미지까지 초기화 중. 

		//dionaea->init("Dionaea_idle", PointMake(150 + i * 200, 100 + i * 100));
		dionaea->init(PointMake(150 + i * 200, 100 + i * 100));








		_vMonster.push_back(dionaea);
	}



}

void EnemyManager::removeMonster(int arrNum)
{
	SAFE_DELETE(_vMonster[arrNum]);
	_vMonster.erase(_vMonster.begin() + arrNum);
}

void EnemyManager::monsterAttack(void)
{
	// 수정중
	//if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	//{
	//	_bulletFireCount = TIMEMANAGER->getWorldTime();
	//	_rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);
	//
	//	return true;
	//}

	//return false;
}

void EnemyManager::collision(void)
{
}
