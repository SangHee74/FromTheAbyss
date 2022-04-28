#include "Stdafx.h"
#include "MainHall.h"

HRESULT MainHall::init(void)
{
	//SOUNDMANAGER->addSound("mainHall", "Resources/sounds/mainHall.wav", true, true);
	//SOUNDMANAGER->play("mainHall", 0.2);

	// 메인홀 입장시 플레이어 hp,sp 회복
	DATAMANAGER->getPlayer()->getPlayerStatus().curHp = DATAMANAGER->getPlayer()->getPlayerStatus().maxHp;
	DATAMANAGER->getPlayer()->getPlayerStatus().curSp = DATAMANAGER->getPlayer()->getPlayerStatus().maxSp;


	_icon[MAINSCENE_ABYSS] = RectMake(756, 132, 110, 90);
	_icon[MAINSCENE_PUB] = RectMake(720, 354, 90, 70);
	_icon[MAINSCENE_STORE] = RectMake(844, 377, 90, 70);
	_icon[MAINSCENE_SQURE] = RectMake(972, 377, 90, 70);
	_icon[MAINSCENE_TUTO] = RectMake(1095, 354, 90, 70);
	_icon[MAINSCENE_CASTLE] = RectMake(1155, 262, 90, 70);

	_sceneIndex = MAINSCENE_ABYSS;
	_changeIndex = MAINSCENE_END;
	_timeCount = 0.0;
	_selectLimit = false;

	fadeOut.init();
	fingerPointer.init();

	return S_OK;
}

void MainHall::release(void)
{
}

void MainHall::update(void)
{
	selectSlot();
	selectMenue();

	// fingerMouse
	fingerPointer.update();

	// Next Scene FadeOut
	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // 씬체인지
	{
		SOUNDMANAGER->stop("mainHall");
		switch (_changeIndex)
		{
		case MAINSCENE_ABYSS:
			SCENEMANAGER->changeScene("abyss");
			break;
		case MAINSCENE_PUB:
			SCENEMANAGER->changeScene("pub");
			break;
		case MAINSCENE_STORE:
			SCENEMANAGER->changeScene("store");
			break;
		case MAINSCENE_SQURE:
			SCENEMANAGER->changeScene("square");
			break;
		case MAINSCENE_TUTO:
			SCENEMANAGER->changeScene("tutorial");
			break;
		case MAINSCENE_CASTLE:
			SCENEMANAGER->changeScene("castle");
			break;
		}
	}

	

	// 메뉴선택 시 시간체크 
	if (_selectLimit)
	{
		_timeCount += TIMEMANAGER->getElapsedTime();
		if (_timeCount >= 10.0f) // 10 지나면 초기화
		{
			_changeIndex = MAINSCENE_END;
			_timeCount = 0;
		}
	}
	else _timeCount = 0; // 시간제한 초기화

}

void MainHall::render(void)
{
	menuInfo(_textNum);

	fingerPointer.img->render(getMemDC(), fingerPointer.pos.x, fingerPointer.pos.y);

	// fadeOut
	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);

}

void MainHall::selectSlot()
{
	int tempX = 0;
	int tempY = 0;
	
	if (PtInRect(&_icon[MAINSCENE_ABYSS], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_sceneIndex = MAINSCENE_ABYSS;
			_selectLimit = true;

			if (_timeCount < 1.0f) // 일정 시간 이상일떄
			{
				_changeIndex = MAINSCENE_ABYSS;

				if (_sceneIndex == _changeIndex) // 선택했던 씬인덱스와 바꿀 인덱스가 같으면
				{
					fadeOut.onOff.set(ON); // 페이드아웃시작
				}
				if (_sceneIndex != _changeIndex)
				{
					_changeIndex = MAINSCENE_END; // 다르면 체인지 초기화, 
					_selectLimit = false; // 시간제한 초기화
				}
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_PUB], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_sceneIndex = MAINSCENE_PUB;
			_selectLimit = true;

			if (_timeCount > 2)  
			{
				_changeIndex = MAINSCENE_PUB;

				if (_sceneIndex == _changeIndex)  
				{
					fadeOut.onOff.set(ON);  
				}
				if (_sceneIndex != _changeIndex)
				{
					_changeIndex = MAINSCENE_END;  
					_selectLimit = false;  
				}
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_STORE], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_sceneIndex = MAINSCENE_STORE;
			_selectLimit = true;

			if (_timeCount > 5) 
			{
				_changeIndex = MAINSCENE_STORE;

				if (_sceneIndex == _changeIndex) 
				{
					fadeOut.onOff.set(ON); 
				}
				if (_sceneIndex != _changeIndex)
				{
					_changeIndex = MAINSCENE_END;   
					_selectLimit = false;  
				}
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_SQURE], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_sceneIndex = MAINSCENE_SQURE;
			_selectLimit = true;

			if (_timeCount > 5) 
			{
				_changeIndex = MAINSCENE_SQURE;

				if (_sceneIndex == _changeIndex)  
				{
					fadeOut.onOff.set(ON); 
				}
				if (_sceneIndex != _changeIndex)
				{
					_changeIndex = MAINSCENE_END;  
					_selectLimit = false;  
				}
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_TUTO], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_sceneIndex = MAINSCENE_TUTO;
			_selectLimit = true;

			if (_timeCount > 5)  
			{
				_changeIndex = MAINSCENE_TUTO;

				if (_sceneIndex == _changeIndex)  
				{
					fadeOut.onOff.set(ON); 
				}
				if (_sceneIndex != _changeIndex)
				{
					_changeIndex = MAINSCENE_TUTO;  
					_selectLimit = false;  
				}
			}
		}
	}
	if (PtInRect(&_icon[MAINSCENE_CASTLE], _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_sceneIndex = MAINSCENE_CASTLE;
			_selectLimit = true;

			if (_timeCount > 5) 
			{
				_changeIndex = MAINSCENE_CASTLE;

				if (_sceneIndex == _changeIndex)  
				{
					fadeOut.onOff.set(ON);  
				}
				if (_sceneIndex != _changeIndex)
				{
					_changeIndex = MAINSCENE_CASTLE;  
					_selectLimit = false; 
				}
			}
		}
	}
	
	// icon w, h 110,90 (abyss)  /  90 ,70
	if (_sceneIndex == 0)
	{
		tempX = _icon[MAINSCENE_ABYSS].left +70;
		tempY = _icon[MAINSCENE_ABYSS].top + 60;
	}
	else
	{
		tempX = _icon[_sceneIndex].left + 60;
		tempY = _icon[_sceneIndex].top + 45;
	}
	fingerPointer.pos = { tempX,tempY };

}

void MainHall::selectMenue()
{
	for (int i = 0; i < MAINSCENE_END; i++)
	{
		if (PtInRect(&_icon[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _timeCount > 2.0 )
			{
				fadeOut.onOff.set(ON);
			}
		}
	}
}

void MainHall::menuInfo(int textNum)
{
	IMGR("main", getMemDC());
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->drawText(getMemDC(), 180, 272, "둥근모꼴", 32, FW_SEMIBOLD,
		_menuInfoText[_sceneIndex].name, wcslen(_menuInfoText[_sceneIndex].name), RGB(255, 255, 255));

	SetTextAlign(getMemDC(), TA_LEFT);
	int _textBufferCnt = 150;
	const int SCRIPT_MAX_LENGTH = 30;

	// gray color font
	FONTMANAGER->drawText(getMemDC(), 36, 351, "돋움", 21, FW_SEMIBOLD, _menuInfoText[_sceneIndex].script,
		((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), RGB(100, 100, 100));

	if (wcslen(_menuInfoText[_sceneIndex].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
	{
		FONTMANAGER->drawText(getMemDC(), 36, 381, "돋움", 21, FW_SEMIBOLD,
			_menuInfoText[_sceneIndex].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_menuInfoText[_sceneIndex].script)) ?
			wcslen(_menuInfoText[_sceneIndex].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, RGB(100, 100, 100));
	}

	// black color font
	FONTMANAGER->drawText(getMemDC(), 35, 350, "돋움", 21, FW_SEMIBOLD, _menuInfoText[_sceneIndex].script,
		((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), RGB(0, 0, 0));

	if (wcslen(_menuInfoText[_sceneIndex].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
	{
		FONTMANAGER->drawText(getMemDC(), 35, 380, "돋움", 21, FW_SEMIBOLD,
			_menuInfoText[_sceneIndex].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_menuInfoText[_sceneIndex].script)) ?
			wcslen(_menuInfoText[_sceneIndex].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, RGB(0, 0, 0));
	}
}
