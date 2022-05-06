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
	float _worldTime;			// ���ӽ����� ����� ��ü�ð� 

public:

	HRESULT init(void);

	// ���� �ð� ���
	void tick(float lockFPS = 0.0f); 
	   
	// ���� FPS
	unsigned long getFrameRate(char* str = nullptr) const;

	// ������ �ð��� ���� �ð��� �����
	inline float getElapsedTime(void) const { return _timeElapsed; }
	
	// ��ü ��� �ð� 
	inline float getWorldTime(void)  const { return _worldTime; }


	Timer() {}
	~Timer() {}


};

