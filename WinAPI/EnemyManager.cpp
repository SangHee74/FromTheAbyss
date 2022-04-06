#include "Stdafx.h"
#include "EnemyManager.h"
#include "Stage.h"

HRESULT EnemyManager::init(void)
{

	return S_OK;
}

HRESULT EnemyManager::init(int abyss, int stage)
{
	setMoster(abyss, stage);

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

void EnemyManager::loadMonsterPos()
{
	vector<string> vData = TEXTDATAMANAGER->load("Resources/stagePos.txt");

	for (int i = 0; i < ABYSS_MAX*STAGE_MAX; i += STAGE_MONSTER_POS_MAX)
	{
		for (int j = 0; j < STAGE_MONSTER_POS_MAX; j++)
		{
			_monsterPos[i*j +j ].pos[i*j + j].x = atoi(vData[i*j + j].c_str());
			_monsterPos[i*j + j].pos[i*j + j].y = atoi(vData[i*j + j+1].c_str());
			_monsterPos[i*j + j].inPos[i*j + j] = false;

			cout << i << endl;
		}
	}
}

void EnemyManager::setMoster(int abyss, int stage)
{

	loadMonsterPos();

	int currentAbyss = 10* abyss;
	int currentStage = 1* stage;

	switch (currentAbyss + currentStage)
	{
	case 11:
		for (int i = 0; i < 5; i++)
		{
			Monster* dionaea;
			dionaea = new Dionaea;

			// 식충식물 
			dionaea->init(PointMake(150 + i * 200, 100 + i * 100));

			_vMonster.push_back(dionaea);
		}
		for (int i = 0; i < 5; i++)
		{
			Monster* evilEye;
			evilEye = new EvilEye;

			// 외눈박이
			evilEye->init();

			_vMonster.push_back(evilEye);

		}
		break;
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








