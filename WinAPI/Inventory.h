#pragma once
#include "GameNode.h"
#include "ItemManager.h"

class Inventory : public GameNode
{
private:

	ItemManager* _im;
	Item* _emptySlot;
	bool _isInventoryOn;

	vector<Item*> _vInvenItem;
	vector<Item*>::iterator _viInvenItem;


public:
	Inventory() {}
	~Inventory() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void invenOnOff(bool state) { _isInventoryOn = state; }

	bool buyItem(int num);
	void addItem(Item* item);
	void addItem(int num);
	void sellItem(int num);
	void keepItem(int num);

	void showInven();

	
};

