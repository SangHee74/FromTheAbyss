#include "Stdafx.h"
#include "MainHall.h"

HRESULT MainHall::init(void)
{
	SOUNDMANAGER->addSound("mainHall", "Resources/sounds/mainHall.wav", true, true);
	SOUNDMANAGER->play("mainHall", 0.2);

	// ¸ÞÀÎÈ¦ ÀÔÀå½Ã ÇÃ·¹ÀÌ¾î hp,sp È¸º¹
	DATAMANAGER->getPlayer()->getPlayerStatus().curHp = DATAMANAGER->getPlayer()->getPlayerStatus().maxHp;
	DATAMANAGER->getPlayer()->getPlayerStatus().curSp = DATAMANAGER->getPlayer()->getPlayerStatus().maxSp;


	_icon[MAINSCENE_ABYSS] = RectMake(756, 132, 110, 90);
	_icon[MAINSCENE_PUB] = RectMake(720, 354, 90, 70);
	_icon[MAINSCENE_STORE] = RectMake(844, 377, 90, 70);
	_icon[MAINSCENE_SQURE] = RectMake(972, 377, 90, 70);
	_icon[MAINSCENE_TUTO] = RectMake(1095, 354, 90, 70);
	_icon[MAINSCENE_CASTLE] = RectMake(1155, 262, 90, 70);

	_textNum = 0;

	_buttonCheck.reset();
	_buttonCheck.set(MAINSCENE_ABYSS);
	_chooseIndex = 0;

	fadeOut.init();
	fingerPointer.init();

	return S_OK;
}

void MainHall::release(void)
{
}

void MainHall::update(void)
{
	selectSlot();
	selectMenue();

	// fingerMouse
	fingerPointer.update();

	// Next Scene FadeOut
	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // ¾ÀÃ¼ÀÎÁö
	{
		SOUNDMANAGER->stop("mainHall");
		switch (_chooseIndex)
		{
		case MAINSCENE_ABYSS:
			SCENEMANAGER->changeScene("abyss");
			break;
		case MAINSCENE_PUB:
			SCENEMANAGER->changeScene("pub");
			break;
		case MAINSCENE_STORE:
			SCENEMANAGER->changeScene("store");
			break;
		case MAINSCENE_SQURE:
			SCENEMANAGER->changeScene("square");
			break;
		case MAINSCENE_TUTO:
			SCENEMANAGER->changeScene("tutorial");
			break;
		case MAINSCENE_CASTLE:
			SCENEMANAGER->changeScene("castle");
			break;
		}
	}
	
}

void MainHall::render(void)
{
	menuInfo(_textNum);

	fingerPointer.img->render(getMemDC(), fingerPointer.pos.x, fingerPointer.pos.y);

	// fadeOut
	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);

}

void MainHall::selectSlot()
{
	int tempX = 0;
	int tempY = 0;
	
	if (PtInRect(&_icon[MAINSCENE_ABYSS], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_textNum = MAINSCENE_ABYSS;
			_chooseIndex = MAINSCENE_ABYSS;
			_buttonCheck.reset();
			_buttonCheck.set(MAINSCENE_ABYSS);
		}
	}
	if (PtInRect(&_icon[MAINSCENE_PUB], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_textNum = MAINSCENE_PUB;
			_chooseIndex = MAINSCENE_PUB;
			_buttonCheck.reset();
			_buttonCheck.set(MAINSCENE_PUB);
		}
	}
	if (PtInRect(&_icon[MAINSCENE_STORE], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_textNum = MAINSCENE_STORE;
			_chooseIndex = MAINSCENE_STORE;
			_buttonCheck.reset();
			_buttonCheck.set(MAINSCENE_STORE);
		}
	}
	if (PtInRect(&_icon[MAINSCENE_SQURE], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_textNum = MAINSCENE_SQURE;
			_chooseIndex = MAINSCENE_SQURE;
			_buttonCheck.reset();
			_buttonCheck.set(MAINSCENE_SQURE);
		}
	}
	if (PtInRect(&_icon[MAINSCENE_TUTO], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_textNum = MAINSCENE_TUTO;
			_chooseIndex = MAINSCENE_TUTO;
			_buttonCheck.reset();
			_buttonCheck.set(MAINSCENE_TUTO);
		}
	}
	if (PtInRect(&_icon[MAINSCENE_CASTLE], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_textNum = MAINSCENE_CASTLE;
			_chooseIndex = MAINSCENE_CASTLE;
			_buttonCheck.reset();
			_buttonCheck.set(MAINSCENE_CASTLE);
		}
	}
	
	// icon w, h 110,90 (abyss)  /  90 ,70
	if (_buttonCheck.test(MAINSCENE_ABYSS))
	{
		tempX = _icon[MAINSCENE_ABYSS].left +70;
		tempY = _icon[MAINSCENE_ABYSS].top + 60;
	}
	else
	{
		tempX = _icon[_chooseIndex].left + 60;
		tempY = _icon[_chooseIndex].top + 45;
	}
	fingerPointer.pos = { tempX,tempY };

}

void MainHall::selectMenue()
{
	for (int i = 0; i < MAINSCENE_END; i++)
	{
		if (PtInRect(&_icon[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _buttonCheck.any())
			{
				fadeOut.onOff.set(ON);
			}
		}
	}
}

void MainHall::menuInfo(int textNum)
{
	IMGR("main", getMemDC());
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->drawText(getMemDC(), 180, 272, "µÕ±Ù¸ð²Ã", 32, FW_SEMIBOLD,
		_menuInfoText[_textNum].name, wcslen(_menuInfoText[_textNum].name), RGB(255, 255, 255));

	SetTextAlign(getMemDC(), TA_LEFT);
	int _textBufferCnt = 150;
	const int SCRIPT_MAX_LENGTH = 30;

	FONTMANAGER->drawText(getMemDC(), 36, 351, "µ¸¿ò", 21, FW_SEMIBOLD, _menuInfoText[_textNum].script,
		((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), RGB(100, 100, 100));

	if (wcslen(_menuInfoText[_textNum].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
	{
		FONTMANAGER->drawText(getMemDC(), 36, 381, "µ¸¿ò", 21, FW_SEMIBOLD,
			_menuInfoText[_textNum].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_menuInfoText[_textNum].script)) ?
			wcslen(_menuInfoText[_textNum].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, RGB(100, 100, 100));
	}

	FONTMANAGER->drawText(getMemDC(), 35, 350, "µ¸¿ò", 21, FW_SEMIBOLD, _menuInfoText[_textNum].script,
		((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), RGB(0, 0, 0));

	if (wcslen(_menuInfoText[_textNum].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
	{
		FONTMANAGER->drawText(getMemDC(), 35, 380, "µ¸¿ò", 21, FW_SEMIBOLD,
			_menuInfoText[_textNum].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_menuInfoText[_textNum].script)) ?
			wcslen(_menuInfoText[_textNum].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, RGB(0, 0, 0));
	}
}
