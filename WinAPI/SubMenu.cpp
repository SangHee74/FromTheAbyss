#include "Stdafx.h"
#include "SubMenu.h"
#include "Player.h"

HRESULT SubMenu::init(void)
{
	_subMenu.reset();

	int subX;
	subX = CENTER_X;

		
		
		
	_menuButton[SUB_ITEM]   = RectMake(subX+(9 * MAGNI),  3* MAGNI, 53* MAGNI, 20* MAGNI);
	_menuButton[SUB_SKILL]  = RectMake(subX+(70 * MAGNI), 3* MAGNI, 53* MAGNI, 20* MAGNI);
	_menuButton[SUB_MAP]    = RectMake(subX+(131* MAGNI), 3* MAGNI, 53* MAGNI, 20* MAGNI);
	_menuButton[SUB_STATUS] = RectMake(subX+(192* MAGNI), 3* MAGNI, 53* MAGNI, 20* MAGNI);

	_tapButton[TAP_ONE]   = RectMake(subX+(10* MAGNI), 35 * MAGNI,  14* MAGNI, 36* MAGNI);
	_tapButton[TAP_TWO]   = RectMake(subX+(10* MAGNI), 75 * MAGNI,  14* MAGNI, 36* MAGNI);
	_tapButton[TAP_THREE] = RectMake(subX+(10* MAGNI), 115* MAGNI, 14* MAGNI, 36* MAGNI);


	return S_OK;
}

void SubMenu::release(void)
{
}

void SubMenu::update(void)
{
	if (KEYOKD(VK_LBUTTON))
	{
		selectMenu();
	}
}

void SubMenu::render(void)
{
	renderMenu();
	rendeTap();


	for (int i = 0; i < SUB_END; i++)
	{
		rcMake(getMemDC(), _menuButton[i]);
	}

	for (int i = 0; i < TAP_END; i++)
	{
		rcMake(getMemDC(), _tapButton[i]);
	}




}

void SubMenu::selectMenu()
{
	if (PtInRect(&_menuButton[SUB_ITEM], _ptMouse))
	{
		_subMenu.reset(); _subMenu.set(1);
	}
	if (PtInRect(&_menuButton[SUB_ITEM], _ptMouse))
	{
		_subMenu.reset(); _subMenu.set(2);
	}
	if (PtInRect(&_menuButton[SUB_ITEM], _ptMouse))
	{
		_subMenu.reset(); _subMenu.set(3);
	}
	if (PtInRect(&_menuButton[SUB_ITEM], _ptMouse))
	{
		_subMenu.reset(); _subMenu.set(4);
	}
}

void SubMenu::selectTap()
{
}

void SubMenu::renderMenu()
{
	if (_subMenu.test(1))
	{
		IMGR("sub_inven", getMemDC(), CENTER_X, 0);
	}
	else if (_subMenu.test(2))
	{
		IMGR("sub_skill", getMemDC(), CENTER_X, 0);
	}
	else if (_subMenu.test(3))
	{
		IMGR("sub_map", getMemDC(), CENTER_X, 0);
	}
	else if (_subMenu.test(4))
	{
		IMGR("sub_map", getMemDC(), CENTER_X, 0);
	}
}

void SubMenu::rendeTap()
{
}
