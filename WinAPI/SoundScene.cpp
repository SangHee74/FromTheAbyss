#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{
	IMAGEMANAGER->addImage("���", "Resources/Images/BackGround/bg.bmp", WINSIZE_X, WINSIZE_Y);
	SOUNDMANAGER->addSound("end","Resources/sounds/end.mp3", true, true);
	SOUNDMANAGER->addSound("lk", "Resources/sounds/Love Killa - MonstaX.mp3", true, true);
	

	return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("lk", 0.1f);

	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stop("end");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
	{
		SOUNDMANAGER->pause("lk");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SOUNDMANAGER->resume("end");
	}

	SOUNDMANAGER->update();
}

void SoundScene::render(void)
{
	IMAGEMANAGER->render("���", getMemDC());
}


#if 0 // 1�� �ۼ�
HRESULT SoundScene::init(void)
{
	IMAGEMANAGER->addImage("���", "Resources/Images/BackGround/bg.bmp", WINSIZE_X, WINSIZE_Y);
	SOUNDMANAGER->setUp("���ϰ��", SOUND_BGM, true, true);

	return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play(SOUND_BGM, 1.0f);
	}
}

void SoundScene::render(void)
{
	IMAGEMANAGER->render("���", getMemDC());
}
#endif