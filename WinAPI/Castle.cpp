#include "Stdafx.h"
#include "Castle.h"



Castle::Castle()
{
	// abyss 1 
	_castleText.abyss1Text[0].text = L"¾î½º¿Í";

	_castleText.abyssCheck.set(0);

}

HRESULT Castle::init(void)
{

	_isQueenSmile = true;
	return S_OK;
}

void Castle::release(void)
{
}

void Castle::update(void)
{
}

void Castle::render(void)
{
	int abyssIdx = DATAMANAGER->getPlayer()->getPlayerAbyss().abyss;


	if(_isQueenSmile) IMGR("castle1",getMemDC());
	else IMGR("castle2", getMemDC());




}
