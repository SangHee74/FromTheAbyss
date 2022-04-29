#include "Stdafx.h"
#include "MainHall.h"

HRESULT MainHall::init(void)
{
	SOUNDMANAGER->play("mainHall", 0.05f);
	
	// ¸ÞÀÎÈ¦ ÀÔÀå½Ã ÇÃ·¹ÀÌ¾î hp,sp È¸º¹
	DATAMANAGER->getPlayer()->getPlayerStatus().curHp = DATAMANAGER->getPlayer()->getPlayerStatus().maxHp;
	DATAMANAGER->getPlayer()->getPlayerStatus().curSp = DATAMANAGER->getPlayer()->getPlayerStatus().maxSp;

	_icon[MAINSCENE_ABYSS] = RectMake(756, 132, 110, 90);
	_icon[MAINSCENE_PUB] = RectMake(720, 354, 90, 70);
	_icon[MAINSCENE_STORE] = RectMake(844, 377, 90, 70);
	_icon[MAINSCENE_SQURE] = RectMake(972, 377, 90, 70);
	_icon[MAINSCENE_TUTO] = RectMake(1095, 354, 90, 70);
	_icon[MAINSCENE_CASTLE] = RectMake(1155, 262, 90, 70);

	_timeCount = 0.0;
	_selectLimit = false;
	_isWaitDubbleClick = true; // ´õºíÅ¬¸¯ ´ë±â 

	_selectScene = MAINSCENE_ABYSS;

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
		switch (_selectScene)
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
	// fingerMouse 
	int tempX = 0;
	int tempY = 0;
	
	MAINSCENE curScene;

#pragma region Scene Click

	if (PtInRect(&_icon[MAINSCENE_ABYSS], _ptMouse))
	{
		if (_isWaitDubbleClick)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isWaitDubbleClick = false;
				_selectScene = MAINSCENE_ABYSS;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) curScene = MAINSCENE_ABYSS;
		}
	}


	if (PtInRect(&_icon[MAINSCENE_PUB], _ptMouse))
	{
		if (_isWaitDubbleClick)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isWaitDubbleClick = false;
				_selectScene = MAINSCENE_PUB;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) curScene = MAINSCENE_PUB;
		}
	}

	

	if (PtInRect(&_icon[MAINSCENE_STORE], _ptMouse))
	{
		if (_isWaitDubbleClick)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isWaitDubbleClick = false;
				_selectScene = MAINSCENE_STORE;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) curScene = MAINSCENE_STORE;
		}
	}
	

	if (PtInRect(&_icon[MAINSCENE_SQURE], _ptMouse))
	{
		if (_isWaitDubbleClick)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isWaitDubbleClick = false;
				_selectScene = MAINSCENE_SQURE;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) curScene = MAINSCENE_SQURE;
		}
	}

	if (PtInRect(&_icon[MAINSCENE_TUTO], _ptMouse))
	{
		if (_isWaitDubbleClick)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isWaitDubbleClick = false;
				_selectScene = MAINSCENE_TUTO;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) curScene = MAINSCENE_TUTO;
		}
	}

	if (PtInRect(&_icon[MAINSCENE_CASTLE], _ptMouse))
	{
		if (_isWaitDubbleClick)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isWaitDubbleClick = false;
				_selectScene = MAINSCENE_CASTLE;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) curScene = MAINSCENE_CASTLE;
		}
	}


	if (_selectScene == curScene) fadeOut.onOff.set(ON);
	else _isWaitDubbleClick = true;

#pragma endregion
	
	// icon w, h 110,90 (abyss)  /  90 ,70
	if (_selectScene == MAINSCENE_ABYSS)
	{
		tempX = _icon[MAINSCENE_ABYSS].left +70;
		tempY = _icon[MAINSCENE_ABYSS].top + 60;
	}
	else
	{
		tempX = _icon[_selectScene].left + 60;
		tempY = _icon[_selectScene].top + 45;
	}
	fingerPointer.pos = { tempX,tempY };

}


void MainHall::menuInfo(int textNum)
{
	IMGR("main", getMemDC());
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->drawText(getMemDC(), 180, 272, "µÕ±Ù¸ð²Ã", 32, FW_SEMIBOLD,
		_menuInfoText[_selectLimit].name, wcslen(_menuInfoText[_selectLimit].name), RGB(255, 255, 255));

	SetTextAlign(getMemDC(), TA_LEFT);
	int _textBufferCnt = 150;
	const int SCRIPT_MAX_LENGTH = 30;

	// gray color font
	FONTMANAGER->drawText(getMemDC(), 36, 351, "µ¸¿ò", 21, FW_SEMIBOLD, _menuInfoText[_selectLimit].script,
		((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), RGB(100, 100, 100));

	if (wcslen(_menuInfoText[_selectLimit].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
	{
		FONTMANAGER->drawText(getMemDC(), 36, 381, "µ¸¿ò", 21, FW_SEMIBOLD,
			_menuInfoText[_selectLimit].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_menuInfoText[_selectLimit].script)) ?
			wcslen(_menuInfoText[_selectLimit].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, RGB(100, 100, 100));
	}

	// black color font
	FONTMANAGER->drawText(getMemDC(), 35, 350, "µ¸¿ò", 21, FW_SEMIBOLD, _menuInfoText[_selectLimit].script,
		((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), RGB(0, 0, 0));

	if (wcslen(_menuInfoText[_selectLimit].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
	{
		FONTMANAGER->drawText(getMemDC(), 35, 380, "µ¸¿ò", 21, FW_SEMIBOLD,
			_menuInfoText[_selectLimit].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_menuInfoText[_selectLimit].script)) ?
			wcslen(_menuInfoText[_selectLimit].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, RGB(0, 0, 0));
	}
}
