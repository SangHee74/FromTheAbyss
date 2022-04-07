#pragma once
#include "GameNode.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ProgressBar.h"
#include "SubMenu.h"

class Abyss;

class Stage :public GameNode
{
private:

	Abyss* _Abyss;
	Player* _player;
	EnemyManager* _em;
	ProgressBar* _UIBar;
	SubMenu* _subScreen;
	
	int _alpha;

	//int _currentAbyss;
	//int _currentStage;

public:
	Stage() {}
	~Stage() {}
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

