#include "Stdafx.h"
#include "StateAttack.h"
#include "Player.h"


// ���⺰ �޺�, ��ų���� 2�� 
//OneHandWeaponCombo* OneHandWeaponCombo::instance;
//TwoHandWeaponCombo* TwoHandWeaponCombo::instance;
//SoulCapture* SoulCapture::instance;
//SpearStrike* SpearStrike::instance;

#if 0
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
	combo.reset(0);


	player->setPlayerImg(IMG("p_oneHandCombo"));


	timeCount = 0;

	// ���⺰ ���� ������ ����(comboOne 1,2 /  comboTwo 1,2 / comboThree 1,2 ) : �� 6��
	// ����ġ�� �÷��̾� ���� �޾Ƽ� ����.

}

void OneHandWeaponCombo::stateUpdate(Player* player)
{
	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺�
	timeCount++;
	if (combo.none())
	{
		combo.set(0);
		comboOne(player);
	}

	// ��
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setPlayerPosX(player->getPlayerPosX() - player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::LEFT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setPlayerPosX(player->getPlayerPosX() + player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::RIGHT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->setPlayerPosY(player->getPlayerPosY() - player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::UP);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
	}
	// �Ʒ�
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->setPlayerPosY(player->getPlayerPosY() + player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::DOWN);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}

	if (combo.test(0) && KEYMANAGER->isStayKeyDown('X') && !player->getIsStateCheck().test(2))
	{
		// 2�� ���� ����
		combo.set(1);
		comboTwo(player);
		combo.reset(0);
	}
	else if (combo.test(1) && KEYMANAGER->isStayKeyDown('X') && !player->getIsStateCheck().test(2))
	{
		// 3�� ���� ����
		combo.set(2);
		comboThree(player);
		combo.reset(1);
	}
	//������ ���� or ī��Ʈ ������ ��������� ��ȯ)
	if (combo.test(2) && (timeCount >= 30 && !player->getIsStateCheck().test(2)))
	{
		SetPlayerState(player, IdleState::getInstance());
		combo.reset();
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

void OneHandWeaponCombo::comboOne(Player* player)
{
	player->getIsStateCheck().set(2);
	cout << "�Ѽչ��� 1�� ���� �Լ�" << endl;
	if (combo.test(0)) cout << "1�ܰ��� ��Ʈ�� Ŵ" << endl;

	player->setPlayerFrameX(player->getPlayerFrameX() + 1);
	if (player->getPlayerFrameX() == 1 && timeCount % 30 == 0)
	{
		//������ó������ �پƾƾ� ������ ����ó�� �� 
		player->getIsStateCheck().reset(2);
	}

}

void OneHandWeaponCombo::comboTwo(Player* player)
{
	player->getIsStateCheck().set(2);

	cout << "�Ѽչ��� 2�� ���� �Լ�" << endl;

	player->setPlayerFrameX(player->getPlayerFrameX() + 1);
	if (player->getPlayerFrameX() == 3 && timeCount % 30 == 0)
	{
		//������ó������ �پƾƾ� ������ ����ó�� �� 
		player->getIsStateCheck().reset(2);
	}

}

void OneHandWeaponCombo::comboThree(Player* player)
{
	player->getIsStateCheck().set(2);

	cout << "�Ѽչ��� 3�� ���� �Լ�" << endl;

	player->setPlayerFrameX(player->getPlayerFrameX() + 1);
	if (player->getPlayerFrameX() == 1 && timeCount % 30 == 0)
	{
		//������ó������ �پƾƾ� ������ ����ó�� �� 
		player->getIsStateCheck().reset(2);
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
#endif 