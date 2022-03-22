#pragma once
#include "GameNode.h"

class Square :public GameNode
{
private:
	POINT _mugPos;


public:
	Square() {}
	~Square() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};


