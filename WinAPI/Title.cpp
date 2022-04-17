#include "Stdafx.h"
#include "Title.h"

HRESULT Title::init(void)
{
	SOUNDMANAGER->addSound("title", "Resources/sounds/title.wav", true, true);
	SOUNDMANAGER->play("title", 0.2);
	_startRc = RectMakeCenter(RSCENTER_X, CENTER_Y, IMG("titleButton")->getWidth(), IMG("titleButton")->getHeight());
	fadeOut.init();
	return S_OK;
}

void Title::release(void)
{
}
 
void Title::update(void)
{
	SOUNDMANAGER->update();

	// Next Scene FadeOut
	if (PtInRect(&_startRc, _ptMouse))
	{
		if  (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			fadeOut.onOff.set(ON);
		}
	}

	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // ¾ÀÃ¼ÀÎÁö
	{
		SOUNDMANAGER->stop("abyss");
		SCENEMANAGER->changeScene("save");
	}


}

void Title::render(void)
{
	IMGR("title",getMemDC());
	IMGR("titleButton",getMemDC(), _startRc.left, _startRc.top);


	// ÆäÀÌµå ¾Æ¿ô
	fadeOut.blackImg->alphaRender(getMemDC(),fadeOut.alpha);
	//rcMake(getMemDC(),_startRc);
}
