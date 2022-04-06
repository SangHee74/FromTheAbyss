#include "Stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager() :_system(nullptr),
							  _sound(nullptr),
							  _channel(nullptr)
{
}

HRESULT SoundManager::init(void)
{
	// 사운드 시스템 생성
	System_Create(&_system);

	// 시스템 초기화
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);

	// 채널 수 만큼 메모리 버퍼 및 사운드를 생성
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	// 메모리 밀기
	memset(_sound, 0, sizeof(Sound*)  * (totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*)  * (totalSoundChannel));


	return S_OK;
}

void SoundManager::release(void)
{
	//destroy
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < totalSoundChannel; i++)
		{
			if (_channel != nullptr)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != nullptr)
			{
				if (_sound != nullptr ) _sound[i]->release();
			}

		}

	}

	SAFE_DELETE(_channel);
	SAFE_DELETE(_sound);

	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::update(void)
{
	// 사운드 시스템 업데이트
	// ㄴ 볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼는 등 다양한 작업을 자동으로 실행.
	_system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool backGround, bool loop)
{

	if (loop)
	{
		if (backGround)
		{
			// 파일이름, 사운드를 열기 위한 옵션(일반적인 루프 재생) , 
			// 피드백(개발자에게 사운드가 재생되는 동안 정보를 제공할지 유무(0,NULL : 안받음), 변수의 주소
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			// 효과음(동시재생을 위해 creatSound 사용)
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);

		}
	}
	else
	{
		// FMOD_DEFAULT : 한번 재생
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);

	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void SoundManager::play(string keyName, float volume)
{

	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	// 사운드를 5개  
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// 사운드 플레이
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]); // 두번째 사운드 부터는 못찾는 문제 발생할 것. 
			//_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);// 이터의 세컨드를 찾고 넘기는 것이 답. 포인터 유무는 고민할 것 .


			// 볼륨 설정
			_channel[count]->setVolume(volume);
			break;
		}
	}


}

void SoundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}


	return isPlay;
}


bool SoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}

	return isPause;
}



unsigned int SoundManager::getLength(string keyName)
{
	Sound* currentSound = nullptr;
	unsigned int length = 0;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getCurrentSound(&currentSound);
			currentSound->getLength(&length, FMOD_TIMEUNIT_MS);
			break;
		}
	}
	return length;
}

unsigned int SoundManager::getPosition(string keyName)
{
	unsigned int position = 0;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&position, FMOD_TIMEUNIT_MS);
			break;
		}
	}
	return position;
}

void SoundManager::setPosition(string keyName, unsigned int position)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(position, FMOD_TIMEUNIT_MS);
			break;
		}
	}
}

float SoundManager::getVolume(string keyName)
{
	float volume;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getVolume(&volume);
			break;
		}
	}
	return volume;
}

void SoundManager::setVolume(string keyName, float volume)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}
}


void SoundManager::setAllVolume(float volume)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		_channel[count]->setVolume(volume);
	}
}
