#include "Stdafx.h"
#include "Castle.h"



Castle::Castle()
{
	// abyss 0 = first
		_castleText.abyss1[0].text = L"아아 ... 당신도 거대한 마 토벌을 지원해주셨군요. "	; 	// 0
		_castleText.abyss1[1].text = L"우리나라는 마물들의 습격에 의해 날로 전력을 잃어가고 있습니다. " ; // 1
		_castleText.abyss1[2].text = L"아직은 성 안으로 침공하는 걸 막고 있지만, 그것도 그리 오래 버티진 못할 것입니다. "  ; // 1
		_castleText.abyss1[3].text = L"이대로 방어만 계속 하다간, 언젠가 나라의 전력이 다해 백성들이 모두 마물들에게 ...  "  ; // 1
		_castleText.abyss1[4].text = L"그것만은 내 목숨과 바꿔서라도 막지 않으면 안됩니다. "	    ; // 1
		_castleText.abyss1[5].text = L"하지만, 거대한 마는 지금도 차원의 마궁 안에서 힘을 키우고 있습니다.  "  ; // 1
		_castleText.abyss1[6].text = L"거대한 마가 완전한 힘을 되찾을 때, 우리나라는 종말을 맞게 되겠지요 ...	 "	    ; // 1
		_castleText.abyss1[7].text = L"그리 되기 전에, 어떻게 해서든 그 마물을 쓰러뜨릴 수 밖에 없습니다. " ; // 0
		_castleText.abyss1[8].text = L"그리고, 그것은 모험자인 당신만이 해낼 수 있습니다.  "    ; // 0
		_castleText.abyss1[9].text = L"부탁드립니다.어비스 홀을 통해 차원의 미궁으로 들어가, 거대한 마를 쓰러뜨려주십시오!	 "    ; // 0
		_castleText.abyss1[10].text = L"우리나라가 평화와 사람들의 미소를 되찾을 수 있도록...! " ; // 0
		
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
			if (fadeOut.onOff.test(NEXT)) // 씬체인지
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

	// 메세지 박스 확인
	//RectangleMake(getMemDC(), )


	//void FontManager::drawText(HDC hdc, RECT rc, char* fontName, int fontSize, int fontWidth, string str, COLORREF color, bool clip)
	//
	//FONTMANAGER->drawText(getMemDC(), 36, 351, "돋움", 21, FW_SEMIBOLD, _castleText.abyss0[index].text,
	//	wcslen(_castleText.abyss0[index].text) , RGB(100, 100, 100));
}
