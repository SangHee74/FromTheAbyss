#pragma once


class Timer
{
private:
	float _timeScale;			// 경과시간 조절 
	float _timeElapsed;			// 마지막 시간과 현재시간의 경과값
	bool _isHardware;			// 고성능 타이머 지원 여부

	__int64 _curTime;			// 현재시간
	__int64 _lastTime;			// 이전시간 
	__int64 _periodFrequency;	// 시간주기 
								// ㄴ 초당 파악할 수 있는 시간이 들어간다.
								// 밀리세컨까지 계산이 가능하다면
								// 1000의 값이 그대로 들어간다.


	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;			// 게임시작후 경과된 전체시간 

public:

	HRESULT init(void);

	// 현재 시간 계산
	void tick(float lockFPS = 0.0f); 
	   
	// 현재 FPS
	// 멤버 함수() + const : 외부에서 수정 절대 금지함, 변경안됨
	unsigned long getFrameRate(char* str = nullptr) const;

	// 마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }
	
	// 전체 경과 시간 
	inline float getWorldTime(void)  const { return _worldTime; }


	Timer() {}
	~Timer() {}


};

