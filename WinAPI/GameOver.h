#pragma once
#include "GameNode.h"

class GameOver :public GameNode
{
private:
	RECT _returnRc;
	int _count;


	// �� ��ȯ�� ���̵�ƿ�
	tagSceneFadeOut fadeOut;
public:
	GameOver() {}
	~GameOver() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
