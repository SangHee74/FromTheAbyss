#pragma once
#include "GameNode.h"

class Title :public GameNode
{
private:
	RECT _startRc;

	// �� ��ȯ�� ���̵�ƿ�
	tagSceneFadeOut fadeOut;
public:
	Title() {}
	~Title() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

