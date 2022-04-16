#pragma once
#include "GameNode.h"

class SubStatus : public GameNode
{
private:


public:
	SubStatus() {}
	~SubStatus() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void showNumberImgAlignLeft(int number, int destX, int destY);
};

