#include "Stdafx.h"
#include "MainHall.h"

HRESULT MainHall::init(void)
{
	mainIdx = 1;
	_textNum = 0;

	_icon[0] = RectMake(756, 132, 110, 90);
	_icon[1] = RectMake(720, 354, 90, 70);
	_icon[2] = RectMake(844, 377, 90, 70);
	_icon[3] = RectMake(972, 377, 90, 70);
	_icon[4] = RectMake(1095, 354, 90, 70);
	_icon[5] = RectMake(1155, 262, 90, 70);

	return S_OK;
}

void MainHall::release(void)
{
}

void MainHall::update(void)
{
	menuSelect();


}

void MainHall::render(void)
{
	menuInfo(_textNum);
	

	for (int i = 0; i < 6; i++)
	{
	//	rcMake(getMemDC(), _icon[i]);
	}
}

int MainHall::menuSelect()
{
	if (PtInRect(&_icon[0], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_textNum = 0;
		}
	}
	if (PtInRect(&_icon[1], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_textNum = 1;
		}
	}
	if (PtInRect(&_icon[2], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_textNum = 2;
		}
	}
	if (PtInRect(&_icon[3], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_textNum = 3;
		}
	}
	if (PtInRect(&_icon[4], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_textNum = 4;
		}
	}
	if (PtInRect(&_icon[5], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_textNum = 5;
		}
	}

	return _selectMenu = _textNum;
}

void MainHall::menuInfo(int textNum)
{
	IMGR("main", getMemDC());
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->drawText(getMemDC(), 180, 272, "µÕ±Ù¸ð²Ã", 32, FW_SEMIBOLD,
		_menuInfoText[_textNum].name, wcslen(_menuInfoText[_textNum].name), RGB(2550, 255, 255));

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
