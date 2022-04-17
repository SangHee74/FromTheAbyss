#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	cout << "포션 하나 넣기 " << endl;

	_im = new ItemManager();
	_im->init();

	_emptySlot = new Item;

	return S_OK;
}

void Inventory::release(void)
{
	SAFE_DELETE(_emptySlot);
}

void Inventory::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		_im->getItem(15);
		cout << "getItem : 15 " << endl;
	}
}

void Inventory::render(void)
{
	if (_isInventoryOn)
	{
		showInven();

	
	}
	else
	{
		cout << "인벤안열림" << endl;
 	}
}

bool Inventory::buyItem(int num)
{
	// item Index로 아이템 가져오기
	Item* item = _im->getItem(num);
	if (item->_price < DATAMANAGER->getPlayer()->getPlayerStatus().lufia)
	{
		DATAMANAGER->getPlayer()->getPlayerStatus().lufia -= item->_price;
		addItem(item); // 금액이 있다면 인벤에 추가
	}
	else
	{
		// 구매 실패
		return false;
	}
}

void Inventory::addItem(Item* item)
{
	_viInvenItem = _vInvenItem.begin();
	//for (; _viInvenItem != _vInvenItem.end(); _viInvenItem++)
	{
	}

		// 인벤토리에 자리가 있으면
	_vInvenItem.push_back(item);
}

void Inventory::addItem(int num)
{
	addItem(_im->getItem(num));
}

void Inventory::sellItem(int num)
{
}

void Inventory::keepItem(int num)
{
}

void Inventory::showInven()
{
	int invenSlotCount =0 ;

	_viInvenItem = _vInvenItem.begin();
	for (; _viInvenItem != _vInvenItem.end(); _viInvenItem++)
	{
		cout << "inven ->render->showInven() " << endl;
		_im->renderItem(getMemDC(), (*_viInvenItem)->_index,
			CENTER_X+83,102);

		invenSlotCount++;
	}
}


