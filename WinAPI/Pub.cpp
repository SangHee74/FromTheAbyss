#include "Stdafx.h"
#include "Pub.h"

HRESULT Pub::init(void)
{
	SOUNDMANAGER->play("village", 0.05f);

	PubIdx = 1;

	for (int i = 0; i < 3; i++)
	{
		_menu[i] = RectMake(CENTER_X+(48)+(204*i),CENTER_Y-40,144,100);
	}
	for (int i = 0; i < 2; i++)
	{
		_type[i] = RectMake(CENTER_X + (110) + (276 * i), CENTER_Y - 40, 144, 100);
	}

	int w = IMG("nextButton")->getWidth();
	int h = IMG("nextButton")->getHeight();
	_next = RectMake(RSCENTER_X - (w*0.5), CENTER_Y-(h*0.5), w, h);
	_back = RectMake(WINSIZE_X - 143, WINSIZE_Y - 53, 140, 50);
	_okBox = false;

	return S_OK;
}

void Pub::release(void)
{
}

void Pub::update(void)
{
	menuSelect();
}

void Pub::render(void)
{
	if (PubIdx & welcome)
	{
		IMGR("pub4", getMemDC());
		IMGR("nextButton", getMemDC(),_next.left,_next.top);
		FONTMANAGER->firstLineText(getMemDC(), _pubText[0].text);
	}
	if (PubIdx & pubMain)
	{
		IMGR("pub", getMemDC());
		FONTMANAGER->firstLineText(getMemDC(), _pubText[1].text);
	}
	if (PubIdx & pubType)
	{
		if (PubIdx & storege)
		{
			IMGR("pub2", getMemDC());
			FONTMANAGER->firstLineText(getMemDC(), _pubText[2].text);
		}
		if (PubIdx & takeout)
		{
			IMGR("pub2", getMemDC());
			FONTMANAGER->firstLineText(getMemDC(), _pubText[3].text);
		}
	}
	if (PubIdx & storege)
	{

		if (PubIdx & item)
		{
			IMGR("pub5", getMemDC());
			FONTMANAGER->firstLineText(getMemDC(), _pubText[2].text);
		}
		if (PubIdx & skill)
		{
			IMGR("pub5", getMemDC());
			FONTMANAGER->firstLineText(getMemDC(), _pubText[2].text);
		}
		
	}
	if (PubIdx & takeout)
	{
		if (PubIdx & item)
		{
			IMGR("pub5", getMemDC());
			FONTMANAGER->firstLineText(getMemDC(), _pubText[3].text);
		}
		if (PubIdx & skill)
		{
			IMGR("pub5", getMemDC());
			FONTMANAGER->firstLineText(getMemDC(), _pubText[3].text);
		}
	}
	if (PubIdx & pubSaveCheck)
	{
		IMGR("pub4", getMemDC());
		FONTMANAGER->firstLineText(getMemDC(), _pubText[4].text);
	}


}

void Pub::menuSelect()
{
	if (PubIdx & welcome)
	{
		if (PtInRect(&_next, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				PubIdx |= pubMain;  PubIdx &= ~welcome; 
			}
		}
	}
	if (PubIdx & pubMain)
	{
		if (PtInRect(&_menu[0], _ptMouse) )
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				PubIdx |= pubType; PubIdx |= storege;  PubIdx &= ~pubMain;
			}
		}
		if (PtInRect(&_menu[1], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
			{ 
				PubIdx |= pubType; PubIdx |= takeout;  PubIdx &= ~pubMain;
			}
		}
		if (PtInRect(&_menu[2], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
			{
				PubIdx |= pubSaveCheck;  PubIdx &= ~pubMain;
			}
		}
	}
	if (PubIdx & pubType)
	{
		if (PtInRect(&_type[0], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				{
					PubIdx |= item;  PubIdx &= ~(skill| pubType);
				}
			}
		}
		if (PtInRect(&_type[1], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				{
					PubIdx |= skill;  PubIdx &= ~(item | pubType);
				}
			}
		}
	}

	if (PtInRect(&_back, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PubIdx & pubMain)
			{
				SOUNDMANAGER->stop("village");
				SCENEMANAGER->changeScene("main");
			}
			if (PubIdx & pubType) 
			{
				PubIdx |= pubMain;
				PubIdx &= ~(pubType| storege| takeout);
			}
			if (PubIdx & storege) // 스토리지에서 뒤로갈건데 
			{
				if (!_okBox)
				{
					if (PubIdx & item)
					{
						PubIdx |= pubType;  PubIdx &= ~item;
					} // 아이템이 켜져있으면 아이템만 끄기 
					if (PubIdx & skill)
					{
						PubIdx |= pubType;  PubIdx &= ~skill; // 스킬이 켜져있으면 스킬만 끄기
					}
				}
			}
			if (PubIdx & takeout)
			{
				if (!_okBox)
				{
					if (PubIdx & item)
					{
						PubIdx |= pubType;  PubIdx &= ~item;
					}
					if (PubIdx & skill)
					{
						PubIdx |= pubType;  PubIdx &= ~skill;
					}
				}
			}
		}
	}
}

