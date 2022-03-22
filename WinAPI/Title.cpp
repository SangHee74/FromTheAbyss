#include "Stdafx.h"
#include "Title.h"

HRESULT Title::init(void)
{
	_startRc = RectMakeCenter(RSCENTER_X, CENTER_Y, IMG("titleButton")->getWidth(), IMG("titleButton")->getHeight());

	SOUNDMANAGER->play("title", 0.5);

	return S_OK;
}

void Title::release(void)
{
}

void Title::update(void)
{

	if (PtInRect(&_startRc, _ptMouse))
	{
		if  (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->stop("abyss");
			SCENEMANAGER->changeScene("save");
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SOUNDMANAGER->stop("abyss");
		SCENEMANAGER->changeScene("save");
	}



	SOUNDMANAGER->update();
}

void Title::render(void)
{
	IMG("title")->render(getMemDC());
	IMG("titleButton")->render(getMemDC(), _startRc.left, _startRc.top);
	//rcMake(getMemDC(),_startRc);
}
