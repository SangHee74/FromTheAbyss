#pragma once
#include "GameNode.h"
#include "Player.h"
#include "ProgressBar.h"

class Stage :public GameNode
{
private:

	Player* _player;
	ProgressBar* _UIBar;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

