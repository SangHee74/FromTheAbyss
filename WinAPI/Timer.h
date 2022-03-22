#pragma once

/*
Ÿ�̸��� ���� ���ڰ� ������ ���ػ� vs ���ػ� 
- ������ ����ϴ� API �����Լ�
GetTickCount(); //32��Ʈ�� - 48-9���� �Ǹ� ����
GetTickCount64(); // 64��Ʈ�� 
*/


/*
Timer 
= �ð��� �����ϴ� �Լ����� ������ ���� �⺻������ �����찡
���۵� ���� ���� �ð��� Milli Second�� ��ȯ

- ���� Ÿ�̸Ӹ� ������ �� �˾Ƶ־� �� ������ �ػ󵵿� Ŭ��

 �ػ�?
- �پ��� �ð� �Լ����� �ð��� �����ϱ� ���� �������� Tick�������� �ִ�.
�� 1���� �������� �󸶳� ���� ���������� ���� �� �ִ��� 
�� 1�е��� �󸶳� ���� Tick���� ������ �ð��� ��Ȯ���� ���̳Ŀ� ����
���ػ󵵿� ���ػ󵵷� ������.

	Ŭ��(Clock)? ������ 
	- Ÿ�̸ӿ��� ����ϴ� Ŭ���� CPU Ŭ��(Clock)�� �ǹ��Ѵ�.
	- Ŭ�� ��ü�� ������ ȸ���� ������ ���� �� �̸� Hz�� ǥ�� 
	�� 1Hz : 1�ʶ�� �����Ͽ� ��ȣ(0or1)�� �� �� �ش�.
								�� 1��Ʈ�� �ѹ� �ű��.
	i5-4690 CPU @ 3.50GHz   3.50 GHz
	�� 1GHz 1�Ⱑ�츣�� : 10�� 9���� -> 10��� 
	�� 3GHz 3�Ⱑ �츣�� : 30���
							�� 1�ʿ� 30�ﰳ�� ��Ʈ�� �ű� �� �ִ�.
	�� ���� Ÿ�̸��� ��� ������ ����Ű�� ���� ��ø�� �ʿ���
	�� �뷫 9�鸸���� 1�ʱ��� ����\
	- �⺻������ �����ϰ� ����� �� �鸸���� 1�ʱ��� ��������

*/

class Timer
{
private:
	float _timeScale;			// ����ð� ���� 
	float _timeElapsed;			// ������ �ð��� ����ð��� �����
	bool _isHardware;			// ���� Ÿ�̸� ���� ����

	__int64 _curTime;			// ����ð�
	__int64 _lastTime;			// �����ð� 
	__int64 _periodFrequency;	// �ð��ֱ� 
								// �� �ʴ� �ľ��� �� �ִ� �ð��� ����.
								// �и��������� ����� �����ϴٸ�
								// 1000�� ���� �״�� ����.


	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;			// ���ӽ����� ����� ��ü�ð� 

public:

	HRESULT init(void);

	// ���� �ð� ���
	void tick(float lockFPS = 0.0f); 
	   
	// ���� FPS
	// ��� �Լ�() + const : �ܺο��� ���� ���� ������, ����ȵ�
	unsigned long getFrameRate(char* str = nullptr) const;

	// ������ �ð��� ���� �ð��� �����
	inline float getElapsedTime(void) const { return _timeElapsed; }
	
	// ��ü ��� �ð� 
	inline float getWorldTime(void)  const { return _worldTime; }


	Timer() {}
	~Timer() {}


};

