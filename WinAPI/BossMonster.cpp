#include "Stdafx.h"
#include "BossMonster.h"

Minotauros::Minotauros()
{
	_curHp = 500;
	_curAtt = 30;
	_dropExp = 50;
	_dropLufia = RND->getFromIntTo(80,100);
	_dropItemIndex = 0; // юс╫ц

	_state = MONSTERSTATE::IDLE;
	_direction = static_cast<MONSTERDIRECTION> (RND->getInt(3));
	_monster.speed = 2;
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;
	_monster.image = IMG("mino_idle");
}

void Minotauros::move()
{
}

void Minotauros::attack()
{
}
