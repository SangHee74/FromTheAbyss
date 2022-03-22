#pragma once
#include "GameNode.h"
#include "Player.h"

class Stage :public GameNode
{
private:

	Player* _player;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

