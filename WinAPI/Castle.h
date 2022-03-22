#pragma once
#include "GameNode.h"

class Castle :public GameNode
{
private:



public:
	Castle() {}
	~Castle() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
