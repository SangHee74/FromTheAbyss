#include "Stdafx.h"
#include "Title.h"

HRESULT Title::init(void)
{
	SOUNDMANAGER->play("title", 0.05);
	_startRc = RectMakeCenter(RSCENTER_X, CENTER_Y, IMG("titleButton")->getWidth(), IMG("titleButton")->getHeight());
	fadeOut.init();
	return S_OK;
}

void Title::release(void)
{
}
 
void Title::update(void)
{

	// Next Scene FadeOut
	if (PtInRect(&_startRc, _ptMouse))
	{
		if  (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			fadeOut.onOff.set(ON);
		}
	}

	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // ??ü????
	{
		SOUNDMANAGER->stop("title");
		SCENEMANAGER->changeScene("save");
	}


}

void Title::render(void)
{
	IMGR("title",getMemDC());
	IMGR("titleButton",getMemDC(), _startRc.left, _startRc.top);


	// fadeOut
	fadeOut.blackImg->alphaRender(getMemDC(),fadeOut.alpha);
	//rcMake(getMemDC(),_startRc);
}
