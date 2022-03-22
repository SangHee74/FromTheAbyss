#pragma once
#include "GameNode.h"

class Store :public GameNode
{
private:



public:
	Store() {}
	~Store() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

