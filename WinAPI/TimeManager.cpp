#include "Stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init(void)
{
	_timer = new Timer;
	_timer->init();
	return S_OK;
}

// 전역에서 사용하는 타이머 기능이기 때문에 
// 프로그램에서 터지지 않게 확인하는것이 중요하다.
void TimeManager::release(void)
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
		_timer = nullptr;
	}
}

void TimeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}

void TimeManager::render(HDC hdc)
{
	char str[256];

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0,0,255));

	/*
	// 타이머 중 프로그래머에게 필요한 정보(경과시간 ... 등을 확인하기 위해)
	_DEBUG
	Release Mode가 아닌 디버그일때만 실행
	ㄴ 개발을 하면서 테스트의 용도가 강하다.
	ㄴ _DEBUG는 절대 밖으로 공개되지 않아야 하므로 assert로 강력하게 확인한다.
	*/
#ifdef _DEBUG

	//assert();
	if (_timer != nullptr)
	{
		// 프레임
		sprintf_s(str, "FramePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		// 월드 시간 
		sprintf_s(str, "WorldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		// 갱신 시간 
		sprintf_s(str, "ElapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));

		// 값 확인용 
		//int n = 0; 
	}

	//Release
#else 
	if (_timer != nullptr)
	{
		// 프레임
		sprintf_s(str, "FramePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}

#endif
}
