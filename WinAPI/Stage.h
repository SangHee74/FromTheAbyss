#pragma once
#include "GameNode.h"
#include "Player.h"
#include "ProgressBar.h"
#include "SubMenu.h"
#include "EnemyManager.h"

class Stage :public GameNode
{
private:

	Player* _player;
	ProgressBar* _UIBar;
	SubMenu* _subScreen;
	EnemyManager* _em;
	
	int _alpha;

	int _currentAbyss;
	int _currentStage;

public:
	Stage() {}
	~Stage() {}
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

