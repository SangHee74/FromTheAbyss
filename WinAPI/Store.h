#pragma once
#include "GameNode.h"

enum STORE_TYPE_INDEX
{
	STORE_BUY, STORE_SELL, // type
	STORE_WELCOME, STORE_MAIN,// state
};

enum STORE_CATECGORY_INDEX
{
	STORE_WEAPON, STORE_ARMOR, STORE_ACC, // menu
	STORE_POTION, STORE_SKILL
};


class Store :public GameNode
{
private:

	RECT _menu[2];
	RECT _category[5];
	RECT _next;
	RECT _back;
	tagOnlyText _storeText[6];

	// 000 00000 ->���� 
	// 1000 ī�׼���  0100 �ȱ�   0010 ���   0001 �޴�����
	bitset<4> _storeMenu;

	// 10000 ��ų  
	// 01000 ����
	// 00100 ��ű�
	// 00010 ��  
	// 00001 ����
	bitset<5> _storeCategory;
	bool _okBox;
	bool _isShowItemList; // �����۸���Ʈ �϶��� ��ҹ�ư��

	tagSceneFadeOut fadeOut;

public:

	Store() :_storeText
	{
		L"�߾�, ���!",
		L"�� �ʿ��� �Ŷ� �־�?",
		L"���� �ʿ�����?",
		L"�� �� �ž�?",
		L"���Ǿ� ���� �ϰڱ�!",
		L"�̺� ���� �����ѰŰ�����?"
	}
	{}
	~Store() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void menuSelect();
};

