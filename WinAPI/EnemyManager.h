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
	int index;
	int posX;
	int posY;
	bool inMonster;
};

struct tagMapPos
{
	// 맵 한개에서 만들어지는 pos는 20개
	tagCreateMonsterPos mapPos[STAGE_MONSTER_POS_MAX];
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

	// 던전*스테이지 수 만큼 몬스터 좌표세트가 만들어짐
	tagMapPos _monsterPos[ABYSS_MAX*STAGE_MAX];

public:
	EnemyManager() {}
	~EnemyManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadMonsterPos();
	void setMoster();
	void removeMonster(int arrNum);

	void monsterAttack(void);
	POINT monsterRandomPos(int abyssStage, int monsterCount);
	int monsterRandomDamage(int i);

	vector<Monster*> getMonsters(void) { return _vMonster; }

};

