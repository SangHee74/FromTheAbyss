#pragma once
#include "GameNode.h"

enum SUBMENU
{
	SUB_ITEM, SUB_SKILL, SUB_MAP, SUB_STATUS,SUB_END
};

enum TAPBUTTON
{
	TAP_ONE, TAP_TWO, TAP_THREE,TAP_END
};

class player;

class SubMenu :public GameNode
{
private:
	bitset<8> _subMenu = 0;
	RECT _menuButton[SUB_END];
	RECT _tapButton[TAP_END];




public:
	SubMenu() {}
	~SubMenu() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void selectMenu();
	void selectTap();
	void renderMenu();
	void rendeTap();
};

