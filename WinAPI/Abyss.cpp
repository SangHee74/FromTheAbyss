#include "Stdafx.h"
#include "Abyss.h"

HRESULT Abyss::init(void)
{
	_rc[0] = RectMake(RSCENTER_X - (IMG("abyss1")->getWidth()*0.5),30, IMG("abyss1")->getWidth(), IMG("abyss1")->getHeight());
	_rc[1] = RectMake(RSCENTER_X - (IMG("abyss1")->getWidth()*0.5), 170, IMG("abyss1")->getWidth(), IMG("abyss1")->getHeight());
	_rc[2] = RectMake(RSCENTER_X - (IMG("abyss1")->getWidth()*0.5), 310, IMG("abyss1")->getWidth(), IMG("abyss1")->getHeight());

	_back = RectMake(WINSIZE_X - 134, WINSIZE_Y - 50, 120, 40);

	_abyssIdx = ABYSS;
	_isStage = false;

	return S_OK;
}

void Abyss::release(void)
{
}

void Abyss::update(void)
{
	if (PtInRect(&_rc[0], _ptMouse))
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

	if (PtInRect(&_back, _ptMouse))
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
		IMGR("abyss1", getMemDC(), _rc[0].left, _rc[0].top);
		FONTMANAGER->firstLineText(getMemDC(), _index[0].text);

	}
	else
	{

		IMGR("stage1", getMemDC(), _rc[0].left, _rc[0].top);
		IMGR("stage2", getMemDC(), _rc[1].left, _rc[1].top);
		IMGR("stage3", getMemDC(), _rc[2].left, _rc[2].top);
		FONTMANAGER->firstLineText(getMemDC(), _index[1].text);


	}

	rcMake(getMemDC(), _back);
}
