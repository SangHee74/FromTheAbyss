#pragma once
#include "Image.h"

static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;


public:
	GameNode() {}
	virtual ~GameNode() {}

	virtual HRESULT init(void);
	virtual HRESULT init(bool _managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	// 백버퍼 이미지 얻기
	Image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	// 메인 프로시저
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

