#include "Stdafx.h"
#include "Store.h"

int tempCount = 0;

HRESULT Store::init(void)
{
	int w = 150;
	int h = 110;
	_menu[0] = RectMakeCenter(820,250,w,h);
	_menu[1] = RectMakeCenter(1098,250,w,h);
	_category[0] = RectMakeCenter(758, 180, w, h);
	_category[1] = RectMakeCenter(963, 180, w, h);
	_category[2] = RectMakeCenter(1165, 180, w, h);
	_category[3] = RectMakeCenter(863, 322, w, h);
	_category[4]  = RectMakeCenter(1065, 322, w , h );

	w = IMG("nextButton")->getWidth();
	h = IMG("nextButton")->getHeight();
	_next = RectMake(RSCENTER_X - (w*0.5), CENTER_Y - (h*0.5), w, h);
	_back = RectMake(WINSIZE_X - 143, WINSIZE_Y - 53, 140, 50);
	_okBox = false;
	_isShowItemList = false;

	_storeMenu.reset(); // 사기, 팔기, 선택
	_storeCategory.reset(); // 무기, 방어구, 장신구, 도구, 스킬

	fadeOut.init();

	return S_OK;
}

void Store::release(void)
{
}

void Store::update(void)
{
	menuSelect();

	// cout count
	tempCount++;
	if (tempCount % 120 == 0)
	{
		tempCount = 0;
	}


	// Next Scene FadeOut
	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // 씬체인지
	{
		//SOUNDMANAGER->stop("");
		SCENEMANAGER->changeScene("main");
	}
}

void Store::render(void)
{
	if(_storeMenu.none())
	{
		IMGR("store4", getMemDC());
		IMGR("nextButton", getMemDC(), _next.left, _next.top);
		FONTMANAGER->firstLineText(getMemDC(), _storeText[0].text);
	}
	if (_storeMenu.test(0))
	{
		IMGR("store",getMemDC());
		FONTMANAGER->firstLineText(getMemDC(), _storeText[1].text);
	}

	if (_storeMenu.test(3)) // buy or sell  +  category(5type)
	{
		IMGR("store2", getMemDC());
		FONTMANAGER->firstLineText(getMemDC(), _storeText[2].text);
	}

	if (_storeCategory.any() ) // itemList
	{
		IMGR("store5", getMemDC());
	}


	//IMGR("store",getMemDC());
	//IMGR("store2",getMemDC());
	//IMGR("store4",getMemDC());
	//rcMake(getMemDC(), _next);
	//rcMake(getMemDC(), _back);

	if(_storeMenu.test(0)) //메뉴선택에서 사기/팔기 체크
	{
	rcMake(getMemDC(), _menu[STORE_BUY]   );
	rcMake(getMemDC(), _menu[STORE_SELL]  );
	}
	if (_storeMenu.test(3))
	{
	rcMake(getMemDC(), _category[STORE_WEAPON]);
	rcMake(getMemDC(), _category[STORE_ARMOR] );
	rcMake(getMemDC(), _category[STORE_ACC]	  );
	rcMake(getMemDC(), _category[STORE_POTION]);
	rcMake(getMemDC(), _category[STORE_SKILL] );
	}
	//rcMake(getMemDC(), _back );


	if (tempCount >= 119)
	{
		// tempcount2가 0이상일때 조건 넣으면 cout 출력

		if (_storeMenu.none() ) cout << "웰컴" << endl;
		if (_storeMenu.test(0)) cout << "메인" << endl;
		if (_storeMenu.test(1)) cout << "사기" << endl;
		if (_storeMenu.test(2)) cout << "팔기" << endl;
		if (_storeMenu.test(3)) cout << "인덱스(카테고리선택)" << endl;

		if (_storeCategory.test(0)) cout << "카테고리-무기" << endl;
		if (_storeCategory.test(1)) cout << "카테고리-방어구" << endl;
		if (_storeCategory.test(2)) cout << "카테고리-악세" << endl;
		if (_storeCategory.test(3)) cout << "카테고리-포션" << endl;
		if (_storeCategory.test(4)) cout << "카테고리-스킬" << endl;

	}

	// fadeOut
	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);
}

void Store::menuSelect()
{
	// welcom
	if (_storeCategory.none() && PtInRect(&_next, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeMenu.reset();
			_storeMenu.set(0);
		}
	}

	// main -> menu - buy
	if (_storeMenu.test(0) && PtInRect(&_menu[STORE_BUY], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeMenu.reset(0);
			_storeMenu.set(1);			_storeMenu.set(3);
		}
	}

	// main -> menu - sell
	if (_storeMenu.test(0) && PtInRect(&_menu[STORE_SELL], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeMenu.reset(0);
			_storeMenu.set(2); 			_storeMenu.set(3);
		}
	}

	// ======================================================
	//  Store Category Type (weapon, armor,acc,potion, skill)

	if (PtInRect(&_category[STORE_WEAPON], _ptMouse) && _storeCategory.none())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeCategory.set(0); //  weapon 
		}
	}
	if (PtInRect(&_category[STORE_ARMOR], _ptMouse) && _storeCategory.none())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeCategory.set(1); // armor
		}
	}
	if (PtInRect(&_category[STORE_ACC], _ptMouse) && _storeCategory.none())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeCategory.set(2); //  acc
		}
	}
	if (PtInRect(&_category[STORE_POTION], _ptMouse) && _storeCategory.none())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeCategory.set(3); //  potion
		}
	}
	if (PtInRect(&_category[STORE_SKILL], _ptMouse) && _storeCategory.none())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeCategory.set(4); //  skill
		}
	}


	//  BACK BUTTON ===============================================
	if (PtInRect(&_back, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// store main(menu select) -> mainHall
			if (_storeMenu.test(0))
			{
				fadeOut.onOff.set(ON);
			}

			// buy or sell ->  store main(menu select)
			if ((_storeMenu.test(1) || _storeMenu.test(2)) && _storeCategory.none())
			{
				_storeMenu.reset(); _storeCategory.reset();  _storeMenu.set(0);
			}

			// buy + category(list) -> buy
			if (_storeMenu.test(1) && _storeCategory.any() )
			{
				_storeCategory.reset(); 
				_storeMenu.set(1); _storeMenu.set(3); 
			}

			// sell + category(list) -> sell
			if (_storeMenu.test(2) && _storeCategory.any())
			{
				_storeCategory.reset(); 
				_storeMenu.set(2); _storeMenu.set(3);
			}

		}
	}
}
