#include "Stdafx.h"
#include "FieldMonster.h"

Dionaea::Dionaea()
{
	_curHp = 50;
	_curAtt = 10;
	_dropExp = 4;
	_dropLufia = RND->getInt(5);
	_dropItemIndex = 0 ; // 임시

	_state = MONSTERSTATE::IDLE;
	_direction = static_cast<MONSTERDIRECTION> (RND->getInt(3));
	_speed = 2;
	_frameX = 0;
	_frameY = (int)_direction;
	_image = IMG("Dionaea_move");
}

void Dionaea::move()
{
	



	_collision.defRc = CollisionAreaResizing(_moveRc, 40, 40);
}

void Dionaea::attack()
{
}


EvilEye::EvilEye()
{
	_curHp = 20;
	_curAtt = 6;
	_dropExp = 10;
	_dropLufia = RND->getInt(15);
	_dropItemIndex = 0; // 임시

	_state = MONSTERSTATE::IDLE;
	_direction = static_cast<MONSTERDIRECTION> (RND->getInt(3));
	_speed = 3;
	_frameX = 0;
	_frameY = (int)_direction;
	_image = IMG("evilEye_idle");
}

void EvilEye::move()
{

	//_movePosX += RND->getFloat(5.0f);
	//if (_movePosX > CENTER_X + 50) _movePosX = 0;
	//_moveRc = RectMakeCenter(_movePosX, _movePosY, _image->getFrameWidth(), _image->getFrameHeight());
	_collision.defRc = CollisionAreaResizing(_moveRc, 40, 40);

}

void EvilEye::attack()
{
}

Kobold::Kobold()
{

	_curHp = 50;
	_curAtt = 20;
	_dropExp = 70;
	_dropLufia = RND->getInt(80);
	_dropItemIndex = 0; // 임시

	_state = MONSTERSTATE::IDLE;
	_direction = static_cast<MONSTERDIRECTION> (RND->getInt(3));
	_speed = 3;
	_frameX = 0;
	_frameY = (int)_direction;
	_image = IMG("Kobold_idle");

}

void Kobold::move()
{

	_collision.defRc = CollisionAreaResizing(_moveRc, 40, 40);

}

void Kobold::attack()
{
}
