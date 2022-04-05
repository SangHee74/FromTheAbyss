#include "Stdafx.h"
#include "FieldMonster.h"

Dionaea::Dionaea()
{
	_curHp = 30;
	_dropExp = 20;
	_dropLufia = RND->getInt(50);
	_dropItemIndex = 0 ; // 임시

	_state = MOSTERSTATE::IDLE;
	_direction = static_cast<MONSTERDIRECTION> (RND->getInt(3));
	_speed = 2;
	_frameX = 0;
	_frameY = (int)_direction;
	_image = IMG("Dionaea_idle");
}

void Dionaea::move()
{
}

void Dionaea::attack()
{
}


EvilEye::EvilEye()
{
	cout << "----------FieldMoster<EvilEye> constructor----------" << endl;

	_curHp = 10;
	_dropExp = 10;
	_dropLufia = RND->getInt(15);
	_dropItemIndex = 0; // 임시

	_state = MOSTERSTATE::IDLE;
	_direction = static_cast<MONSTERDIRECTION> (RND->getInt(3));
	_speed = 3;
	_frameX = 0;
	_frameY = (int)_direction;
	_image = IMG("EvilEye_idle");

	cout << "----------------------------------------------------" << endl;
}

void EvilEye::move()
{
}

void EvilEye::attack()
{
}

Kobold::Kobold()
{
	cout << "----------FieldMoster<Kobold> constructor----------" << endl;

	_curHp = 50;
	_dropExp = 70;
	_dropLufia = RND->getInt(80);
	_dropItemIndex = 0; // 임시

	_state = MOSTERSTATE::IDLE;
	_direction = static_cast<MONSTERDIRECTION> (RND->getInt(3));
	_speed = 3;
	_frameX = 0;
	_frameY = (int)_direction;
	_image = IMG("Kobold_idle");

	cout << "---------------------------------------------------" << endl;
}

void Kobold::move()
{
}

void Kobold::attack()
{
}
