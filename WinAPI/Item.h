#pragma once


enum ITEM_TYPE_JSON
{
	WEAPON = 1,
	ARMOR,
	ACCESARY,
	POTION,
	SKILL

};

struct  tagItemOption
{
	int hp;
	int mp;
	int atk;
	int dff;
};

class ItemJson
{
protected:

	string _name;
	string _description;
	int _gold;
	int _frameX;
	int _frameY;
	tagItemOption _option;

	ITEM_TYPE_JSON _itemType;


public:
	ItemJson() {}
	~ItemJson() {}

	void init(string name, string description, int gold, int frameX, int frameY, tagItemOption option);

	string getName() { return this->_name; }
	string getDescription() { return this->_description; }

	int getGold() { return this->_gold; }
	int getFrameX() { return this->_frameX; }
	int getFrameY() { return this->_frameY; }

	tagItemOption getOption() { return this->_option; }
	ITEM_TYPE_JSON getType() { return this->_itemType; }

};





