#pragma once
#include "SingletonBase.h"


constexpr auto soundBuffer = 10;
constexpr auto extraSoundCgannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundCgannel;

using namespace FMOD;

class SoundManager :public SingletonBase <SoundManager>
{
private:
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
