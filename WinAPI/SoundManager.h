#pragma once
#include "SingletonBase.h"

/*
FMOD
-Sound Engine ���̺귯��
�� Unreal Engine�� Unity Engine���� ���̼��� ������� �⺻�����.
�� �̿��� ��κ��� �÷��������� ����ϱ� ���� �����غ� ����� ��. 
*/

/*
const, constexpr
�� C++11 (��� C++)
�� �ش� ��ü�� �Լ��� ���ϰ��� "������" Ÿ�ӿ� �� �� �ִ�.(��)
�� C++ 17���ʹ� ���ٽĿ��� ������ �ȴ�. 

�� ������ Ÿ�ӿ� ���� �����ǹǷ� �Լ� ȣ�� �� ���ø� ���ڷ� �Ѱ� �� �� �����ϴ�.

const�� constexpr�� �������� �ʱ�ȭ ���ο� ���� �߰� �ñ�.
�� const ������ �ʱ�ȭ�� ��Ÿ�ӱ��� ���� ��ų �� ������ (C++���� ����Ʈ�� ������ ������ �����ϴ�. )
�� constecpr ������ �ݵ�� ������ Ÿ�ӿ� �ʱ�ȭ�� �Ǿ� �־�� �Ѵ�.(C++������ ������ ���ϴ� ��¥ ���..)

*/

/* C++ ��Ÿ�� */
constexpr auto soundBuffer = 10;
constexpr auto extraSoundCgannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundCgannel;

using namespace FMOD;

class SoundManager :public SingletonBase <SoundManager>
{
private:
	// enum�� ��ü�Ͽ� map ���.
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
