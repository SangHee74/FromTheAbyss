#pragma once
#include "GameNode.h"

class GameOver :public GameNode
{
private:
	RECT _returnRc;
	int _count;


	// 씬 전환용 페이드아웃
	tagSceneFadeOut fadeOut;
public:
	GameOver() {}
	~GameOver() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
