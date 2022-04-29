#pragma once
#include "GameNode.h"

enum BUTTON_NUM
{
	BUTTON_ONE,
	BUTTON_TWO,
	BUTTON_THREE,
	BUTTON_END
};

class Abyss :public GameNode
{
private:

	tagOnlyText _index[3];		// npc ��ȭ
	
	RECT _buttonRc[BUTTON_END]; // ���/�������� ���ù�ư
	RECT _backButton;		    // �ڷΰ���
	RECT _upButton;				// ���� �ø���
	RECT _downButton;			// �Ʒ��� ������ 

	bool _mainHall;			    // ����Ȧ�� ���ư��� 
	bool _isWaitDubbleClick;	// ����Ŭ�� ���
	bool _selectAbyss;			// ó���� ���, �ι�°�� �������� ����
	BUTTON_NUM  _selectButton; 
	
	tagFingerMouse fingerPointer;
	tagSceneFadeOut fadeOut;

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

	void selectStage();

};