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


	_map = new SubMap();
	_map->init();


	HFONT font2;
	HFONT oldFont2;
	return S_OK;
}

void SubMenu::release(void)
{
	_map->release();
	SAFE_DELETE(_map);
}

void SubMenu::update(void)
{
	selectMenu();
	if( _subMenu.test(0) || _subMenu.test(1)) selectTap();

	_map->update();
}

void SubMenu::render(void)
{
	renderMenu();
	renderTap();


	for (int i = 0; i < SUB_END; i++)
	{
		//rcMake(getMemDC(), _menuButton[i]);
	}

	if (_subMenuIdx == SUB_ITEM);//
	if (_subMenuIdx == SUB_SKILL);//
	if (_subMenuIdx == SUB_MAP) _map->render();
	if (_subMenuIdx == SUB_STATUS)
	{	renderStat(); } //

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

void SubMenu::renderStat()
{
	IMAGEMANAGER->findImage("p_face")->render(getMemDC(), CENTER_X + 35, 75);

	// ÀÌ¸§ Ãâ·ÂÇÏ±â......
	FONTMANAGER->drawText(getMemDC(),RectMake(CENTER_X+120,85,100,50),"µ¸¿ò",40,FW_EXTRABOLD,"SH",RGB(0,0,0));

	// Left 
	// lv, hp, sp, exp, next, lufia 
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().lv,     CENTER_X+ 272, 144);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().curHp,  CENTER_X+ 155, 196);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().curSp,  CENTER_X+ 155, 230);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().maxHp,  CENTER_X+ 280, 196);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().maxSp,  CENTER_X+ 280, 230);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().curExp, CENTER_X+ 280, 360);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().maxExp, CENTER_X+ 280, 394);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().lufia,  CENTER_X+ 254, 426);


	// Right
	// point, atk, def,int,men,agi,luk
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iStatusPoint, RSCENTER_X + 250, 108);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iAtk, RSCENTER_X + 120, 150);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iDef, RSCENTER_X + 120, 193);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iInt, RSCENTER_X + 120, 236);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iMen, RSCENTER_X + 120, 279);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iAgi, RSCENTER_X + 120, 322);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iLuk, RSCENTER_X + 120, 365);


	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		cout << "ÀÌ¹ÌÁö Á¶Á¤¿ë ¸¶¿ì½ºÁÂÇ¥ -----------------------------------" << endl;
		cout << "X : " << _ptMouse.x  << " ,  Y : "<< _ptMouse.y << endl;
	}

}


void SubMenu::showNumberImgAlignLeft(int number, int destX, int destY)
{
	// ±âº» È­ÀÌÆ®
	Image* numberImg = IMG("Num_W2");
	//Image* numberImg;
	//numberImg = new Image;
	//numberImg->init("Num_W",);

	int tempX = 22;
	
	// ÃÖ´ë 9999
	if (number > 999)		 numberImg->frameRender(getMemDC(), destX - tempX * 3, destY, number / 1000 % 10, 0);
	if (number > 99)		 numberImg->frameRender(getMemDC(), destX - tempX * 2, destY, number / 100 % 10, 0);
	if (number > 9)			 numberImg->frameRender(getMemDC(), destX - tempX, destY, number / 10 % 10, 0);
							 numberImg->frameRender(getMemDC(), destX, destY, number % 10, 0);
	if (number <= 0)		 numberImg->frameRender(getMemDC(), destX, destY, 0, 0);

}