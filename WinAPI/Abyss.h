#pragma once
#include "GameNode.h"

enum BUTTONNUM
{
	BUTTON_ONE,
	BUTTON_TWO,
	BUTTON_THREE,
	BUTTON_END
};

class Abyss :public GameNode
{
private:

	
	RECT _buttonRc[BUTTON_END]; // ���/�������� ���ù�ư
	RECT _backButton;		    // �ڷΰ���
	RECT _upButton;				// ���� �ø���
	RECT _downButton;			// �Ʒ��� ������ 
	bool _isWaitInput;			// ����Ŭ�� ���
	tagOnlyText _index[3];		// npc ��ȭ

	int _abyss;	        // ������ �Ŵ����� ������ ���� ���� 
	int _stage;	        // ������ �Ŵ����� ������ ���� ���� 
	int _alpha;			// ���̵�ƿ� ����
	bitset<2> _fadeOut; // ���̵�ƿ� �¿���
	bool _downButtonOn; // ������ ��ư Ȱ��ȭ ���� 


public:
	Abyss():
		_index
	{ 
		L"�ʷα�.",
		L"������ � ���迡 �����Ұž�?",
		L""
	}
	{}
	~Abyss() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};