#include "Stdafx.h"
#include "StartScene.h"
#include "ImageClass.h"

HRESULT StartScene::init(void)
{
	_img = new ImageClass;
	_img->init();

	return S_OK;
}

void StartScene::release(void)
{
	SAFE_DELETE(_img);
}

void StartScene::update(void)
{

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("이동맵");
	}
}

void StartScene::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	RECT rc = { 0,0,WINSIZE_X,WINSIZE_Y };


	IMAGEMANAGER->findImage("타이틀")->render(getMemDC());


}
