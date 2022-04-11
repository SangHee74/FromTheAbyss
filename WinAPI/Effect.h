#pragma once
#include "GameNode.h"


struct tagEffect
{
	Image* img;
	RECT rc;
	int count;
	float x, y;
};

class PlayerEffect :public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	PlayerEffect() {}
	~PlayerEffect() {}
};


class MosterEffect :public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	MosterEffect() {}
	~MosterEffect() {}
};
