#pragma once


enum ITEM_TYPE
{
	WEAPON = 1,
	ARMOR,
	ACCESARY

};

struct  tagItemOption
{
	int hp;
	int mp;
	int att;
	int dff;
};

class Item
{
protected:

	string _name;
	string _description;
	int _gold;
	int _frameX;
	int _frameY;
	tagItemOption _option;

	ITEM_TYPE _itemType;


public:
	Item() {}
	~Item() {}

	void init(string name, string description, int gold, int frameX, int frameY, tagItemOption option);

	string getName() { return this->_name; }
	string getDescription() { return this->_description; }

	int getGold() { return this->_gold; }
	int getFrameX() { return this->_frameX; }
	int getFrameY() { return this->_frameY; }

	tagItemOption getOption() { return this->_option; }
	ITEM_TYPE getType() { return this->_itemType; }

};





