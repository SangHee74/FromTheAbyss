#pragma once
#include "SingletonBase.h"

/*
FMOD
-Sound Engine 라이브러리
ㄴ Unreal Engine과 Unity Engine에는 라이센스 계약으로 기본내장됨.
ㄴ 이외의 대부분의 플랫폼에서는 사용하기 위해 선행준비 해줘야 함. 
*/

/*
const, constexpr
ㄴ C++11 (모던 C++)
ㄴ 해당 객체나 함수의 리턴값을 "컴파일" 타임에 알 수 있다.(값)
ㄴ C++ 17부터는 람다식에도 적용이 된다. 

※ 컴파일 타임에 값이 결정되므로 함수 호출 간 템플릿 인자로 넘겨 줄 때 유용하다.

const와 constexpr의 차이점은 초기화 여부와 오류 발견 시기.
ㄴ const 변수는 초기화를 런타임까지 지연 시킬 수 있지만 (C++에서 포인트로 접근해 수정이 가능하다. )
ㄴ constecpr 변수는 반드시 컴파일 타임에 초기화가 되어 있어야 한다.(C++에서도 접근을 못하는 진짜 상수..)

*/

/* C++ 스타일 */
constexpr auto soundBuffer = 10;
constexpr auto extraSoundCgannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundCgannel;

using namespace FMOD;

class SoundManager :public SingletonBase <SoundManager>
{
private:
	// enum을 대체하여 map 사용.
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;


	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	SoundManager();
	~SoundManager() {}


	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool backGround, bool loop);


	// 사운드 플레이
	void play(string keyName,float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);


	int getSoundCount() { return _mTotalSounds.size(); }

	//sound 길이 
	unsigned int getLength(string keyName);
	//플레이 위치
	unsigned int getPosition(string keyName);
	void setPosition(string keyName, unsigned int position);

	float getVolume(string keyName);
	void setVolume(string keyName, float volume);
	void setAllVolume(float volume);

};



#if 0 // 1차 작성


/* C스타일 */
enum SOUNDKIND
{
	SOUND_BGM = 0,
	SOUND_EFFECT_1,
	SOUND_EFFECT_2,
	SOUND_END
};

// 여분의 채널 갯수(버퍼)
#define EXTRA_SOUND_CHANNEL 5

// 총 사운드 갯수
#define TOTAL_SOUND_CHANNEL SOUND_END + EXTRA_SOUND_CHANNEL


// C# 스타일
class SoundManager :public SingletonBase <SoundManager>
{
private:
	System* _system;
	Sound** _sound;
	Channel** _channel;


public:
	SoundManager();
	~SoundManager() {}


	HRESULT init(void);
	void release(void);
	void update(void);

	// 사운드 파일 셋업
	void setUp(char* fileName, int soundKind,
		bool backGround, bool loop);

	// 사운드 플레이
	void play(int soundKind, float volume);

};

#endif
