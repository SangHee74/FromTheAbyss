#include "Stdafx.h"
#include "Save.h"

HRESULT Save::init(void)
{
	for(int i = 0; i < SAVE_END; i++)
	{
		int h = 16 + (i * (56 * MAGNI));
		_slot[i].slotRc = RectMake(CENTER_X+20, h , 244 * MAGNI, 48 * MAGNI);
		
		// ¼¼ÀÌºê ÆÄÀÏ °Ë»ç 

		_slot[0].info[NAME] = "NAME : DAHLIA";
		_slot[0].info[STAT] ="STAT : Lv 1 ABYSS-1 STAGE-1";
		_slot[0].info[TIME] = "TIME : 00:07";
		
		_slot[1].txet[NAME] = { L"NAME : ROSE" };
		_slot[1].txet[STAT] = { L"STAT : Lv 17 ABYSS-3 STAGE-1" };
		_slot[1].txet[TIME] = { L"TIME : 02:02" };

		_slot[i].face = IMG("none");
		_slot[i].newGame = nullptr;
		_slot[i].isSaved = false;

		if (i == 0 ) _slot[i].isSelected = true;
		else _slot[i].isSelected = false;
	}

	_nextScene = false;
	fadeOut.reset();
	return S_OK;
}

void Save::release(void)
{
}

void Save::update(void)
{
	if (PtInRect(&_slot[SAVE_ONE].slotRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// ÇÃ·¹ÀÌ¾î ÀÌ´Ö µ¥ÀÌÅÍ 1¹ø 
			DATAMANAGER->getPlayerNumber() = PLAYER_ONE;
			DATAMANAGER->init(PLAYER_ONE);
			_nextScene = true;

		}
	}
	if (PtInRect(&_slot[SAVE_TWO].slotRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// ÇÃ·¹ÀÌ¾î ÀÌ´Ö µ¥ÀÌÅÍ 2¹ø 
			DATAMANAGER->getPlayerNumber() = PLAYER_TWO;
			DATAMANAGER->init(PLAYER_TWO);
			_nextScene = true;
		}
	}
	if (PtInRect(&_slot[SAVE_THREE].slotRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// ÇÃ·¹ÀÌ¾î ÀÌ´Ö µ¥ÀÌÅÍ 3¹ø 
			DATAMANAGER->getPlayerNumber() = PLAYER_THREE;
			DATAMANAGER->init(PLAYER_THREE);
			_nextScene = true;
		}
	}


	// Next Scene FadeOut
	if (_nextScene)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			fadeOut.onOff.set(ON);
		}
	}

	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // ¾ÀÃ¼ÀÎÁö
	{
		//SOUNDMANAGER->stop("abyss");
		SCENEMANAGER->changeScene("main");
	}
}

void Save::render(void)
{
	IMG("save")->render(getMemDC());

	playerInfo();
	
}

void Save::playerInfo()
{
	for (int i = 0; i < SAVE_END; i++)
	{
		if (_slot[i].isSaved) // savefile o
		{
			
			IMGR("p_face",getMemDC(), _slot[i].slotRc.left+20, _slot[i].slotRc.top );

			if (_slot[i].isSelected) // choose slot o
			{
				FONTMANAGER->drawText(getMemDC(), _slot[i].slotRc,
					"µ¸¿ò", 21, FW_SEMIBOLD, _slot[i].info[NAME], RGB(230, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[i].slotRc,
					"µ¸¿ò", 21, FW_SEMIBOLD, _slot[i].info[STAT], RGB(230, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[i].slotRc,
					"µ¸¿ò", 21, FW_SEMIBOLD, _slot[i].info[TIME], RGB(230, 0, 0));
			}
			else if (!_slot[i].isSelected)
			{
				FONTMANAGER->drawText(getMemDC(), _slot[i].slotRc,
					"µ¸¿ò", 21, FW_SEMIBOLD, _slot[i].info[NAME], RGB(0, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[i].slotRc,
					"µ¸¿ò", 21, FW_SEMIBOLD, _slot[i].info[STAT], RGB(0, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[i].slotRc,
					"µ¸¿ò", 21, FW_SEMIBOLD, _slot[i].info[TIME], RGB(0, 0, 0));
			}
		}
	
		else if (!_slot[i].isSaved)
		{
			// ¼¼ÀÌºê ½½·Ô x -> ¼±ÅÃµÇ¸é »¡°£, ¾Æ´Ï¸é ÇÏ¾ç 
			if (_slot[i].isSelected) _slot[i].newGame = IMG("newGameSelect");
			else  _slot[i].newGame = IMG("newGame");
		}
	}

}
