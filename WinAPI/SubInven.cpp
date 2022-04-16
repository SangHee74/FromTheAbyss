#include "Stdafx.h"
#include "SubInven.h"

HRESULT SubInven::init(void)
{
	_rc = RectMake(CENTER_X+74,94,380,270);
	_currentSlot.slot = IMG("Item_select");


	_onInvenTile = false;
	return S_OK;
}

void SubInven::release(void)
{
}

void SubInven::update(void)
{
	if (PtInRect(&_rc, _ptMouse)) _onInvenTile = true;
	else _onInvenTile = false;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _onInvenTile)
	{
		 
	}
}

void SubInven::render(void)
{



	_currentSlot.slot->render(getMemDC(),CENTER_X+73,90);
}

