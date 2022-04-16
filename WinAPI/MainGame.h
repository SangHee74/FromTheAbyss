#pragma once
#include "GameNode.h"

/*
F2 : 픽셀충돌 토글
F3 : 몬스터 인식범위, 피격범위, 타격범위 토글
*/

class MainGame :public GameNode
{
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	MainGame() {}
	~MainGame() {}
};

