#include "Stdafx.h"
#include "SubMenu.h"

HRESULT SubMenu::init(void)
{
	_playerInfo = new Player();
	_playerInfo->init();

	// 0001 ÀÎº¥ 0010 ½ºÅ³ 0100 ¸Ê 1000 ½ºÅÈ
	_subMenu.reset();
	_subMenu.set(1);

	// 0001 1ÅÇ 0010 2ÅÇ 0100 3ÅÇ
	_tapOn.reset();
	_tapOn.set(1);

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
	_playerInfo->release();
	SAFE_DELETE(_playerInfo);
}

void SubMenu::update(void)
{
	if (KEYOKD(VK_LBUTTON))
	{
		selectMenu();
		selectTap();
	}
}

void SubMenu::render(void)
{
	renderMenu();
	renderTap();
	renderStat();


}


void SubMenu::selectMenu()
{
	if (PtInRect(&_menuButton[SUB_ITEM], _ptMouse))
	{
		_subMenu.reset(); _subMenu.set(1);
		_tapOn.reset();   _tapOn.set(1);
	}
	if (PtInRect(&_menuButton[SUB_SKILL], _ptMouse))
	{
		_subMenu.reset(); _subMenu.set(2);
		_tapOn.reset();   _tapOn.set(1);
	}
	if (PtInRect(&_menuButton[SUB_MAP], _ptMouse))
	{
		_subMenu.reset(); _subMenu.set(3);
	}
	if (PtInRect(&_menuButton[SUB_STATUS], _ptMouse))
	{
		_subMenu.reset(); _subMenu.set(4);
	}
}

void SubMenu::selectTap()
{
	if (PtInRect(&_tapButton[TAP_ONE], _ptMouse))
	{
		_tapOn.reset(); _tapOn.set(1);
	}
	if (PtInRect(&_tapButton[TAP_TWO], _ptMouse))
	{
		_tapOn.reset(); _tapOn.set(2);
	}
	if (PtInRect(&_tapButton[TAP_THREE], _ptMouse))
	{
		_tapOn.reset(); _tapOn.set(3);
	}
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
		IMGR("sub_stat", getMemDC(), CENTER_X, 0);
	}
}

void SubMenu::renderTap()
{
	if (_subMenu.test(1) || _subMenu.test(2)) 
	{
		if (_tapOn.test(1))
		{
			IMGR("tap_1", getMemDC(), CENTER_X, 62);
		}
		else if (_tapOn.test(2))
		{
			IMGR("tap_2", getMemDC(), CENTER_X, 162);
		}
		else
		{
			IMGR("tap_3", getMemDC(), CENTER_X, 262);
		}
	}
}

void SubMenu::renderStat()
{
	
}
