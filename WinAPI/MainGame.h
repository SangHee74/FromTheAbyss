#pragma once
#include "GameNode.h"

/*
F2 : �ȼ��浹 ���
F3 : ���� �νĹ���, �ǰݹ���, Ÿ�ݹ��� ���
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

