#include "Stdafx.h"
#include "Item.h"

void ItemJson::init(string name, string description, int gold, int frameX, int frameY, tagItemOption option)
{
	_name = name;
	_description = description;
	_gold = gold;
	_frameX = frameX;
	_frameY = frameY;
	_option = option;

}
