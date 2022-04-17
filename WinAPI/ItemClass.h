#pragma once
#include "Stdafx.h"

enum class ITEM_TYPE
{
	NONE = 0,
	WEAPON,
	ARMOR,
	ACCESSORY,
	POTION,
	USE,
	SKILL,
	ITEM_END
};

struct tagAbility
{
	int maxHp;
	int maxSp;
	int iAtk; //물공
	int iDef; //물방
	int iInt; //마공
	int iMen; //마방
	int iAgi; //속도
	int iLuk; //크리

	tagAbility operator+(tagAbility other)
	{
		tagAbility temp;
		
		temp.maxHp = maxHp + other.maxHp;
		temp.maxSp = maxSp + other.maxSp;
		temp.iAtk = iAtk + other.iAtk;
		temp.iDef = iDef + other.iDef;
		temp.iInt = iInt + other.iInt;
		temp.iMen = iMen + other.iMen;
		temp.iAgi = iAgi + other.iAgi;
		temp.iLuk = iLuk + other.iLuk;

		return temp;
	}
};

class Item
{
public:
	int _index;
	int _invenImgNum;
	int _storeImgNum;
	int _dropImgNum;
	ITEM_TYPE _type;
	string _name;
	string _description;
	int _price;

	tagAbility _ability;

	void operator=(Item other)
	{
		_index = other._index;
		_invenImgNum = other._invenImgNum;
		_storeImgNum = other._storeImgNum;
		_dropImgNum = other._dropImgNum;
		_type = other._type;
		_name = other._name;
		_description = other._description;
		_price = other._price;
		_ability = other._ability;
	}

	Item()
	{
		_index = 0;
		_invenImgNum = 0;
		_storeImgNum = 0;
		_dropImgNum = 0;
		_type = ITEM_TYPE::NONE;
		_name = "NONE";
		_description = "NONE";
		_price = 0;
	}
	~Item() {}


	void toString(void)
	{
		cout << "=============================================" << endl;
		cout << "_index         :" << _index << endl;
		cout << "_invenImgNum   :" << _invenImgNum << endl;
		cout << "_storeImgNum   :" << _storeImgNum << endl;
		cout << "_dropImgNum    :" << _dropImgNum << endl;
		cout << "_type          :" << (int)_type << endl;
		cout << "_name          :" << _name << endl;
		cout << "_description   :" << _description << endl;
		cout << "_price         :" << _price << endl;
		cout << "===================================" << endl;
		cout << "maxHp          :" << _ability.maxHp	<<endl;
		cout << "maxSp          :" << _ability.maxSp	<<endl;
		cout << "iAtk          :" << _ability.iAtk	<<endl;
		cout << "iDef          :" << _ability.iDef	<<endl;
		cout << "iInt          :" << _ability.iInt	<<endl;
		cout << "iMen          :" << _ability.iMen	<<endl;
		cout << "iAgi          :" << _ability.iAgi	<<endl;
		cout << "iLuk          :" << _ability.iLuk   <<endl;
	}
};

