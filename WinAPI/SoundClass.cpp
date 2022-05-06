#include "Stdafx.h"
#include "SoundClass.h"

HRESULT SoundClass::init(void)
{
	SOUNDMANAGER->addSound("title",    "Resources/sounds/title.wav", true, true);
	SOUNDMANAGER->addSound("save",     "Resources/sounds/save.wav", true, true);
	SOUNDMANAGER->addSound("mainHall", "Resources/sounds/mainHall.wav", true, true);
	SOUNDMANAGER->addSound("abyss",    "Resources/sounds/abyss.wav", true, true);
	SOUNDMANAGER->addSound("village",  "Resources/sounds/village.wav", true, true);
	SOUNDMANAGER->addSound("castle",   "Resources/sounds/castle.wav", true, true);
	SOUNDMANAGER->addSound("stage11",  "Resources/sounds/stage11.wav", true, true);
	SOUNDMANAGER->addSound("stage14",  "Resources/sounds/stage14.wav", true, true);


	return S_OK;
}

SoundClass::SoundClass()
{
}

SoundClass::~SoundClass()
{
}
