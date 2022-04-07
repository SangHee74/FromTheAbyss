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

	_abyssIdx = ABYSS;
	_isStage = false;
	_abyss = 0;
	_stage = 0;
	_maxAbyss = DATAMANAGER->getPlayer()->getPlayerAbyss().abyss;
	_maxStage = DATAMANAGER->getPlayer()->getPlayerAbyss().stage;


	return S_OK;
}

void Abyss::release(void)
{
}

void Abyss::update(void)
{
	if (PtInRect(&_buttonRc[BUTTON_ONE], _ptMouse))
	{
		if (!_isStage)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isStage = true;
			}			
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("stage");
			}
		}
	}

	if (PtInRect(&_backButton, _ptMouse))
	{
		if (!_isStage)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("main");
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isStage = false;
			}
		}
	}
}

void Abyss::render(void)
{
	IMGR("abyss", getMemDC());

	if(!_isStage)
	{
		IMGR("abyss1", getMemDC(), _buttonRc[0].left, _buttonRc[0].top);
		FONTMANAGER->firstLineText(getMemDC(), _index[0].text);

	}
	else
	{

		IMGR("stage1", getMemDC(), _buttonRc[0].left, _buttonRc[0].top);
		//IMGR("stage2", getMemDC(), _buttonRc[1].left, _buttonRc[1].top);
		//IMGR("stage3", getMemDC(), _buttonRc[2].left, _buttonRc[2].top);
		FONTMANAGER->firstLineText(getMemDC(), _index[1].text);


	}

	//rcMake(getMemDC(), _backButton);
}
