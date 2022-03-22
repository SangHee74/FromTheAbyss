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
	IMG("store")->render(getMemDC());
	IMG("store2")->render(getMemDC());
	IMG("store3")->render(getMemDC());


}
