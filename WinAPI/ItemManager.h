#pragma once
#include "SingletonBase.h"
#include "ItemClass.h"

class ItemManager :public SingletonBase<ItemManager>
{
private:
	Image* _invenIcon;
	Image* _storeIcon;
	Image* _dropIcon;

	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;


public:
	ItemManager() {}
	~ItemManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Item* getItem(int itemIndex);
	void renderItem(HDC hdc, int itemIndex, int x, int y);
	void renderItemInStore(HDC hdc, int itemIndex, int x, int y);
	void renderItemDrop(HDC hdc, int itemIndex, int x, int y);
};

