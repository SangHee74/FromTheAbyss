#pragma once
#include "GameNode.h"

class Title :public GameNode
{
private:
	RECT _startRc;

	// 씬 전환용 페이드아웃
	tagSceneFadeOut fadeOut;
public:
	Title() {}
	~Title() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

