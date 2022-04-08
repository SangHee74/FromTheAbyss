#pragma once
#include "GameNode.h"
class Title :public GameNode
{
private:
	RECT _startRc;
	int _alpha;
	bitset<2> _fadeout;

public:
	Title() {}
	~Title() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

