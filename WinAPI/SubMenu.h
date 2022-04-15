#pragma once
#include "GameNode.h"
#include "SubMap.h"

enum SUBMENU
{
	SUB_ITEM, SUB_SKILL, SUB_MAP, SUB_STATUS,SUB_END
};

enum TAPBUTTON
{
	TAP_ONE, TAP_TWO, TAP_THREE,TAP_END
};


class SubMenu :public GameNode
{
private:

	bitset<4> _subMenu = 0;
	bitset<4> _tapOn = 0;
	RECT _menuButton[SUB_END];
	RECT _tapButton[TAP_END];
	int _subMenuIdx;

	SubMap* _map;

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
	void renderTap();

	void renderInven();
	void renderSkill();
	void renderStat();

	void showNumberImgAlignLeft(int number, int destX, int destY);


	SubMap* getSubMap() { return _map; }

};

