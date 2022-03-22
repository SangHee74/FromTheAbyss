#include "Stdafx.h"
#include "Tutorial.h"

HRESULT Tutorial::init(void)
{
	return S_OK;
}

void Tutorial::release(void)
{
}

void Tutorial::update(void)
{
}

void Tutorial::render(void)
{
	IMGR("tutorial", getMemDC());
}
