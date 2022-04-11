#include "Stdafx.h"
#include "MainHall.h"

HRESULT MainHall::init(void)
{
	mainIdx = 1;
	_textNum = 0;
	_selectCount = 0;

	_icon[MAINSCENE_ABYSS] = RectMake(756, 132, 110, 90);
	_icon[MAINSCENE_PUB] = RectMake(720, 354, 90, 70);
	_icon[MAINSCENE_STORE] = RectMake(844, 377, 90, 70);
	_icon[MAINSCENE_SQURE] = RectMake(972, 377, 90, 70);
	_icon[MAINSCENE_TUTO] = RectMake(1095, 354, 90, 70);
	_icon[MAINSCENE_CASTLE] = RectMake(1155, 262, 90, 70);

	return S_OK;
}

void MainHall::release(void)
{
}

void MainHall::update(void)
{
	menuSelect();
	//_isWaitInput = false;

}

void MainHall::render(void)
{
	menuInfo(_textNum);
	

	for (int i = 0; i < 6; i++)
	{
	//	rcMake(getMemDC(), _icon[i]);
	}
}

void MainHall::menuSelect()
{
	
	if (PtInRect(&_icon[MAINSCENE_ABYSS], _ptMouse))
	{
		if (!_isWaitInput)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_textNum = MAINSCENE_ABYSS;
				_selectMenu = _textNum;
				_isWaitInput = true;
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("abyss");
			}
		}

	}
	if (PtInRect(&_icon[MAINSCENE_PUB], _ptMouse))
	{
		if (!_isWaitInput)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_textNum = MAINSCENE_PUB;
				_selectMenu = _textNum;
				_isWaitInput = true;
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("pub");
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_STORE], _ptMouse))
	{
		if (!_isWaitInput)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_textNum = MAINSCENE_STORE;
				_selectMenu = _textNum;
				_isWaitInput = true;
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("store");
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_SQURE], _ptMouse))
	{
		if (!_isWaitInput)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_textNum = MAINSCENE_SQURE;
				_selectMenu = _textNum;
				_isWaitInput = true;
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("square");
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_TUTO], _ptMouse))
	{
		if (!_isWaitInput)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_textNum = MAINSCENE_TUTO;
				_selectMenu = _textNum;
				_isWaitInput = true;
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("tutorial");
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_CASTLE], _ptMouse))
	{
		if (!_isWaitInput)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_textNum = MAINSCENE_CASTLE;
				_selectMenu = _textNum;
				_isWaitInput = true;
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("castle");
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
