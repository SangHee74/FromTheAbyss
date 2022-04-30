#include "Stdafx.h"
#include "Castle.h"


Castle::Castle()
{
	_castleText.welcomText.text = L"    ~   �纥�Ͽ�Ʈ ��  ~    ";
}

HRESULT Castle::init(void)
{

	SOUNDMANAGER->play("castle", 0.05f);


	storydCheck(); // ��� �ܰ迡 ���� ��� �߰� 

	_messageBox = RectMake(30, 345, 580, 110);

	int w = IMG("nextButton")->getWidth();
	int h = IMG("nextButton")->getHeight();
	_next = RectMake(RSCENTER_X - (w*0.5), CENTER_Y - (h*0.5), w, h);

	_textIndex = 0;
	_nextCount = 0;
	_isQueenSmile = true;
	_firstBG = true;

	fadeOut.init();

	DATAMANAGER->getStoryRewardAbyss().set(0);


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


	if (PtInRect(&_next, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (DATAMANAGER->getStoryRewardAbyss().none())
		{
			if (_textIndex < _maxIndex - 3) _textIndex += 3;
		}
		if (DATAMANAGER->getStoryRewardAbyss().test(0))
		{
			if (_textIndex < _maxIndex - 3) _textIndex += 2;
		}
		else
		{
			if (_textIndex < _maxIndex ) _textIndex ++;
		}
		queenSmileCheck();
	}
		
	// lastText -> sceneChange start
	if (DATAMANAGER->getStoryRewardAbyss().none())
	{
		if (_textIndex  == 9)  // first castle Text -> change Scene
		{
			_nextCount++;
			if (_nextCount > 110)
			{
				_nextCount = 0;
				fadeOut.onOff.set(ON);
			}
		}
	}

	cout << "_textIndex  : " << _textIndex << endl;
	cout << " _nextCount : " << _nextCount << endl;
	if (DATAMANAGER->getStoryRewardAbyss().test(0))
	{
		if (_textIndex == 4) 
		{
			_nextCount++;
			if (_nextCount > 60)
			{
				_nextCount = 0;
				fadeOut.onOff.set(ON);
			}
		}
	}
	else
	{
		if (_textIndex == _maxIndex)
		{
			_nextCount++;
			if (_nextCount > 60)
			{
				_nextCount = 0;
				fadeOut.onOff.set(ON);
			}
		}
	}


	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // ��ü����
	{
		SOUNDMANAGER->stop("castle");
		SCENEMANAGER->changeScene("main");
	}
}

void Castle::render(void)
{
	int abyssIdx = DATAMANAGER->getPlayer()->getPlayerAbyss().abyss;
	

	if (_firstBG)
	{
		IMGR("castle", getMemDC());
		
		// gray color font
		FONTMANAGER->drawText(getMemDC(), 166, 391, "����", 21, FW_SEMIBOLD, _castleText.welcomText.text,
			wcslen(_castleText.welcomText.text) , RGB(100, 100, 100));

		// black color font
		FONTMANAGER->drawText(getMemDC(), 165, 390, "����", 21, FW_SEMIBOLD, _castleText.welcomText.text,
			wcslen(_castleText.welcomText.text), RGB(0, 0, 0));
	}
	else
	{
		if (_isQueenSmile) IMGR("castle1", getMemDC());
		else IMGR("castle2", getMemDC());
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

	if (DATAMANAGER->getStoryRewardAbyss().none())
	{
		_maxIndex = ABYSS0LAST;
		_castleText.abyss0[0].text = L"�ƾ� ... ��ŵ� �Ŵ��� �� ����� ";
		_castleText.abyss0[1].text = L"�������ּ̱���. ";
		_castleText.abyss0[2].text = L"";
		_castleText.abyss0[3].text = L"�츮����� �������� ���ݿ� ���� ";
		_castleText.abyss0[4].text = L"���� ������ �Ҿ�� �ֽ��ϴ�. "; // 1
		_castleText.abyss0[5].text = L"";
		_castleText.abyss0[6].text = L"������ �� ������ ħ���ϴ� �� ���� ������, ";
		_castleText.abyss0[7].text = L"�װ͵� �׸� ���� ��Ƽ�� ���� ���Դϴ�. ";
		_castleText.abyss0[8].text = L"";
		_castleText.abyss0[9].text = L"��Ź�帳�ϴ�.��� Ȧ�� ���� ������ �̱����� ��,";
		_castleText.abyss0[10].text = L"�Ŵ��� ���� �����߷��ֽʽÿ�! "; // 0
		_castleText.abyss0[11].text = L" ";
	}
	if (DATAMANAGER->getStoryRewardAbyss().test(0)) 
	{
		_maxIndex = ABYSS1LAST;

		_castleText.abyss1[0].text = L"������ ���ƿԱ���, ���谡. ";
		_castleText.abyss1[1].text = L"ũ�� ��ġ�� �ʾƺ��� �����Դϴ�. "; 	// 0
		_castleText.abyss1[2].text = L"���� �����뿡 ������ �̳�Ÿ�츣���� ������ �� ";
		_castleText.abyss1[3].text = L"��ó���� �Ŵ��� ������ �巯���ٰ� �մϴ�. "; // 1
		_castleText.abyss1[4].text = L"������ Ǯ���� �װ����� ������ ��Ź�帳�ϴ�."; // 1
		_castleText.abyss1[5].text = L""; // 1

		DATAMANAGER->getPlayer()->getPlayerAbyss().abyss = 2;
		DATAMANAGER->getPlayer()->getPlayerAbyss().stage = 1;
	}

}
void Castle::storydRender()
{
	if (DATAMANAGER->getStoryRewardAbyss().none())
	{
		FONTMANAGER->drawText(getMemDC(), 30, 355, "����", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex].text, wcslen(_castleText.abyss0[_textIndex].text), RGB(0, 0, 0));
		FONTMANAGER->drawText(getMemDC(), 30, 385, "����", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex + 1].text, wcslen(_castleText.abyss0[_textIndex + 1].text), RGB(0, 0, 0));
		FONTMANAGER->drawText(getMemDC(), 30, 415, "����", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex + 2].text, wcslen(_castleText.abyss0[_textIndex + 2].text), RGB(0, 0, 0));
	}
	if (DATAMANAGER->getStoryRewardAbyss().test(0))
	{
		FONTMANAGER->drawText(getMemDC(), 30, 355, "����", 21, FW_SEMIBOLD,
			_castleText.abyss1[_textIndex].text, wcslen(_castleText.abyss1[_textIndex].text), RGB(0, 0, 0));
		FONTMANAGER->drawText(getMemDC(), 30, 385, "����", 21, FW_SEMIBOLD,
			_castleText.abyss1[_textIndex+1].text, wcslen(_castleText.abyss1[_textIndex+1].text), RGB(0, 0, 0));
	}


}

