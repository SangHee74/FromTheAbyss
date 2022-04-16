#include "Stdafx.h"
#include "SubMenu.h"

HRESULT SubMenu::init(void)
{
	// 0001 ÀÎº¥ 0010 ½ºÅ³ 0100 ¸Ê 1000 ½ºÅÈ
	_subMenu.reset();
	_subMenu.set(0);

	// 0001 1ÅÇ 0010 2ÅÇ 0100 3ÅÇ
	_tapOn.reset();
	_tapOn.set(0);

	int subX;
	subX = CENTER_X;
		
	_menuButton[SUB_ITEM]   = RectMake(subX+(9  * MAGNI), 3* MAGNI, 53* MAGNI, 20* MAGNI);
	_menuButton[SUB_SKILL]  = RectMake(subX+(70 * MAGNI), 3* MAGNI, 53* MAGNI, 20* MAGNI);
	_menuButton[SUB_MAP]    = RectMake(subX+(131* MAGNI), 3* MAGNI, 53* MAGNI, 20* MAGNI);
	_menuButton[SUB_STATUS] = RectMake(subX+(192* MAGNI), 3* MAGNI, 53* MAGNI, 20* MAGNI);

	_tapButton[TAP_ONE]   = RectMake(subX+(10* MAGNI), 35 * MAGNI,  14* MAGNI, 36* MAGNI);
	_tapButton[TAP_TWO]   = RectMake(subX+(10* MAGNI), 75 * MAGNI,  14* MAGNI, 36* MAGNI);
	_tapButton[TAP_THREE] = RectMake(subX+(10* MAGNI), 115* MAGNI,  14* MAGNI, 36* MAGNI);

	_inven = new SubInven();
	_inven->init();
	_inven->update();

	_map = new SubMap();
	_map->init();

	_status = new SubStatus();
	_status->init();


	//HFONT font2;
	//HFONT oldFont2;
	return S_OK;
}

void SubMenu::release(void)
{
	_inven->release();
	SAFE_DELETE(_inven);
	_map->release();
	SAFE_DELETE(_map);
	_status->release();
	SAFE_DELETE(_status);
}

void SubMenu::update(void)
{
	selectMenu();
	if( _subMenu.test(0) || _subMenu.test(1)) selectTap();

	_inven->update();
	_map->update();

	_status->render();
}

void SubMenu::render(void)
{
	renderMenu();
	renderTap();

	if (_subMenuIdx == SUB_ITEM)	 _inven->render();
	if (_subMenuIdx == SUB_SKILL);//
	if (_subMenuIdx == SUB_MAP)		 _map->render();
	if (_subMenuIdx == SUB_STATUS)	 _status->render();

	// Ã¼·Â¹Ù ¸Ê UI
	IMGR("UI_pathInfo", getMemDC(), LSCENTER_X - 21, 10);
	IMGFR("UI_path", getMemDC(), 309, 20, _map->getCurPathFrameX(), 0);
	//IMGFR("UI_point", getMemDC(), 309, 20, _map->getCurPathFrameX(), 0);
}


void SubMenu::selectMenu()
{
	if (PtInRect(&_menuButton[SUB_ITEM], _ptMouse))
	{
		if (KEYOKD(VK_LBUTTON))
		{
			_subMenuIdx = SUB_ITEM;
			_subMenu.reset(); _subMenu.set(0);
			_tapOn.reset();   _tapOn.set(0);
		}
	}
	if (PtInRect(&_menuButton[SUB_SKILL], _ptMouse))
	{

		if (KEYOKD(VK_LBUTTON))
		{
			_subMenuIdx = SUB_SKILL;
			_subMenu.reset(); _subMenu.set(1);
			_tapOn.reset();   _tapOn.set(0);
		}
	}
	if (PtInRect(&_menuButton[SUB_MAP], _ptMouse))
	{

		if (KEYOKD(VK_LBUTTON))
		{
			_subMenuIdx = SUB_MAP;
			_subMenu.reset(); _subMenu.set(2);
			_tapOn.reset();
		}
	}
	if (PtInRect(&_menuButton[SUB_STATUS], _ptMouse) )
	{
		if (KEYOKD(VK_LBUTTON))
		{
			_subMenuIdx = SUB_STATUS;
			_subMenu.reset(); _subMenu.set(3);
			_tapOn.reset();
		}
	}
}

void SubMenu::selectTap()
{
	if (PtInRect(&_tapButton[TAP_ONE], _ptMouse))
	{
		if (KEYOKD(VK_LBUTTON))
		{
			_tapOn.reset(); _tapOn.set(0);
		}
	}
	if (PtInRect(&_tapButton[TAP_TWO], _ptMouse))
	{
		if (KEYOKD(VK_LBUTTON))
		{
			_tapOn.reset(); _tapOn.set(1);
		}
	}
	if (PtInRect(&_tapButton[TAP_THREE], _ptMouse))
	{
		if (KEYOKD(VK_LBUTTON))
		{
			_tapOn.reset(); _tapOn.set(2);
		}
	}
}

void SubMenu::renderMenu()
{
	if (_subMenu.test(0))
	{
		IMGR("sub_inven", getMemDC(), CENTER_X, 0);
	}
	else if (_subMenu.test(1))
	{
		IMGR("sub_skill", getMemDC(), CENTER_X, 0);
	}
	else if (_subMenu.test(2))
	{
		IMGR("sub_map", getMemDC(), CENTER_X, 0);
	}
	else if (_subMenu.test(3))
	{
		IMGR("sub_stat", getMemDC(), CENTER_X, 0);
	}
}

void SubMenu::renderTap()
{
	if (_tapOn.test(0))
	{
		IMGR("tap_1", getMemDC(), CENTER_X, 62);
	}
	if (_tapOn.test(1))
	{
		IMGR("tap_2", getMemDC(), CENTER_X, 162);
	}
	if (_tapOn.test(2))
	{
		IMGR("tap_3", getMemDC(), CENTER_X, 262);
	}
}

