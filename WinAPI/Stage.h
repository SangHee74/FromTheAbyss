#pragma once
#include "GameNode.h"
#include "Player.h"
#include "ProgressBar.h"
#include "SubMenu.h"

class Stage :public GameNode
{
private:

	Player* _player;
	ProgressBar* _UIBar;
	SubMenu* _subScreen;
	
	int _alpha;

public:
	Stage() {}
	~Stage() {}
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

