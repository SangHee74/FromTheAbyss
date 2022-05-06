#pragma once


class Timer
{
private:
	float _timeScale;			
	float _timeElapsed;			
	bool _isHardware;			

	__int64 _curTime;			
	__int64 _lastTime;			
	__int64 _periodFrequency;	
								
								
								


	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;			// 게임시작후 경과된 전체시간 

public:

	HRESULT init(void);

	// 현재 시간 계산
	void tick(float lockFPS = 0.0f); 
	   
	// 현재 FPS
	unsigned long getFrameRate(char* str = nullptr) const;

	// 마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }
	
	// 전체 경과 시간 
	inline float getWorldTime(void)  const { return _worldTime; }


	Timer() {}
	~Timer() {}


};

