//WinMain
#include "Stdafx.h"
#include "MainGame.h"

//==============
//# 전역 변수 #
//==============
HINSTANCE _hInstance;
HWND      _hWnd;
POINT	  _ptMouse;


//! 콜백 함수
//===================
//# 함수 전방 선언 #
//===================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int wideh, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_mg = new MainGame();

	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;									  //클래스 여분 메모리 (안써이거우리)
	wndClass.cbWndExtra = 0;							    	  //윈도우 여분 메모리 (안써이거우리)
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	  //백그라운드
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);		  //마우스커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		  //아이콘
	wndClass.hInstance = hInstance;							  //윈도우를 소유한 식별자 정보
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						  //윈도우 프로시저                     
	wndClass.lpszClassName = WINNAME;					     		  //클래스이름
	wndClass.lpszMenuName = NULL;									  //메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;				  //윈도우 스타일 (다시 그리기 정보)

	RegisterClass(&wndClass);

#ifdef FULLSCREEN

	// 디바이스 모드 구조체 : 화면 디스플레이 관련 기능
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));
	dm.dmBitsPerPel = 32; // 32비트 트루컬러
	dm.dmPelsWidth=1980; // 해상도 
	dm.dmPelsHeight = 1020;
	dm.dmDisplayFrequency = 80;	// 재생빈도 

	// 다양한 디스플레이 정보 중 우리가 사용한 정보값만 넘겨준다.
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
	// 화면이 종료되면 자동으로 원래 화면의 해상도로 돌린다.
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

#else
	_hWnd = CreateWindow //크리에이트로 셋팅
	(
		WINNAME,					  //윈도우 클래스 식별자
		WINNAME,					  //윈도우 타이틀 바 이름
		WINSTYLE,					  //윈도우 스타일
		WINSTART_X,					  //윈도우 화면 X좌표
		WINSTART_Y,					  //윈도우 화면 Y좌표
		WINSIZE_X,					  //윈도우 화면 가로크기
		WINSIZE_Y,					  //윈도우 화면 세로크기
		NULL,//확장성을 위해 널		  //부모 윈도우 //GetDesktopWindow() 이걸 많이 줌
		(HMENU)NULL,				  //메뉴 핸들
		hInstance,					  //인스턴스 지정
		NULL						  //윈도우의 자식 윈도우를 생성하면 지정, 그렇지 않으면 NULL
									  // ㄴ필요에 의해서 사용하지만 지금은 NULL
	);


	//클라이언트 영역의 사이즈를 정확히 잡아준다.
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#endif

	ShowWindow(_hWnd, nCmdShow); //화면에 부르기! 뿌린다


	//메인게임 클래스 초기화 실패시 종료
	if (FAILED(_mg->init()))
	{
		return 0;
	}

	MSG message;

	while (true) // 게임 - 핸들을 넣으면 while문에 종속됨. 
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) //
		{
			if (message.message == WM_QUIT)
				break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}

	_mg->release();
	delete _mg;

	//! 윈도우 클래스 등록 해제
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

//!윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}


//클라이언트 사이즈 맞추는 작업
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	//클라이언트 사이즈를 잡아줌


	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);


	//얻어온 렉트의 정보로 윈도우 사이즈 셋팅
	//마우스 가따대면 인자값 보임
	SetWindowPos
	(
		_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE
	);

}