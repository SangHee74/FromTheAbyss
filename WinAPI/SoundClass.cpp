#include "Stdafx.h"
#include "SoundClass.h"

HRESULT SoundClass::init(void)
{
	SOUNDMANAGER->addSound("title", "Resources/sounds/abyss_title.wav", true, true);


	return S_OK;
}

SoundClass::SoundClass()
{
}

SoundClass::~SoundClass()
{
}
