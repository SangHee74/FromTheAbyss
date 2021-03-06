#pragma once
#include "GameNode.h"
#include "EnemyManager.h"
#include "Effect.h"
#include "ProgressBar.h"
#include "SubMenu.h"


class Stage11 : public GameNode
{
private:
	EnemyManager* _enemyM;
	//Effect* _enemyEff;
	Effect* _playerEff;
	ProgressBar* _UIBar;
	SubMenu* _subScreen;
	
	tagEnterStageTextImage _enterInfo;

	tagSceneFadeOut fadeOut;
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

