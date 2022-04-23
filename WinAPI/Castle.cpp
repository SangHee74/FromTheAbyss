#include "Stdafx.h"
#include "Castle.h"



Castle::Castle()
{
	// abyss 1 
	_castleText.abyss1Text[0].text = L"¾î½º¿Í";



}

HRESULT Castle::init(void)
{
	int w = IMG("nextButton")->getWidth();
	int h = IMG("nextButton")->getHeight();
	_next = RectMake(RSCENTER_X - (w*0.5), CENTER_Y - (h*0.5), w, h);
	_isQueenSmile = true;
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
	if (_castleText.abyss0Text[0].text || _castleText.abyss0Text[7].text || _castleText.abyss0Text[8].text
		|| _castleText.abyss0Text[9].text || _castleText.abyss0Text[10].text)
	{
		_isQueenSmile = false;
	}
	else _isQueenSmile = true;
}

void Castle::showDialogue(int index)
{
	// first Dialogue (new Game)
	if (DATAMANAGER->getStoryRewardCheck().test(0))
	{
		// if ( test(3) ) : reward receive
		if (DATAMANAGER->getStoryRewardCheck().test(2)) _castleText.abyss0Text[ABYSS0LAST-2].text;
		else _castleText.abyss0Text[index].text;
	}
	else if((DATAMANAGER->getStoryRewardCheck().test(1)))
	{
		// if ( test(3) ) : reward receive
		if (DATAMANAGER->getStoryRewardCheck().test(2)) _castleText.abyss0Text[ABYSS1LAST - 2].text;
		else _castleText.abyss0Text[index].text;
	}
}
