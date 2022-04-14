#pragma once
#include <sdkddkver.h>

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN 

// ����ȯ ������ �ս� 
#pragma warning(disable:4244)

//! Windows ��� ����
#include <Windows.h>

//! ���̺귯��
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib") // �÷��� ���带 ����ϱ� ���� �߰��ߴ� ���̺귯��. + 0209 timeGetTime
#pragma comment (lib,"msimg32.lib") // ���� ���带 ����ϱ� ���� ���̺귯��
#pragma comment (lib,"lib/FMOD/fmodex_vc.lib") // ���带 ����ϱ� ���� ���̺귯��
#pragma comment (lib,"lib/Jsoncpp/json_vc71_libmtd.lib") // Json�� ����ϱ� ���� ���̺귯��


//! �ܺ� ��� ����
#include "inc/FMOD/fmod.hpp"
#include "inc/Jsoncpp/json.h"


//! C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <mciapi.h>


//! C++ ��Ÿ�� ��� ����
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <functional> // �˰��� ������� : ���̵� �����͸� ����ó�� ������
#include <fstream> // ���� �����
#include <queue> // ť

using namespace std;

//===================================
// # ���� ���� ��������� �̰��� �߰� #
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
// # �̱����� �̰��� �߰� #
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
// # ��ũ�� # (������â �ʱ�ȭ)
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
#define WINSTART_X	 1920 // ����Ϳ� ���� �ٸ� 
#define WINSTART_Y	 0
// GetSystemMetrics ���ڷ� ���޵Ǵ� �ý��� ���� ���� ��Ȳ
// ��SM_CXSCREEN / SM_CYSCREEN :  ���� ȭ�� �ػ� X, Y�� ��ȯ 
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
// # ��ũ�� # (��� �� ȿ��)
//============================
#define CENTER_X WINSIZE_X/2
#define CENTER_Y WINSIZE_Y/2
#define LSCENTER_X CENTER_X-(CENTER_X*0.5) 
#define RSCENTER_X CENTER_X+(CENTER_X*0.5) 

#define MAGNI WINSIZE_X/512   //magnification


//===============================================
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}
//#define SAFE_DESTROY(p)	

//=============
// # �������� #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

//=========================
// # ���Ǹ� ���� �Ŵ��� #
//=========================
#include "DataManager.h"
#define DATAMANAGER DataManager::getSingleton()

