#include "Stdafx.h"
#include "Castle.h"

HRESULT Castle::init(void)
{
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
	IMG("castle")->render(getMemDC());


}
