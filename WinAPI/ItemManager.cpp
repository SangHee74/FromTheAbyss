#include "Stdafx.h"
#include "ItemManager.h"

HRESULT ItemManager::init(void)
{
	_invenIcon = IMAGEMANAGER->addFrameImage("Inven_icon", "Resources/Images/Object/Inven_icon.bmp", 352 * MAGNI, 96 * MAGNI, 11, 3, MGT);
	_storeIcon = IMAGEMANAGER->addFrameImage("store_icon", "Resources/Images/Object/store_icon.bmp", 240 * MAGNI, 20 * MAGNI, 15, 2, MGT);
	_dropIcon  = IMAGEMANAGER->addFrameImage("dropItem", "Resources/Images/Object/dropItem.bmp", 150 * MAGNI, 22 * MAGNI, 6, 1, MGT);
	
	vector<string> vData = TEXTDATAMANAGER->load("Resources/Item1.txt");
	for (int i = 0; i < vData.size(); i += 14)
	{
		Item* item = new Item;
		 item->_index = atoi(vData[i].c_str());
		 item->_invenImgNum = atoi(vData[i+1].c_str());
		 item->_storeImgNum = atoi(vData[i+2].c_str());
		 item->_dropImgNum = atoi(vData[i+3].c_str());
		 item->_type = static_cast<ITEM_TYPE>(atoi(vData[i+4].c_str()));
		 item->_name = vData[i+5].c_str();
		 item->_descripton = vData[i+7].c_str();
		 item->_price = atoi(vData[i+6].c_str());
		 item->_ability.maxHp = 0;
		 item->_ability.maxSp = 0;
		 item->_ability.iAtk = atoi(vData[i+8].c_str());
		 item->_ability.iDef = atoi(vData[i+9].c_str());
		 item->_ability.iInt = atoi(vData[i+10].c_str());
		 item->_ability.iMen = atoi(vData[i+11].c_str());
		 item->_ability.iAgi = atoi(vData[i+12].c_str());
		 item->_ability.iLuk = atoi(vData[i+13].c_str());

		 _vItem.push_back(item);
	}

	return S_OK;
}

void ItemManager::release(void)
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); _viItem++)
	{
		SAFE_DELETE(*_viItem);
	}
}

void ItemManager::update(void){
}

void ItemManager::render(void){
}

Item* ItemManager::getItem(int itemIndex)
{
	return _vItem[itemIndex];
}

void ItemManager::renderItem(HDC hdc, int itemIndex, int x, int y)
{
	int frameX = 0;
	int frameY = 0;
	frameX = itemIndex % _invenIcon->getMaxFrameX();
	frameY = itemIndex / _invenIcon->getMaxFrameX();

	_invenIcon->frameRender(hdc,x,y,frameX,frameY);
}

void ItemManager::renderItemInStore(HDC hdc, int itemIndex, int x, int y)
{
	int frameX = 0;
	int frameY = 0;
	frameX = itemIndex % _invenIcon->getMaxFrameX();
	frameY = itemIndex / _invenIcon->getMaxFrameX();

	_storeIcon->frameRender(hdc, x, y, frameX, frameY);
}

void ItemManager::renderItemDrop(HDC hdc, int itemIndex, int x, int y)
{
	_dropIcon->frameRender(hdc, 
		x - CAM->getScreenRect().left, y - CAM->getScreenRect().top, itemIndex, 0);
}

