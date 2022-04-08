#include "Stdafx.h"
#include "Title.h"

HRESULT Title::init(void)
{
	_startRc = RectMakeCenter(RSCENTER_X, CENTER_Y, IMG("titleButton")->getWidth(), IMG("titleButton")->getHeight());

	SOUNDMANAGER->play("title", 0.2);

	_alpha = 0;
	_fadeout.reset(0);

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
			_fadeout.set(1);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_fadeout.set(1);
	}

	SOUNDMANAGER->update();

	// &&getElipcedTime 해서 지연시간 약간 있으면 좋을듯
	// 페이드아웃
	if (_fadeout.test(1) )
	{
		_alpha+=4;
		if (_alpha >= 255)
		{
			_alpha = 255; 
			SOUNDMANAGER->stop("abyss");
			SCENEMANAGER->changeScene("save");
		}
	}

}

void Title::render(void)
{
	IMGR("title",getMemDC());
	IMGR("titleButton",getMemDC(), _startRc.left, _startRc.top);
	IMGAR("black", getMemDC(), _alpha);
	//rcMake(getMemDC(),_startRc);
}
