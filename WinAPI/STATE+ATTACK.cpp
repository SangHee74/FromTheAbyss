#include "Stdafx.h"
#include "STATE.h"


// ���⺰ �޺�, ��ų���� 2�� 
OneHandWeaponCombo* OneHandWeaponCombo::instance;
TwoHandWeaponCombo* TwoHandWeaponCombo::instance;
SoulCapture* SoulCapture::instance;
SpearStrike* SpearStrike::instance;


// ����
OneHandWeaponCombo* OneHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new OneHandWeaponCombo();
	return instance;
}

void OneHandWeaponCombo::stateInit(Player* player)
{
	// ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_oneHandCombo"));

	// Y�����Ӹ� ����
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺�
	timeCount++;

	cout << "�Ѽչ��� 1�� ����" << endl;
	if ( KEYMANAGER->isStayKeyDown('X'))
	{
		// 2�� ���� ����

	}
	//������ ���� or ī��Ʈ ������ ��������� ��ȯ)
	if ( KEYOKU('X') && timeCount >= 30)
	{
		SetPlayerState(player, IdleState::getInstance());
	}

}

void OneHandWeaponCombo::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}


TwoHandWeaponCombo * TwoHandWeaponCombo::getInstance()
{
	if (instance == nullptr) instance = new TwoHandWeaponCombo();
	return instance;
}

void TwoHandWeaponCombo::stateInit(Player * player)
{
	// ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_twoHandCombo"));

	// Y�����Ӹ� ����
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));
}

void TwoHandWeaponCombo::stateUpdate(Player * player)
{
	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺�
	timeCount++;

	cout << "�μչ��� 1�� ����" << endl;
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		// 2�� ���� ����

	}
	//������ ���� or ī��Ʈ ������ ��������� ��ȯ)
	if (KEYOKU('X') && timeCount >= 30)
	{
		SetPlayerState(player, IdleState::getInstance());
	}
}

void TwoHandWeaponCombo::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}


// ��ų =========================================================
SoulCapture* SoulCapture::getInstance()
{
	if (instance == nullptr) instance = new SoulCapture();
	return instance;
}

void SoulCapture::stateInit(Player * player)
{
	// ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_skill_soulCapture"));

	// Y�����Ӹ� ����
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));
}

void SoulCapture::stateUpdate(Player * player)
{
	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺�
	timeCount++;

	cout << "��ų : �ҿ�ĸ�� ���� " << endl;
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// XŰ ��Ÿ�� �ҿ�ĸ�� ������ �� ����
	}

	// �ҿ� ĸ�� �����(�����ʿ�)
	if (KEYOKU('X') && timeCount >= 30)
	{
		SetPlayerState(player, IdleState::getInstance());
	}
}

void SoulCapture::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}



SpearStrike * SpearStrike::getInstance()
{
	if (instance == nullptr) instance = new SpearStrike();
	return instance;
}

void SpearStrike::stateInit(Player * player)
{
	// �����ʿ�~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ��Ʈ�� �ʱ�ȭ + �������� ��ȯ
	player->getIsStateCheck().reset(0);
	player->getIsStateCheck().set(2);

	player->setPlayerImg(IMG("p_skill_soulCapture"));

	// Y�����Ӹ� ����
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));
}

void SpearStrike::stateUpdate(Player * player)
{
}

void SpearStrike::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

