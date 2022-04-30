#include "Stdafx.h"
#include "GameOver.h"

HRESULT GameOver::init(void)
{
	_returnRc = RectMakeCenter(CENTER_X, CENTER_Y, IMG("gameOver")->getWidth(), IMG("gameOver")->getHeight());
	_count = 0;

	fadeOut.init();
	return S_OK;
}

void GameOver::release(void)
{
}

void GameOver::update(void)
{
	_count++;
	
	if (_count >= 180)
	{
		_count = 0;
		fadeOut.onOff.set(ON);
	}

	fadeOut.update();
	if (fadeOut.onOff.test(NEXT))
	{
		SOUNDMANAGER->stop("stage14");
		SCENEMANAGER->changeScene("main");
	}
	}

void GameOver::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	IMGR("gameOver", getMemDC(), _returnRc.left, _returnRc.top);

	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);
}
