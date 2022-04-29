#include "Stdafx.h"
#include "Castle.h"


Castle::Castle()
{
	_castleText.welcomText.text = L"    ~   루벤하우트 성  ~    ";
}

HRESULT Castle::init(void)
{

	SOUNDMANAGER->play("castle", 0.05f);


	storydCheck(); // 어비스 단계에 따라 대사 추가 

	_messageBox = RectMake(30, 345, 580, 110);

	int w = IMG("nextButton")->getWidth();
	int h = IMG("nextButton")->getHeight();
	_next = RectMake(RSCENTER_X - (w*0.5), CENTER_Y - (h*0.5), w, h);

	_textIndex = 0;
	_nextCount = 0;
	_isQueenSmile = true;
	_firstBG = true;

	fadeOut.init();

	return S_OK;
}

void Castle::release(void)
{
}

void Castle::update(void)
{

	if (_firstBG && PtInRect(&_next, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_firstBG = false;
	}

	// first Castle text
	if (DATAMANAGER->getStoryRewardAbyss().none())
	{
		_maxIndex = ABYSS0LAST - 1;;

		// if ( test(8) ) : reward receive
		if (DATAMANAGER->getStoryRewardCheck().test(2)) _textIndex = ABYSS0LAST - 2;
	}


	if (PtInRect(&_next, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (DATAMANAGER->getStoryRewardAbyss().test(0))
		{
			if (_textIndex < _maxIndex - 3) _textIndex += 3;
		}
		else
		{
			if (_textIndex < _maxIndex ) _textIndex ++;
		}
		queenSmileCheck();
	}
		
	// lastText -> sceneChange start
	if (DATAMANAGER->getStoryRewardAbyss().test(0))
	{
		if (_textIndex + 2 == _maxIndex)
		{
			_nextCount++;
			if (_nextCount > 80)  fadeOut.onOff.set(ON);
		}
	}
	else
	{
		if (_textIndex == _maxIndex)
		{
			_nextCount++;
			if (_nextCount > 60)  fadeOut.onOff.set(ON);
		}
	}


	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // 씬체인지
	{
		SOUNDMANAGER->stop("castle");
		SCENEMANAGER->changeScene("main");
	}
}

void Castle::render(void)
{
	int abyssIdx = DATAMANAGER->getPlayer()->getPlayerAbyss().abyss;


	if (_isQueenSmile) IMGR("castle1", getMemDC());
	else IMGR("castle2", getMemDC());

	if (_firstBG)
	{
		IMGR("castle", getMemDC());
		
		// gray color font
		FONTMANAGER->drawText(getMemDC(), 166, 391, "돋움", 21, FW_SEMIBOLD, _castleText.welcomText.text,
			wcslen(_castleText.welcomText.text) , RGB(100, 100, 100));

		// black color font
		FONTMANAGER->drawText(getMemDC(), 165, 390, "돋움", 21, FW_SEMIBOLD, _castleText.welcomText.text,
			wcslen(_castleText.welcomText.text), RGB(0, 0, 0));
	}
	else
	{
		IMGR("castle", getMemDC());
		storydRender();
	}


	// fadeOut
	fadeOut.blackImg->alphaRender(getMemDC(), fadeOut.alpha);

}






void Castle::queenSmileCheck()
{
	if (DATAMANAGER->getStoryRewardCheck().test(0))
	{
		if (_textIndex == 0 || _textIndex == 7 || _textIndex == 8 || _textIndex == 9 || _textIndex == 10)
		{
			_isQueenSmile = false;
		}
		else _isQueenSmile = true;
	}
}


void Castle::storydCheck()
{

	if (DATAMANAGER->getStoryRewardAbyss().test(0))
	{
		_castleText.abyss0[0].text = L"아아 ... 당신도 거대한 마 토벌을 ";
		_castleText.abyss0[1].text = L"지원해주셨군요. ";
		_castleText.abyss0[2].text = L"";
		_castleText.abyss0[3].text = L"우리나라는 마물들의 습격에 의해 ";
		_castleText.abyss0[4].text = L"날로 전력을 잃어가고 있습니다. "; // 1
		_castleText.abyss0[5].text = L"";
		_castleText.abyss0[6].text = L"아직은 성 안으로 침공하는 걸 막고 있지만, ";
		_castleText.abyss0[7].text = L"그것도 그리 오래 버티진 ";
		_castleText.abyss0[8].text = L"못할 것입니다. "; // 1
		_castleText.abyss0[9].text = L"부탁드립니다.어비스 홀을 ";
		_castleText.abyss0[10].text = L"통해 차원의 미궁으로 들어가, ";
		_castleText.abyss0[11].text = L"거대한 마를 쓰러뜨려주십시오! "; // 0
	}
	if (DATAMANAGER->getStoryRewardAbyss().test(1))
	{
		_castleText.abyss1[0].text = L"무사히 돌아왔군요, 모함가. 다행입니다. "; 	// 0
		_castleText.abyss1[1].text = L"이것이 모험에 도움이 되었으면 좋겠군요"; // 0
		_castleText.abyss1[2].text = L"미노타우르스를 쓰러트린 후 거대한 동굴이 드러났다고 합니다. "; // 1
		_castleText.abyss1[3].text = L"그곳으로 지원을 부탁드립니다."; // 1
	}

}
void Castle::storydRender()
{
	if (DATAMANAGER->getStoryRewardAbyss().test(0))
	{
		cout << "스토리0" << endl;
		FONTMANAGER->drawText(getMemDC(), 30, 355, "돋움", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex].text, wcslen(_castleText.abyss0[_textIndex].text), RGB(0, 0, 0));
		FONTMANAGER->drawText(getMemDC(), 30, 385, "돋움", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex + 1].text, wcslen(_castleText.abyss0[_textIndex + 1].text), RGB(0, 0, 0));
		FONTMANAGER->drawText(getMemDC(), 30, 415, "돋움", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex + 2].text, wcslen(_castleText.abyss0[_textIndex + 2].text), RGB(0, 0, 0));
	}
	if (DATAMANAGER->getStoryRewardAbyss().test(1))
	{
		cout << "스토리1" << endl;
		FONTMANAGER->drawText(getMemDC(), 30, 355, "돋움", 21, FW_SEMIBOLD,
			_castleText.abyss1[_textIndex].text, wcslen(_castleText.abyss1[_textIndex].text), RGB(0, 0, 0));
	}



}

