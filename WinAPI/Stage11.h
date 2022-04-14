#pragma once
#include "GameNode.h"
#include "Stage.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "ProgressBar.h"
#include "SubMenu.h"


class Stage11 : public GameNode
{
private:
	EnemyManager* _enemyM;
	EffectManager* _effectM;
	ProgressBar* _UIBar;
	SubMenu* _subScreen;
	
	tagEnterStageTextImage _enterInfo;

public:
	Stage11() {}
	~Stage11() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void enterInfoCheck();
	void portalOn();
	void collision();



};

