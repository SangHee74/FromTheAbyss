#include "Stdafx.h"
#include "Save.h"

HRESULT Save::init(void)
{
	//SOUNDMANAGER->addSound("save", "Resources/sounds/save.wav", true, true);
	//SOUNDMANAGER->play("save", 0.2);

	//vector<string> vData = TEXTDATAMANAGER->load("Resources/player.txt");

	//for (int i = 0; i < SAVETEXT_END; i++)
	//{
	//	char* str = new char[_slot[i].info[i].size() + 1];
	//	copy(_slot[i].info[i].begin(), _slot[i].info[i].end(), str);
	//	str[_slot[i].info[i].size()] = '\0';
	//
	//	FONTMANAGER->drawText(getMemDC(), 
	//		260 ,40+(40*i), "µ¸¿ò", 20, 200, str, strlen(str), RGB(0, 0, 0));
	//
	//	delete[] str;
	//}

	for (int i = 0; i < SAVE_END; i++)
	{
		int h = 16 + (i * (56 * MAGNI));
		_slot[i].slotRc = RectMake(CENTER_X + 20, h, 244 * MAGNI, 48 * MAGNI);

		// ¼¼ÀÌºê ÆÄÀÏ °Ë»ç 
		_slot[i].textCaption[NAME].text = L"NAME : ";
		_slot[i].textCaption[STAT].text = L"STAT : ";
		_slot[i].textCaption[TIME].text = L"TIME : ";
		_slot[i].text[NAME].text =  L"ROSE" ;
		_slot[i].text[STAT].text =  L"Lv 17 ABYSS-3 STAGE-1" ;
		_slot[i].text[TIME].text =  L"02:02" ;

		_slot[i].face = IMG("none");
		_slot[i].newGame = nullptr;
	
		if (i == 0)
		{
			_slot[i].face = IMG("p_face");
			_slot[i].isSaved = true;
		}
		if (i == 1 || i == 2)
		{
			_slot[i].isSaved = false;
		}
	}
	
	_selectRc = RectMakeCenter(1047,450,130,40);
	_deleteRc = RectMakeCenter(1205,450,130,40);

	_buttonCheck.reset();
	_buttonCheck.set(SAVE_ONE);
	_chooseIndex = 0;
	_nextScene = false;

	fingerPointer.init();
	fadeOut.init();
	
	return S_OK;
}

void Save::release(void)
{
}

void Save::update(void)
{
	selectSlot();
	selectMenu();
	
	// fingerMouse
	fingerPointer.update();

	// Next Scene FadeOut
	if (PtInRect(&_selectRc, _ptMouse) )
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _buttonCheck.any())
		{
			fadeOut.onOff.set(ON);
		}
	}
	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // ¾ÀÃ¼ÀÎÁö
	{
		// ¼±ÅÃ½½·Ô¿¡ µû¸¥ ÇÃ·¹ÀÌ¾î ÀÌ´Ö µ¥ÀÌÅÍ
		switch (_chooseIndex)
		{
		case 0:
			DATAMANAGER->getPlayerNumber() = PLAYER_ONE;
			DATAMANAGER->init(PLAYER_ONE);
			break;
		case 1:
			DATAMANAGER->getPlayerNumber() = PLAYER_TWO;
			DATAMANAGER->init(PLAYER_TWO);
			break;
		case 2:
			DATAMANAGER->getPlayerNumber() = PLAYER_THREE;
			DATAMANAGER->init(PLAYER_THREE);
			break;
		}
		SOUNDMANAGER->stop("save");
		SCENEMANAGER->changeScene("main");
	}

	
}

void Save::render(void)
{
	IMG("save")->render(getMemDC());
	FONTMANAGER->drawText(getMemDC(), 36, 351, "µ¸¿ò", 21, FW_SEMIBOLD, _rScreenMBox.text,
		wcslen(_rScreenMBox.text), RGB(100, 100, 100));
	FONTMANAGER->drawText(getMemDC(), 35, 350, "µ¸¿ò", 21, FW_SEMIBOLD, _rScreenMBox.text,
		wcslen(_rScreenMBox.text), RGB(0, 0, 0));



	playerInfoRender();

	fingerPointer.img->render(getMemDC(), fingerPointer.pos.x, fingerPointer.pos.y);

	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);


}

void Save::selectSlot()
{
	int tempX = 0;
	int tempY = 0;

	if (PtInRect(&_slot[SAVE_ONE].slotRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_chooseIndex = SAVE_ONE;
			_buttonCheck.reset();
			_buttonCheck.set(SAVE_ONE);
		}
	}
	if (PtInRect(&_slot[SAVE_TWO].slotRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_chooseIndex = SAVE_TWO;
			_buttonCheck.reset();
			_buttonCheck.set(SAVE_TWO);
		}
	}
	if (PtInRect(&_slot[SAVE_THREE].slotRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_chooseIndex = SAVE_THREE;
			_buttonCheck.reset();
			_buttonCheck.set(SAVE_THREE);
		}
	}
	
	// slotRc width = 610
	tempX = CENTER_X + 20 + 386;
	if (_buttonCheck.test(SAVE_ONE)) tempY = _slot[SAVE_ONE].slotRc.top + 70;
	if (_buttonCheck.test(SAVE_TWO))  tempY = _slot[SAVE_TWO].slotRc.top + 70;
	if (_buttonCheck.test(SAVE_THREE)) tempY = _slot[SAVE_THREE].slotRc.top + 70;
	
	fingerPointer.pos = { tempX,tempY };
}

void Save::selectMenu()
{

}

void Save::playerInfoRender()
{
	RECT temp;

	for (int slotNum = 0; slotNum < SAVE_END; slotNum++)
	{
		if (_buttonCheck.test(slotNum)) // selected o
		{
			// selected o - saved o
			if (_slot[slotNum].isSaved)
			{
				_slot[slotNum].face->render(getMemDC(), _slot[slotNum].slotRc.left + 59, _slot[slotNum].slotRc.top+9);

				// caption
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left +170, _slot[slotNum].slotRc.top + 15,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].textCaption[NAME].text, wcslen(_slot[slotNum].textCaption[NAME].text), RGB(230, 0, 0) );
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 170, _slot[slotNum].slotRc.top + 45,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].textCaption[STAT].text, wcslen(_slot[slotNum].textCaption[STAT].text), RGB(230, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 170, _slot[slotNum].slotRc.top + 80,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].textCaption[TIME].text, wcslen(_slot[slotNum].textCaption[TIME].text), RGB(230, 0, 0));

				// text
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 260, _slot[slotNum].slotRc.top + 15,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].text[NAME].text, wcslen(_slot[slotNum].text[NAME].text), RGB(230, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 260, _slot[slotNum].slotRc.top + 45,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].text[STAT].text, wcslen(_slot[slotNum].text[STAT].text), RGB(230, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 255, _slot[slotNum].slotRc.top + 80,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].text[TIME].text, wcslen(_slot[slotNum].text[TIME].text), RGB(230, 0, 0));
			}
			else // selected o - saved x
			{
				_slot[slotNum].newGame = IMG("newGameSelect");

				temp = RectMakeCenter(rcCenterPos(_slot[slotNum].slotRc).x, rcCenterPos(_slot[slotNum].slotRc).y,
					_slot[slotNum].newGame->getWidth(), _slot[slotNum].newGame->getHeight());

				_slot[slotNum].newGame->render(getMemDC(), temp.left, temp.top);
			}

		}
		else  // selected x
		{
			// selected x - saved o
			if (_slot[slotNum].isSaved)
			{
				_slot[slotNum].face->render(getMemDC(), _slot[slotNum].slotRc.left + 59, _slot[slotNum].slotRc.top + 9);

				// caption
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 170, _slot[slotNum].slotRc.top + 15,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].textCaption[NAME].text, wcslen(_slot[slotNum].textCaption[NAME].text), RGB(0, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 170, _slot[slotNum].slotRc.top + 45,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].textCaption[STAT].text, wcslen(_slot[slotNum].textCaption[STAT].text), RGB(0, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 170, _slot[slotNum].slotRc.top + 80,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].textCaption[TIME].text, wcslen(_slot[slotNum].textCaption[TIME].text), RGB(0, 0, 0));

				// text
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 260, _slot[slotNum].slotRc.top + 15,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].text[NAME].text, wcslen(_slot[slotNum].text[NAME].text), RGB(0, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 260, _slot[slotNum].slotRc.top + 45,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].text[STAT].text, wcslen(_slot[slotNum].text[STAT].text), RGB(0, 0, 0));
				FONTMANAGER->drawText(getMemDC(), _slot[slotNum].slotRc.left + 255, _slot[slotNum].slotRc.top + 80,
					"µ¸¿ò", 24, FW_EXTRABOLD,
					_slot[slotNum].text[TIME].text, wcslen(_slot[slotNum].text[TIME].text), RGB(0, 0, 0));
			}
			else // selected x - saved x
			{
				_slot[slotNum].newGame = IMG("newGame");

				temp = RectMakeCenter(rcCenterPos(_slot[slotNum].slotRc).x, rcCenterPos(_slot[slotNum].slotRc).y,
					_slot[slotNum].newGame->getWidth(), _slot[slotNum].newGame->getHeight());

				_slot[slotNum].newGame->render(getMemDC(), temp.left, temp.top);
			}
		}
	}


}
