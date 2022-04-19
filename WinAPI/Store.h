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

	// 000 00000 ->웰컴 
	// 1000 카테선택  0100 팔기   0010 사기   0001 메뉴선택
	bitset<4> _storeMenu;

	// 10000 스킬  
	// 01000 도구
	// 00100 장신구
	// 00010 방어구  
	// 00001 무기
	bitset<5> _storeCategory;
	bool _okBox;
	bool _isShowItemList; // 아이템리스트 일때는 취소버튼만

	tagSceneFadeOut fadeOut;

public:

	Store() :_storeText
	{
		L"야아, 어서와!",
		L"뭐 필요한 거라도 있어?",
		L"뭐가 필요하지?",
		L"뭘 팔 거야?",
		L"루피아 정도 하겠군!",
		L"이봐 돈이 부족한거같은데?"
	}
	{}
	~Store() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void menuSelect();
};

