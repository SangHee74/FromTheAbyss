#include "Stdafx.h"
#include "Castle.h"

#pragma region CastleTextInit

Castle::Castle()
{
	_castleText.welcomText.text = L"    ~   �纥�Ͽ�Ʈ ��  ~    ";

	// abyss 0 = first
	//_castleText.abyss0[0].text = L"�ƾ� ... ��ŵ� �Ŵ��� �� ����� �������ּ̱���. "; 	// 0
	//_castleText.abyss0[1].text = L"�츮����� �������� ���ݿ� ���� ���� ������ �Ҿ�� �ֽ��ϴ�. "; // 1
	//_castleText.abyss0[2].text = L"������ �� ������ ħ���ϴ� �� ���� ������, �װ͵� �׸� ���� ��Ƽ�� ���� ���Դϴ�. "; // 1
	//_castleText.abyss0[3].text = L"�̴�� �� ��� �ϴٰ�, ������ ������ ������ ���� �鼺���� ��� �����鿡�� ... "; // 1
	//_castleText.abyss0[4].text = L"�װ͸��� �� ����� �ٲ㼭�� ���� ������ �ȵ˴ϴ�. "; // 1
	//_castleText.abyss0[5].text = L"������, �Ŵ��� ���� ���ݵ� ������ ���� �ȿ��� ���� Ű��� �ֽ��ϴ�. "; // 1
	//_castleText.abyss0[6].text = L"�Ŵ��� ���� ������ ���� ��ã�� ��, �츮����� ������ �°� �ǰ����� ... "; // 1
	//_castleText.abyss0[7].text = L"�׸� �Ǳ� ����, ��� �ؼ��� �� ������ �����߸� �� �ۿ� �����ϴ�. "; // 0
	//_castleText.abyss0[8].text = L"�׸���, �װ��� �������� ��Ÿ��� �س� �� �ֽ��ϴ�. "; // 0
	//_castleText.abyss0[9].text = L"��Ź�帳�ϴ�.��� Ȧ�� ���� ������ �̱����� ��, �Ŵ��� ���� �����߷��ֽʽÿ�! "; // 0
	//_castleText.abyss0[10].text = L"�츮���� ��ȭ�� ������� �̼Ҹ� ��ã�� �� �ֵ���...! "; // 0

	_castleText.abyss0[0].text = L"�ƾ� ... ��ŵ� �Ŵ��� �� ����� ";
	_castleText.abyss0[1].text = L"�������ּ̱���. "; 	
	_castleText.abyss0[2].text = L"";

	_castleText.abyss0[3].text = L"�츮����� �������� ���ݿ� ���� ";
	_castleText.abyss0[4].text = L"���� ������ �Ҿ�� �ֽ��ϴ�. "; // 1
	_castleText.abyss0[5].text = L"";

	_castleText.abyss0[6].text = L"������ �� ������ ħ���ϴ� �� ���� ������, ";
	_castleText.abyss0[7].text = L"�װ͵� �׸� ���� ��Ƽ�� ";
	_castleText.abyss0[8].text = L"���� ���Դϴ�. "; // 1
	
	_castleText.abyss0[9].text = L"��Ź�帳�ϴ�.��� Ȧ�� ";
	_castleText.abyss0[10].text = L"���� ������ �̱����� ��, ";
	_castleText.abyss0[11].text = L"�Ŵ��� ���� �����߷��ֽʽÿ�! "; // 0


	_castleText.abyss1[0].text = L"������ ���ƿԱ���, �����Դϴ�. "; 	// 0
	_castleText.abyss1[1].text = L"�̰��� ���迡 ������ �Ǿ����� ���ڱ���"; // 0
	_castleText.abyss1[2].text = L"���� ���� �������� �����ֽ��ϴ�. "; // 1
	_castleText.abyss1[3].text = L"�̳�Ÿ�츣���� ����Ʈ�� �� �Ŵ��� ������ �巯���� �մϴ�. "; // 1
	_castleText.abyss1[4].text = L"�װ����� ������ ��Ź�帳�ϴ�."; // 1




}
#pragma endregion

HRESULT Castle::init(void)
{
	storydCheck();

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

	if (PtInRect(&_next, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_textIndex < _maxIndex-3) _textIndex+=3;
		
		queenSmileCheck();
	}
		
	if (_textIndex + 2 == _maxIndex)
	{
		_nextCount++;
		if (_nextCount > 80)  fadeOut.onOff.set(ON);
	}

	fadeOut.update();
	if (fadeOut.onOff.test(NEXT)) // ��ü����
	{
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
		FONTMANAGER->drawText(getMemDC(), 166, 391, "����", 21, FW_SEMIBOLD, _castleText.welcomText.text,
			wcslen(_castleText.welcomText.text) , RGB(100, 100, 100));

		// black color font
		FONTMANAGER->drawText(getMemDC(), 165, 390, "����", 21, FW_SEMIBOLD, _castleText.welcomText.text,
			wcslen(_castleText.welcomText.text), RGB(0, 0, 0));
	}
	else
	{
		
		FONTMANAGER->drawText(getMemDC(), 30,355, "����", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex].text, wcslen(_castleText.abyss0[_textIndex].text), RGB(0, 0, 0));
		FONTMANAGER->drawText(getMemDC(), 30, 385, "����", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex+1].text, wcslen(_castleText.abyss0[_textIndex+1].text), RGB(0, 0, 0));
		FONTMANAGER->drawText(getMemDC(), 30, 415, "����", 21, FW_SEMIBOLD,
			_castleText.abyss0[_textIndex+2].text, wcslen(_castleText.abyss0[_textIndex+2].text), RGB(0, 0, 0));



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
	// first Castle text
	if (DATAMANAGER->getStoryRewardAbyss().none()) 
	{
		_maxIndex = ABYSS0LAST - 1;;

		// if ( test(8) ) : reward receive
		if (DATAMANAGER->getStoryRewardCheck().test(2)) _textIndex = ABYSS0LAST - 2;

	}
	if (DATAMANAGER->getStoryRewardAbyss().test(0))
	{

	}


}