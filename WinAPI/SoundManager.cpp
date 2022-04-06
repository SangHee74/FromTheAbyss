#include "Stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager() :_system(nullptr),
							  _sound(nullptr),
							  _channel(nullptr)
{
}

HRESULT SoundManager::init(void)
{
	// ���� �ý��� ����
	System_Create(&_system);

	// �ý��� �ʱ�ȭ
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);

	// ä�� �� ��ŭ �޸� ���� �� ���带 ����
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	// �޸� �б�
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
	// ���� �ý��� ������Ʈ
	// �� ������ �ٲ�ų� ����� ���� ���带 ä�ο��� ���� �� �پ��� �۾��� �ڵ����� ����.
	_system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool backGround, bool loop)
{

	if (loop)
	{
		if (backGround)
		{
			// �����̸�, ���带 ���� ���� �ɼ�(�Ϲ����� ���� ���) , 
			// �ǵ��(�����ڿ��� ���尡 ����Ǵ� ���� ������ �������� ����(0,NULL : �ȹ���), ������ �ּ�
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			// ȿ����(��������� ���� creatSound ���)
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);

		}
	}
	else
	{
		// FMOD_DEFAULT : �ѹ� ���
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);

	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void SoundManager::play(string keyName, float volume)
{

	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	// ���带 5��  
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]); // �ι�° ���� ���ʹ� ��ã�� ���� �߻��� ��. 
			//_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);// ������ �����带 ã�� �ѱ�� ���� ��. ������ ������ ����� �� .


			// ���� ����
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
