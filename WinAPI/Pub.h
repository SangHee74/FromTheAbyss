#pragma once
#include "GameNode.h"

class Pub :public GameNode
{
private:
	
	RECT _menu[3];
	RECT _type[2];
	RECT _next;
	RECT _back;
	tagOnlyText _index[8];

	bool _okBox;
	
#pragma region menu bit flags
	unsigned char PubIdx = 1;

	unsigned char welcome = 1 << 0;			// 0000 0001 
	unsigned char pubMain = 1 << 1;			// 0000 0010
	unsigned char pubType = 1 << 2;			// 0000 0100 
	unsigned char pubSaveCheck = 1 << 3;	// 0000 1000 
	unsigned char storege = 1 << 4;			// 0001 0000 
	unsigned char takeout = 1 << 5;			// 0010 0000 
	unsigned char item = 1 << 6;			// 0100 0000
	unsigned char skill = 1 << 7;			// 1000 0000 
#pragma endregion

public:
	Pub():
	_index
	{
		L"� ������, ȯ���մϴ�!",
		L"������ �� �ҰŴ�?",
		L"�� �þ��ٱ�?",
		L"���� �ʿ���?",
		L"�ϱ⸦ ���Ŵ�?",
		L"",
		L"�̰� ������ ��?",
		L"�̰� �ָ� ��?"
	}
	{}
	~Pub() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void menuSelect();
};

