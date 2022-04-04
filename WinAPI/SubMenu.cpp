#include "Stdafx.h"
#include "SubMenu.h"

HRESULT SubMenu::init(void)
{
	_playerInfo = new Player();
	_playerInfo->init();

	// 0001 인벤 0010 스킬 0100 맵 1000 스탯
	_subMenu.reset();
	_subMenu.set(1);

	// 0001 1탭 0010 2탭 0100 3탭
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

	_subMenuIdx = 0;

	return S_OK;
}

void SubMenu::release(void)
{
	_playerInfo->release();
	SAFE_DELETE(_playerInfo);
}

void SubMenu::update(void)
{

		selectMenu();
		selectTap();


	if (KEYOKD('Q'))
	{
		_subMenuIdx--;
		if (_subMenuIdx < 0) _subMenuIdx = 0;
		selectMenu();
	}
	if (KEYOKD('W'))
	{
		_subMenuIdx++;
		if (_subMenuIdx > 3) _subMenuIdx = 3;
		selectMenu();
	}

}

void SubMenu::render(void)
{
	renderMenu();
	renderTap();
	renderStat();

	for (int i = 0; i < SUB_END; i++)
	{
		rcMake(getMemDC(), _menuButton[i]);
	}

}


void SubMenu::selectMenu()
{
	if (PtInRect(&_menuButton[SUB_ITEM], _ptMouse)|| _subMenuIdx ==0)
	{
	//	cout << "인벤버튼 검출-----" << endl;
		if (KEYOKD(VK_LBUTTON))
		{
			cout << "문제1=============" << endl;
			_subMenu.reset(); _subMenu.set(1);
			_tapOn.reset();   _tapOn.set(1);
		}
	}
	if (PtInRect(&_menuButton[SUB_SKILL], _ptMouse) || _subMenuIdx == 1)
	{
		//cout << "스킬버튼 검출-----" << endl;

		if (KEYOKD(VK_LBUTTON))
		{
			cout << "문제2=============" << endl;

			_subMenu.reset(); _subMenu.set(2);
			_tapOn.reset();   _tapOn.set(1);
		}
	}
	if (PtInRect(&_menuButton[SUB_MAP], _ptMouse) || _subMenuIdx == 2)
	{
		//cout << "맵버튼 검출-----" << endl;

		if (KEYOKD(VK_LBUTTON))
		{
			cout << "문제3=============" << endl;

			_subMenu.reset(); _subMenu.set(3);
		}
	}
	if (PtInRect(&_menuButton[SUB_STATUS], _ptMouse) || _subMenuIdx == 3)
	{
		//cout << "스탯버튼 검출-----" << endl;
		if (KEYOKD(VK_LBUTTON))
		{
			cout << "문제4=============" << endl;

			_subMenu.reset(); _subMenu.set(4);
		}
	}


}

void SubMenu::selectTap()
{
	if (PtInRect(&_tapButton[TAP_ONE], _ptMouse))
	{
		if (KEYOKD(VK_LBUTTON))
		{
			_tapOn.reset(); _tapOn.set(1);
		}
	}
	if (PtInRect(&_tapButton[TAP_TWO], _ptMouse))
	{
		if (KEYOKD(VK_LBUTTON))
		{
			_tapOn.reset(); _tapOn.set(2);
		}
	}
	if (PtInRect(&_tapButton[TAP_THREE], _ptMouse))
	{
		if (KEYOKD(VK_LBUTTON))
		{
			_tapOn.reset(); _tapOn.set(3);
		}
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
	//_playerInfo->getStatus.
	
}
