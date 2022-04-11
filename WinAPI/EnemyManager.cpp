#include "Stdafx.h"
#include "EnemyManager.h"
#include "Stage.h"

HRESULT EnemyManager::init(void)
{
	loadMonsterPos();
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

void EnemyManager::loadMonsterPos()
{
	vector<string> vData = TEXTDATAMANAGER->load("Resources/stagePos.txt");

	for (int i = 0; i < ABYSS_MAX*STAGE_MAX; i++)
	{
		for (int j = 0; j < STAGE_MONSTER_POS_MAX; j++)
		{
			_monsterPos[i].mapPos[j].index = (20 * i) + j ;
			_monsterPos[i].mapPos[j].posX = atoi(vData[((20 * i) + j) * 2].c_str());
			_monsterPos[i].mapPos[j].posY = atoi(vData[(((20 * i) + j) * 2) + 1].c_str());
			_monsterPos[i].mapPos[j].inMonster = false;
		}
	}
}

void EnemyManager::setMoster()
{
	int currentAbyss = DATAMANAGER->getMapData().enterAbyssInfo.abyss;
	int currentStage = DATAMANAGER->getMapData().enterAbyssInfo.stage;

	switch (currentAbyss)
	{
		// ���-��������(index����)
		// ex :  11(0~19) 12(20~39) 13(40~59) 14(60~79)
		//		 21(80~99) 22(100~119) 23(120~139) 24(140~159)
	case 1:
		if (currentStage == 1)
		{

			// �ǰ� �׽�Ʈ �� 
			Monster* dionaea;
			dionaea = new Dionaea;

			// ����Ĺ� 
			dionaea->init({ 280, 330 });
			_vMonster.push_back(dionaea);




			for (int i = 0; i < 9; i++)
			{
				Monster* dionaea;
				dionaea = new Dionaea;

				// ����Ĺ� 
				dionaea->init(monsterRandomPos(11, 5));
				_vMonster.push_back(dionaea);
			}

			for (int i = 0; i < 9; i++)
			{
				Monster* evilEye;
				evilEye = new EvilEye;

				// �ܴ�����
				evilEye->init(monsterRandomPos(11, 5));
				_vMonster.push_back(evilEye);

			}
		}
		if (currentStage == 2)
		{
			cout << "���1-��������2 ���� �̱���!" << endl;
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
	// ������
	//if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	//{
	//	_bulletFireCount = TIMEMANAGER->getWorldTime();
	//	_rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);
	//
	//	return true;
	//}

	//return false;
}

// ���� ������ ��ǥ ��������
POINT EnemyManager::monsterRandomPos(int abyssStage, int monsterCount)
{


	// �������� ������ �ε����� ��ǥ
	int count=0; // ���� ī��Ʈ��ŭ ��ǥ�� �����ߴ��� üũ 
	int rndIndex = 0;
	POINT rndPos = { 0,0 };

	//�Ű�����: ��� - �������� - (index���� �����)
	switch (abyssStage)
	{
	case 11:
	rndIndex = RND->getFromIntTo(0, 19);
		for (int i = 0; i < monsterCount; i++)
		{
			if (monsterCount != count)
			{
				for (int j = 0; j < STAGE_MONSTER_POS_MAX; j++)
				{
					// ! �����ε����� ���Ͱ� �ִٸ� ��ŵ
					if (_monsterPos[0].mapPos[rndIndex].inMonster) continue;
					else // �����ε����� ���Ͱ� ���ٸ� ��ǥ�Է� �� true ����
					{
						rndPos.x = _monsterPos[0].mapPos[rndIndex].posX;
						rndPos.y = _monsterPos[0].mapPos[rndIndex].posY;
						_monsterPos[0].mapPos[rndIndex].inMonster = true;
						count++;
						break;
					}
				}
			}
			else break;
		}
		break;
	}
	// ����Ʈ�� ���� ��ȯ�ϸ� init�� �Լ� �ٷ� ��� ����
	return PointMake(rndPos.x, rndPos.y);
}






