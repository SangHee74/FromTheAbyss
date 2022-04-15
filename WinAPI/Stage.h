#pragma once
#include "GameNode.h"
#include "EnemyManager.h"
#include "Effect.h"
#include "ProgressBar.h"
#include "SubMenu.h"


class Stage : public GameNode
{
protected:
	EnemyManager* _enemyM;
	MonsterEffect* _enemyEff;
	PlayerEffect* _playerEff;
	ProgressBar* _UIBar;
	ProgressBarBoss* _bossUIBar;
	SubMenu* _subScreen;

	tagEnterStageTextImage _enterInfo;

	bool _lastStageGate;
	int _tempMonsterNum;


public:
	Stage() {}
	~Stage() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void portalOn();
	virtual void collision();
	void getPlayerAngleAndDistance(int i);
	void renderCheck();
	int playerRandomDamage();
	int monsterRandomDamage(int i);
};

