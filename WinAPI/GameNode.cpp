#include "Stdafx.h"
#include "GameNode.h"
#include <Locale.h>

HRESULT GameNode::init(void)
{
	//함수가 성공적으로 실행되었음을 알리는 S_OK 변환
	//Success_ok
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;


	if (managerInit)
	{	
		// 로케일 설정(디렉토리에서 한글로 검색하기 위해 필요) - 로케일 헤더 파일 추가할 것.
		setlocale(LC_ALL, "Korean"); // LC_ALL : OS에 저장된 한국(Korean) 정보를 모두 가져온다. 


		//타이머 초기화
		SetTimer(_hWnd, 1, 10, NULL);
		
		//키매니저 초기화
		KEYMANAGER->init();

		//랜덤 펑션 초기화
		RND->init();

		//이미지매니저 초기화
		IMAGEMANAGER->init();

		// 폰트매니저 초기화

		// 타임매니저 초기화
		TIMEMANAGER->init();

		// 텍스트 데이터 매니저 초기화
		TEXTDATAMANAGER->init();

		// 씬 매니저 초기화
		SCENEMANAGER->init();

		// 사운드 매니저 초기화
		SOUNDMANAGER->init();

		// 카메라 매니저 초기화
		CAM->init();


	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);

		//키매니저 싱글톤 해제
		KEYMANAGER->releaseSingleton();

		// 랜덤펑션 싱글톤 해제
		RND->releaseSingleton();

		// 이미지매니저 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		// 폰트매니저 싱글톤 해제 
		FONTMANAGER->releaseSingleton();

		// 타임매니저 해제 
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		// 텍스트 매니저 해제
		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		// 씬 매니저 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		// 사운드 매니저 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		// 제이슨 데이터 매니저 해제, 싱글톤 해제
		JSONDATAMANAGER->release();
		JSONDATAMANAGER->releaseSingleton();

		// 카메라 해제, 싱글톤 해제
		CAM->release();
		CAM->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	//새로고침
	//버퍼링이 추가되면 고민이 필요하다
	//InvalidateRect(_hWnd, NULL, FALSE);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		//핸들DC
	PAINTSTRUCT ps;	//페인트구조체

	switch (imessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_CREATE:  //생성자
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		//20211230 마우스좌표 
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0); //esc누르면 소멸자 부르기
			break;
		}
		InvalidateRect(hWnd, NULL, false);  // 화면이 계속 반짝거린다면 false 로 수정해야함 (지금 고쳐진상태임)
		break;

	case WM_DESTROY:    //소멸자
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, imessage, wParam, lParam);
	return LRESULT();
}
