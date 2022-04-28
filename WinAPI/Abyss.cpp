#include "Stdafx.h"
#include "Abyss.h"

HRESULT Abyss::init(void)
{
	int w, h;
	w = IMG("abyss1")->getWidth();
	h = IMG("abyss1")->getHeight();
	
	_buttonRc[BUTTON_ONE]	 = RectMake(RSCENTER_X - (w*0.5), 30 , w, h);
	_buttonRc[BUTTON_TWO]	 = RectMake(RSCENTER_X - (w*0.5), 170, w, h);
	_buttonRc[BUTTON_THREE]  = RectMake(RSCENTER_X - (w*0.5), 310, w, h);

	_backButton = RectMake(WINSIZE_X - 134, WINSIZE_Y - 50, 120, 40);
	_upButton	= RectMake(CENTER_X, 0, 78,78);
	_downButton = RectMake(CENTER_X, WINSIZE_Y-78, 78,78);
	_isWaitInput = false;
	
	_abyss = 0;
	_stage = 0;

	_downButtonOn = false;


	fadeOut.init();
	fingerPointer.init();


	return S_OK;
}

void Abyss::release(void)
{
}

void Abyss::update(void)
{

	if (PtInRect(&_buttonRc[BUTTON_ONE], _ptMouse))
	{
		if (!_isWaitInput)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				DATAMANAGER->getMapData().enterAbyssInfo.abyss = 1;
				DATAMANAGER->getMapData().enterAbyssInfo.stage = 1;
				_isWaitInput = true;

			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				fadeOut.onOff.set(ON);
			}
		}
	}
	if (PtInRect(&_backButton, _ptMouse))
	{
		if (!_isWaitInput)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isWaitInput = false;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("main");
			}
		}
	}



	if (_downButtonOn)
	{

	}


	// fingerMouse
	fingerPointer.update();

	// Next Scene FadeOut
	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // 씬체인지
	{
		SOUNDMANAGER->stop("abyss");

		// 스위치문 추가 
		SCENEMANAGER->changeScene("stage11");
	}

}

void Abyss::render(void)
{
	IMGR("abyss", getMemDC());

	if(!_isWaitInput)
	{
		IMGR("abyss1", getMemDC(), _buttonRc[0].left, _buttonRc[0].top);
		FONTMANAGER->firstLineText(getMemDC(), _index[0].text);

	}
	else
	{

		IMGR("stage1", getMemDC(), _buttonRc[0].left, _buttonRc[0].top);
		IMGR("stage2", getMemDC(), _buttonRc[1].left, _buttonRc[1].top);
		//IMGR("stage3", getMemDC(), _buttonRc[2].left, _buttonRc[2].top);
		FONTMANAGER->firstLineText(getMemDC(), _index[1].text);


	}


	fingerPointer.img->render(getMemDC(), fingerPointer.pos.x, fingerPointer.pos.y);

	// fadeOut
	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);



	//rcMake(getMemDC(), _backButton);
}
