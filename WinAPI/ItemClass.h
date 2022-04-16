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
	int iAtk; //����
	int iDef; //����
	int iInt; //����
	int iMen; //����
	int iAgi; //�ӵ�
	int iLuk; //ũ��

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
	string _descripton;
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
		_descripton = other._descripton;
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
		_descripton = "NONE";
		_price = 0;
	}
	~Item() {}

};

