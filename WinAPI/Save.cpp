#include "Stdafx.h"
#include "Save.h"

HRESULT Save::init(void)
{
	for(int i = 0; i < SAVE_END; i++)
	{
		int h = 16 + (i * (56 * MAGNI));
		_slot[i].slotRc = RectMake(CENTER_X+20, h , 244 * MAGNI, 48 * MAGNI);
		
		// 세이브 파일 검사 



		_slot[i].isSaved = false;
			
		_slot[i].isSelected = false;
	}

	DATAMANAGER->getPlayerNumber() = PLAYER_NONE;
	_nextScene = false;

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
			// 플레이어 이닛 데이터 1번 
			DATAMANAGER->getPlayerNumber() = PLAYER_ONE;
			DATAMANAGER->init(PLAYER_ONE);
			_nextScene = true;

		}
	}
	if (PtInRect(&_slot[SAVE_TWO].slotRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// 플레이어 이닛 데이터 2번 
			DATAMANAGER->getPlayerNumber() = PLAYER_TWO;
			DATAMANAGER->init(PLAYER_TWO);
			_nextScene = true;
		}
	}
	if (PtInRect(&_slot[SAVE_THREE].slotRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// 플레이어 이닛 데이터 3번 
			DATAMANAGER->getPlayerNumber() = PLAYER_THREE;
			DATAMANAGER->init(PLAYER_THREE);
			_nextScene = true;
		}
	}

	if( _nextScene )  SCENEMANAGER->changeScene("main");

}

void Save::render(void)
{
	IMG("save")->render(getMemDC());
}
