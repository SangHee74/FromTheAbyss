#pragma once
#include "GameNode.h"
#include "EnemyManager.h"
#include "ProgressBar.h"
#include "SubMenu.h"
#include "Effect.h"

enum DAMAGEDIGITS
{
	UNIT_DIGITS, TENS_DIGITS, HUNDRED_DIGITS,
	DIGITS_END
};

struct tagDamageData
{
	Image* hundred;
	Image* tens;
	Image* unit;
	int damage;
	POINT pos[DIGITS_END];
	bitset<3> fontColor; // RGB 
};

class Stage :public GameNode
{
private:
	EnemyManager* _em;
	ProgressBar* _UIBar;
	PlayerEffect* _playereEffect;
	MosterEffect* _monsterEffect;
	SubMenu* _subScreen;
	
	int _alpha;

public:
	Stage() {}
	~Stage() {}
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void portalOn();
	void collision();
	int playerRandomDamage();
	int monsterRandomDamage(int i);
};

