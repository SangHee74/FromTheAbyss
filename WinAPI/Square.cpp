#include "Stdafx.h"
#include "Square.h"

HRESULT Square::init(void)
{
	_mugPos.x = LSCENTER_X - ((158 * MAGNI) / 2);
	_mugPos.y = WINSIZE_Y - (178 * MAGNI);

	return S_OK;
}

void Square::release(void)
{
}

void Square::update(void)
{
}

void Square::render(void)
{
	IMG("square")->render(getMemDC());


	IMGR("tomi", getMemDC(), _mugPos.x, _mugPos.y);
	//IMGR("doble", getMemDC(), _mugPos.x, _mugPos.y);
	//IMGR("lasmeda", getMemDC(), _mugPos.x, _mugPos.y);
	//IMGR("daisy_0", getMemDC(), _mugPos.x, _mugPos.y);
	//IMGR("fiena_0", getMemDC(), _mugPos.x, _mugPos.y);
	//IMGR("gamel_0", getMemDC(), _mugPos.x, _mugPos.y);



	IMG("square_boxBottom")->alphaRender(getMemDC(),0,WINSIZE_Y-IMG("square_boxBottom")->getHeight(),30);
	IMGR("square_boxTop", getMemDC(),0,WINSIZE_Y-IMG("square_boxTop")->getHeight());


}
