#pragma once
#include "GameNode.h"
#include "Stage.h"
#include "EnemyManager.h"
#include "Effect.h"
#include "ProgressBar.h"
#include "SubMenu.h"


class Stage14 : public GameNode
{
private:
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
	Stage14() {}
	~Stage14() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void enterInfoCheck();
	void portalOn();
	void collision();
	void getPlayerAngleAndDistance(int i);
	void renderCheck();

	//SubMenu* getSubMenu() { return _subScreen; }

};

