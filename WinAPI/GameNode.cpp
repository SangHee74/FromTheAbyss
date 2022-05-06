#include "Stdafx.h"
#include "GameNode.h"
#include <Locale.h>

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;


	if (managerInit)
	{	
		setlocale(LC_ALL, "Korean");

		SetTimer(_hWnd, 1, 10, NULL);
		
		KEYMANAGER->init();

		RND->init();

		IMAGEMANAGER->init();


		TIMEMANAGER->init();

		TEXTDATAMANAGER->init();

		SCENEMANAGER->init();

		SOUNDMANAGER->init();

		CAM->init();

		DATAMANAGER->init();


	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();

		RND->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		FONTMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		CAM->release();
		CAM->releaseSingleton();

		DATAMANAGER->release();
		DATAMANAGER->releaseSingleton();

		
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		
	PAINTSTRUCT ps;

	switch (imessage)
	{
	case WM_TIMER:
		break;
	case WM_CREATE: 
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		InvalidateRect(hWnd, NULL, false); 
		break;

	case WM_DESTROY:  
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, imessage, wParam, lParam);
	return LRESULT();
}
