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


	// ���� �÷���
	void play(string keyName,float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);


	int getSoundCount() { return _mTotalSounds.size(); }

	//sound ���� 
	unsigned int getLength(string keyName);
	//�÷��� ��ġ
	unsigned int getPosition(string keyName);
	void setPosition(string keyName, unsigned int position);

	float getVolume(string keyName);
	void setVolume(string keyName, float volume);
	void setAllVolume(float volume);

};



#if 0 // 1�� �ۼ�


/* C��Ÿ�� */
enum SOUNDKIND
{
	SOUND_BGM = 0,
	SOUND_EFFECT_1,
	SOUND_EFFECT_2,
	SOUND_END
};

// ������ ä�� ����(����)
#define EXTRA_SOUND_CHANNEL 5

// �� ���� ����
#define TOTAL_SOUND_CHANNEL SOUND_END + EXTRA_SOUND_CHANNEL


// C# ��Ÿ��
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

	// ���� ���� �¾�
	void setUp(char* fileName, int soundKind,
		bool backGround, bool loop);

	// ���� �÷���
	void play(int soundKind, float volume);

};

#endif
