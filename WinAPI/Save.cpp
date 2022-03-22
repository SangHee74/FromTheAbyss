#include "Stdafx.h"
#include "Save.h"

HRESULT Save::init(void)
{
	for(int i = 0; i < MAXSAVESLOT; i++)
	{
		int h = 16 + (i * (56 * MAGNI));
		_slot[i]._slotRc = RectMake(CENTER_X+20, h , 244 * MAGNI, 48 * MAGNI);
		
		// 세이브 파일 검사 
		_slot[i]._isSaved = false;
			
		_slot[i]._isSelected = false;
	}
	return S_OK;
}

void Save::release(void)
{
}

void Save::update(void)
{



}

void Save::render(void)
{
	IMG("save")->render(getMemDC());

	for (int i = 0; i < MAXSAVESLOT; i++)
	{
		rcMake(getMemDC(), _slot[i]._slotRc);
	}
}
