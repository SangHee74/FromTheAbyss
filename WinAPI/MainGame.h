#pragma once
#include "GameNode.h"

/*

Debug x86


���� Ȯ�ν� PCH���� â��� -> �������� ��ȯ

---

F2 : �ȼ��浹, �÷��̾� �ǰݹ���, Ÿ�ݹ��� ���
F3 : ���� �νĹ���, �ǰݹ���, Ÿ�ݹ��� ���

--- ���� �� ��� ��� Ȯ�� 
1 : �÷��̾� �� ����
2 : �÷��̾� ���� ����
3 : �÷��̾� â ���� 

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

