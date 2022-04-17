#include "Stdafx.h"
#include "Store.h"

HRESULT Store::init(void)
{
	return S_OK;
}

void Store::release(void)
{
}

void Store::update(void)
{
}

void Store::render(void)
{
	IMGR("store",getMemDC());
	//IMGR("store2",getMemDC());
	//IMGR("store3",getMemDC());


}
