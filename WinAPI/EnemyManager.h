#pragma once
#include "GameNode.h"
#include "Monster.h"
#include "FieldMonster.h"
#include "BossMonster.h"


#define STAGE_MONSTER_POS_MAX 20
#define ABYSS_MAX 2
#define STAGE_MAX 4

struct tagCreateMonsterPos
{
	POINT pos[STAGE_MONSTER_POS_MAX];
	bool inPos[STAGE_MONSTER_POS_MAX];
};

class Stage;

class EnemyManager : public GameNode
{
private:
	typedef vector<Monster*> vMonster;
	typedef vector<Monster*>::iterator viMoster;

private:
	vMonster _vMonster;
	viMoster _viMonster;

	tagCreateMonsterPos _monsterPos[ABYSS_MAX*STAGE_MAX];

public:
	HRESULT init(void);
	HRESULT init(int abyss, int stage);
	void release(void);
	void update(void);
	void render(void);

	void loadMonsterPos();
	void setMoster(int abyss, int stage);
	void removeMonster(int arrNum);

	void monsterAttack(void);
	//void collision(void);

	vector<Monster*> getMonsters(void) { return _vMonster; }

	EnemyManager() {}
	~EnemyManager() {}
};

