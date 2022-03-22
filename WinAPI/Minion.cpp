#include "Stdafx.h"
#include "Minion.h"

Minion::Minion(){
	//! Do Nothing
}

Minion::~Minion(){
	//! Do Nothing
}


Minion2::Minion2()
{
}

void Minion2::move(void)
{
	//_x += 3.0f; 
	_x += RND->getFloat(5.0f);
	if ( _x > WINSIZE_X + 50) _x = 0;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}



void Minion3::move(void)
{

	float _speed = 0;
	_speed += 0.02f;
	_x = cosf((_speed * 36 - 90)* PI / 180) * 200 + WINSIZE_X / 2;// +RND->getInt(200);
	_y = -sinf((_speed * 36 - 90)*  PI / 180) * 200 + WINSIZE_Y / 2;// +RND->getInt(200);


	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

