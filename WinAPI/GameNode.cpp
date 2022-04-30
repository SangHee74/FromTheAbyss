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
		// ������ ����(���丮���� �ѱ۷� �˻��ϱ� ���� �ʿ�) - ������ ��� ���� �߰��� ��.
		setlocale(LC_ALL, "Korean"); // LC_ALL : OS�� ����� �ѱ�(Korean) ������ ��� �����´�. 

		//Ÿ�̸� �ʱ�ȭ
		SetTimer(_hWnd, 1, 10, NULL);
		
		//Ű�Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();

		//���� ��� �ʱ�ȭ
		RND->init();

		//�̹����Ŵ��� �ʱ�ȭ
		IMAGEMANAGER->init();

		// ��Ʈ�Ŵ��� �ʱ�ȭ

		// Ÿ�ӸŴ��� �ʱ�ȭ
		TIMEMANAGER->init();

		// �ؽ�Ʈ ������ �Ŵ��� �ʱ�ȭ
		TEXTDATAMANAGER->init();

		// �� �Ŵ��� �ʱ�ȭ
		SCENEMANAGER->init();

		// ���� �Ŵ��� �ʱ�ȭ
		SOUNDMANAGER->init();

		// ī�޶� �Ŵ��� �ʱ�ȭ
		CAM->init();

		// ������ �Ŵ��� �ʱ�ȭ
		DATAMANAGER->init();


	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);

		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();

		// ������� �̱��� ����
		RND->releaseSingleton();

		// �̹����Ŵ��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		// ��Ʈ�Ŵ��� �̱��� ���� 
		FONTMANAGER->releaseSingleton();

		// Ÿ�ӸŴ��� ���� 
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		// �ؽ�Ʈ �Ŵ��� ����
		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		// �� �Ŵ��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		// ���� �Ŵ��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		// ���̽� ������ �Ŵ��� ���� 
		JSONDATAMANAGER->release();
		JSONDATAMANAGER->releaseSingleton();

		// ī�޶� ����, �̱��� ����
		CAM->release();
		CAM->releaseSingleton();

		// ������ �Ŵ��� ����
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
	HDC hdc;		//�ڵ�DC
	PAINTSTRUCT ps;	//����Ʈ����ü

	switch (imessage)
	{
	case WM_TIMER:
		break;
	case WM_CREATE:  //������
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

	case WM_DESTROY:    //�Ҹ���
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, imessage, wParam, lParam);
	return LRESULT();
}
