#include "Stdafx.h"
#include "Abyss.h"

HRESULT Abyss::init(void)
{
	SOUNDMANAGER->play("abyss", 0.05f);

	int w, h;
	w = IMG("abyss1")->getWidth();
	h = IMG("abyss1")->getHeight();
	
	_buttonRc[BUTTON_ONE]	 = RectMake(RSCENTER_X - (w*0.5), 30 , w, h);
	_buttonRc[BUTTON_TWO]	 = RectMake(RSCENTER_X - (w*0.5), 170, w, h);
	_buttonRc[BUTTON_THREE]  = RectMake(RSCENTER_X - (w*0.5), 310, w, h);

	_backButton = RectMake(WINSIZE_X - 134, WINSIZE_Y - 50, 120, 40);
	_upButton	= RectMake(CENTER_X, 0, 78,78);
	_downButton = RectMake(CENTER_X, WINSIZE_Y-78, 78,78);
	
	_mainHall = false;
	_isWaitDubbleClick =  true; // 더블클릭 대기 
	_selectAbyss = true;	    // 어비스 -> 스테이지 선택
	_selectButton = BUTTON_ONE; // 버튼 상태 확인

	fadeOut.init();
	fingerPointer.init();


	return S_OK;
}

void Abyss::release(void)
{
}

void Abyss::update(void)
{
	selectStage();


	// fingerMouse
	fingerPointer.update();

	// Next Scene FadeOut
	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // 씬체인지
	{
		SOUNDMANAGER->stop("abyss");

		if (_mainHall) // 메인홀로 돌아가기 
		{
			SCENEMANAGER->changeScene("main");
		}
		else
		{
			int enterAbyss = DATAMANAGER->getMapData().enterAbyssInfo.abyss;
			int enterStage = DATAMANAGER->getMapData().enterAbyssInfo.stage;
		
			switch (enterAbyss)
			{
			case 1 :
				if(enterStage == 1 ) SCENEMANAGER->changeScene("stage11");
				if(enterStage == 4 ) SCENEMANAGER->changeScene("bossIntro");
 				break;
			}
		}
	}

}

void Abyss::render(void)
{
	IMGR("abyss", getMemDC());

	if(_selectAbyss)
	{
		IMGR("abyss1", getMemDC(), _buttonRc[0].left, _buttonRc[0].top);
		FONTMANAGER->firstLineText(getMemDC(), _index[0].text);
	}
	else
	{
		IMGR("stage1", getMemDC(), _buttonRc[BUTTON_ONE].left, _buttonRc[BUTTON_ONE].top);
		IMGR("stage2", getMemDC(), _buttonRc[BUTTON_TWO].left, _buttonRc[BUTTON_TWO].top);
		//IMGR("stage3", getMemDC(), _buttonRc[BUTTON_THREE].left, _buttonRc[BUTTON_THREE].top);

		FONTMANAGER->firstLineText(getMemDC(), _index[1].text);
	}

	fingerPointer.img->render(getMemDC(), fingerPointer.pos.x, fingerPointer.pos.y);

	// fadeOut
	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);

}

void Abyss::selectStage()
{
	// fingerMouse 
	int tempX = 0;
	int tempY = 0;

	BUTTON_NUM curButton; 

	if (_selectAbyss)
	{
		// abyss select ==============================================================
		if (PtInRect(&_buttonRc[BUTTON_ONE], _ptMouse))
		{
			if (_isWaitDubbleClick)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					DATAMANAGER->getMapData().enterAbyssInfo.abyss = 1;
					_isWaitDubbleClick = false;
				}
			}
			else
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					curButton = BUTTON_ONE;
					_selectAbyss = false;      // 어비스 선택이 끝나면
					_isWaitDubbleClick = true; // 더블클릭대기 중
				}
			}
		}
		
	
	}
	else // stage select ==========================================================
	{
		if (PtInRect(&_buttonRc[BUTTON_ONE], _ptMouse))
		{
			if (_isWaitDubbleClick)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					DATAMANAGER->getMapData().enterAbyssInfo.stage = 1;
					_isWaitDubbleClick = false;
					_selectButton = BUTTON_ONE;
				}
			}
			else
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					curButton = BUTTON_ONE; 
					if (_selectButton == curButton) fadeOut.onOff.set(ON);
					else _isWaitDubbleClick = true;
				}
			}
		}
		//// stage select  ========================================================
		if (PtInRect(&_buttonRc[BUTTON_TWO], _ptMouse))
		{
			if (_isWaitDubbleClick)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					DATAMANAGER->getMapData().enterAbyssInfo.stage = 4;
					_isWaitDubbleClick = false;
					_selectButton = BUTTON_TWO;
				}
			}
			else
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					curButton = BUTTON_TWO;
					if (_selectButton == curButton) fadeOut.onOff.set(ON);
					else _isWaitDubbleClick = true;
				}
			}
		}
	}

	
	 // 뒤로가기 
	if (PtInRect(&_backButton, _ptMouse))
	{
		if (_selectAbyss)
		{
			if (_isWaitDubbleClick)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_isWaitDubbleClick = false;
				}
			}
			else
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_mainHall = true;
					fadeOut.onOff.set(ON);
					cout << "백투홈   페이드아웃 온 " << endl;

				}
			}
		}
		else
		{
			if (_isWaitDubbleClick)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_isWaitDubbleClick = false;
				}
			}
			else
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_selectAbyss = true;
					_selectButton = BUTTON_ONE;
				}
			}
		}
	}

	
	tempX = _buttonRc[_selectButton].left + 180;
	tempY = _buttonRc[_selectButton].top + 75;
	fingerPointer.pos = { tempX,tempY };

}
