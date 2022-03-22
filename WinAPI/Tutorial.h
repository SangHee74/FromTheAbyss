#pragma once
#include "GameNode.h"

class Tutorial :public GameNode
{
private:



public:
	Tutorial() {}
	~Tutorial() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
