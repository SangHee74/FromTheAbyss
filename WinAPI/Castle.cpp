#include "Stdafx.h"
#include "Castle.h"



Castle::Castle()
{
	// abyss 0 = first
		_castleText.abyss1[0].text = L"�ƾ� ... ��ŵ� �Ŵ��� �� ����� �������ּ̱���. "	; 	// 0
		_castleText.abyss1[1].text = L"�츮����� �������� ���ݿ� ���� ���� ������ �Ҿ�� �ֽ��ϴ�. " ; // 1
		_castleText.abyss1[2].text = L"������ �� ������ ħ���ϴ� �� ���� ������, �װ͵� �׸� ���� ��Ƽ�� ���� ���Դϴ�. "  ; // 1
		_castleText.abyss1[3].text = L"�̴�� �� ��� �ϴٰ�, ������ ������ ������ ���� �鼺���� ��� �����鿡�� ...  "  ; // 1
		_castleText.abyss1[4].text = L"�װ͸��� �� ����� �ٲ㼭�� ���� ������ �ȵ˴ϴ�. "	    ; // 1
		_castleText.abyss1[5].text = L"������, �Ŵ��� ���� ���ݵ� ������ ���� �ȿ��� ���� Ű��� �ֽ��ϴ�.  "  ; // 1
		_castleText.abyss1[6].text = L"�Ŵ��� ���� ������ ���� ��ã�� ��, �츮����� ������ �°� �ǰ����� ...	 "	    ; // 1
		_castleText.abyss1[7].text = L"�׸� �Ǳ� ����, ��� �ؼ��� �� ������ �����߸� �� �ۿ� �����ϴ�. " ; // 0
		_castleText.abyss1[8].text = L"�׸���, �װ��� �������� ��Ÿ��� �س� �� �ֽ��ϴ�.  "    ; // 0
		_castleText.abyss1[9].text = L"��Ź�帳�ϴ�.��� Ȧ�� ���� ������ �̱����� ��, �Ŵ��� ���� �����߷��ֽʽÿ�!	 "    ; // 0
		_castleText.abyss1[10].text = L"�츮���� ��ȭ�� ������� �̼Ҹ� ��ã�� �� �ֵ���...! " ; // 0
		
}

HRESULT Castle::init(void)
{
	int w = IMG("nextButton")->getWidth();
	int h = IMG("nextButton")->getHeight();
	_next = RectMake(RSCENTER_X - (w*0.5), CENTER_Y - (h*0.5), w, h);
	_isQueenSmile = true;

	fadeOut.init();

	return S_OK;
}

void Castle::release(void)
{
}

void Castle::update(void)
{
	queenSmileCheck();

	if (PtInRect(&_next, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_textIndex++;
		if (_textIndex == _maxIndex + 1)
		{
			fadeOut.update();
			if (fadeOut.onOff.test(NEXT)) // ��ü����
			{
				SCENEMANAGER->changeScene("mainHall");
			}
		}
	}
}

void Castle::render(void)
{
	int abyssIdx = DATAMANAGER->getPlayer()->getPlayerAbyss().abyss;


	if(_isQueenSmile) IMGR("castle1",getMemDC());
	else IMGR("castle2", getMemDC());

	showDialogue(_textIndex);


}

void Castle::queenSmileCheck()
{
	if (_castleText.abyss0[0].text || _castleText.abyss0[7].text || _castleText.abyss0[8].text
		|| _castleText.abyss0[9].text || _castleText.abyss0[10].text)
	{
		_isQueenSmile = false;
	}
	else _isQueenSmile = true;
}

void Castle::showDialogue(int index)
{
	// first Dialogue (new Game)
	//if (DATAMANAGER->getStoryRewardCheck().test(0))
	//{
	//	// if ( test(8) ) : reward receive
	//	if (DATAMANAGER->getStoryRewardCheck().test(2)) _castleText.abyss0[ABYSS0LAST-2].text;
	//	else _castleText.abyss0[index].text;
	//}
	//
	//if((DATAMANAGER->getStoryRewardCheck().test(1)))
	//{
	//	// if ( test(8) ) : reward receive
	//	if (DATAMANAGER->getStoryRewardCheck().test(2)) _castleText.abyss0[ABYSS1LAST - 2].text;
	//	else _castleText.abyss0[index].text;
	//}

	// �޼��� �ڽ� Ȯ��
	//RectangleMake(getMemDC(), )


	//void FontManager::drawText(HDC hdc, RECT rc, char* fontName, int fontSize, int fontWidth, string str, COLORREF color, bool clip)
	//
	//FONTMANAGER->drawText(getMemDC(), 36, 351, "����", 21, FW_SEMIBOLD, _castleText.abyss0[index].text,
	//	wcslen(_castleText.abyss0[index].text) , RGB(100, 100, 100));
}
