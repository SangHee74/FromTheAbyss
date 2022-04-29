#pragma once
#include "GameNode.h"
#include "EnemyManager.h"
#include "Effect.h"
#include "ProgressBar.h"
#include "SubMenu.h"


class Stage14 : public GameNode
{
private:
	EnemyManager* _enemyM;
	ProgressBar* _UIBar;
	ProgressBarBoss* _bossUIBar;
	SubMenu* _subScreen;
	
	Effect* _monsterEff;
	Effect* _playerEff;
	PlayerEffect* _playerEff2;

	int _playerRndDmg; // Random Damage
	int _monsterRndDmg;
	int _tempMonsterNum; // render order check

	bool _lastStageGate;
	bool _dmgSettingOk;

	tagSceneFadeOut fadeOut;

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
	void damageSetting();
	void getPlayerAngleAndDistance(int i);
	void renderCheck();

	//SubMenu* getSubMenu() { return _subScreen; }

};

