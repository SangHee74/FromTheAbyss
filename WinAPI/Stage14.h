#pragma once
#include "GameNode.h"
#include "Stage.h"
#include "EnemyManager.h"
#include "ProgressBar.h"
#include "SubMenu.h"


class Stage14 : public GameNode
{
private:
	EnemyManager* _enemyM;
	ProgressBar* _UIBar;
	ProgressBarBoss* _bossUIBar;
	SubMenu* _subScreen;

	tagEnterStageTextImage _enterInfo;

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
	int playerRandomDamage();
	int monsterRandomDamage(int i);


};

