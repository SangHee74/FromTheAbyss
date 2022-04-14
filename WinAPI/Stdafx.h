#pragma once
#include <sdkddkver.h>

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외
#define WIN32_LEAN_AND_MEAN 

// 형변환 데이터 손실 
#pragma warning(disable:4244)

//! Windows 헤더 파일
#include <Windows.h>

//! 라이브러리
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib") // 플레이 사운드를 사용하기 위해 추가했던 라이브러리. + 0209 timeGetTime
#pragma comment (lib,"msimg32.lib") // 알파 블렌드를 사용하기 위한 라이브러리
#pragma comment (lib,"lib/FMOD/fmodex_vc.lib") // 사운드를 사용하기 위한 라이브러리
#pragma comment (lib,"lib/Jsoncpp/json_vc71_libmtd.lib") // Json을 사용하기 위한 라이브러리


//! 외부 헤더 파일
#include "inc/FMOD/fmod.hpp"
#include "inc/Jsoncpp/json.h"


//! C 런타임 헤더 파일
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <mciapi.h>


//! C++ 런타임 헤더 파일
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <functional> // 알고리즘에 따라오는 : 보이드 포인터를 변수처럼 던진다
#include <fstream> // 파일 입출력
#include <queue> // 큐

using namespace std;

//===================================
// # 내가 만든 헤더파일을 이곳에 추가 #
//===================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "Utils.h"
#include "Text.h"
#include "TimeManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "JsonSaveLoader.h"
#include "Camera.h"
#include "ObjectManager.h"

using namespace MY_UTIL;

//========================
// # 싱글톤을 이곳에 추가 #
//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()
#define CAM Camera::getSingleton()
#define OBJMANAGER ObjectManager::getSingleton()


//============================
// # 매크로 # (윈도우창 초기화)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

#define MGT true,RGB(255,0,255)
//IMAGEMANAGER
#define IMG IMAGEMANAGER->findImage
#define IMGR IMAGEMANAGER->render
#define IMGFR IMAGEMANAGER->frameRender
#define IMGAR IMAGEMANAGER->alphaRender
#define IMGFAR IMAGEMANAGER->frameAlphaRender
//KEYMANAGER
#define KEYOKD KEYMANAGER->isOnceKeyDown
#define KEYOKU KEYMANAGER->isOnceKeyUp
#define KEYSKD KEYMANAGER->isStayKeyDown
#define KEYTOG KEYMANAGER->isToggleKey



//#define MAPTOOL

//#define FULLSCREEN
/*
#ifdef FULLSCREEN
#define WINSTART_X	 1920 // 모니터에 따라 다름 
#define WINSTART_Y	 0
// GetSystemMetrics 인자로 전달되는 시스템 설정 정보 현황
// ㄴSM_CXSCREEN / SM_CYSCREEN :  현재 화면 해상도 X, Y축 반환 
#define WINSIZE_X	 GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	 WS_POPUPWINDOW | WS_MAXWIZE
*/

#ifdef MAPTOOL
#define WINSTART_X	 50
#define WINSTART_Y	 20
#define WINSIZE_X	 1280 // 1200
#define WINSIZE_Y	 720 // 675
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU

#else
#define WINSTART_X	 100
#define WINSTART_Y	 100
#define WINSIZE_X	 1280 // 1200
#define WINSIZE_Y	 480 // 675
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU
#endif 


//============================
// # 매크로 # (기능 및 효율)
//============================
#define CENTER_X WINSIZE_X/2
#define CENTER_Y WINSIZE_Y/2
#define LSCENTER_X CENTER_X-(CENTER_X*0.5) 
#define RSCENTER_X CENTER_X+(CENTER_X*0.5) 

#define MAGNI WINSIZE_X/512   //magnification


//===============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}
//#define SAFE_DESTROY(p)	

//=============
// # 전역변수 #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

//=========================
// # 편의를 위한 매니저 #
//=========================
#include "DataManager.h"
#define DATAMANAGER DataManager::getSingleton()

