#include "Stdafx.h"
#include "SubInven.h"
#include "Inventory.h"

HRESULT SubInven::init(void)
{

	for (int i = 0; i < INVEN_SIZE_Y; i++)
	{
		for (int j = 0; j < INVEN_SIZE_X; j++)
		{
			_invenPos[i * INVEN_SIZE_X + j].rc =
				RectMake(CENTER_X + 83 + (j * 97), 100 + (i * 93), 80, 80);
			_invenPos[i * INVEN_SIZE_X + j].slotNum = i * INVEN_SIZE_X + j;
			_invenPos[i * INVEN_SIZE_X + j].pos = {j, i};
		}
	}

	_currentSlot.rc = RectMake(CENTER_X + 83, 100, 80, 80);

	_baseRc = RectMake(CENTER_X+74,94,380,270);
	_currentSlot.slot = IMG("Item_select");

	_onInvenTile = false;
	return S_OK;
}

void SubInven::release(void)
{
}

void SubInven::update(void)
{
	if (PtInRect(&_baseRc, _ptMouse)) _onInvenTile = true;
	else _onInvenTile = false;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _onInvenTile)
	{
		for (int i = 0; i < INVEN_SIZE_X*INVEN_SIZE_Y; i++)
		{
			if (PtInRect(&_invenPos[i].rc, _ptMouse))
			{
				_currentSlot.rc = _invenPos[i].rc;
			}
		}
	}

	DATAMANAGER->getInven()->update();

}

void SubInven::render(void)
{
	for (int i = 0; i < INVEN_SIZE_X*INVEN_SIZE_Y; i++)
	{
	//	rcMake(getMemDC(), _invenPos[i].rc );
	}


	DATAMANAGER->getInven()->render();
	_currentSlot.slot->render(getMemDC(), _currentSlot.rc.left-9, _currentSlot.rc.top-9);


}

void SubInven::setCurrentSlot(int num)
{
	_currentSlot.rc = _invenPos[num].rc;
}

