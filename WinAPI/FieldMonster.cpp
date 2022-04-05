#include "Stdafx.h"
#include "FieldMonster.h"

Dionaea::Dionaea()
{
	_curHp = 10;
	_dropExp = 10;
	_dropLufia = RND->getInt(15);
	_dropItemIndex = 0 ; // юс╫ц

	_state = static_cast<MOSTERSTATE> (RND->getInt(1));
	_direction = static_cast<MONSTERDIRECTION> (RND->getInt(3));

	//	_width, _height;
	_speed = 2;
	if (_state == MOSTERSTATE::IDLE) _image = IMG("Dionaea_idle");
	else if(_state == MOSTERSTATE::MOVE) _image = IMG("Dionaea_move");

	_frameY = (int)_direction;
	cout << "FieldMoster constructor end" << endl;
}

EvilEye::EvilEye()
{
}

Kobold::Kobold()
{
}
