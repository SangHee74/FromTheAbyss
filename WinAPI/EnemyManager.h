#pragma once
#include "GameNode.h"
#include "Monster.h"
#include "FieldMonster.h"
#include "BossMonster.h"
#include "player.h"

class EnemyManager : public GameNode
{
private:
	typedef vector<Monster*> vMonster;
	typedef vector<Monster*>::iterator viMoster;

private:
	vMonster _vMonster;
	viMoster _viMonster;

	Player* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMoster(void);
	void removeMonster(int arrNum);

	void monsterAttack(void);
	void collision(void);

	// � ��ü�� �浹 �ߴ��� ���� ������ �Ѱ��ش�.
	vector<Monster*> getMonsters(void) { return _vMonster; }
	void setPlayerMemoryAddress(Player* player) { _player = player; }

	EnemyManager() {}
	~EnemyManager() {}
};

