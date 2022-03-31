#include "Stdafx.h"
#include "STATE.h"


// ���, �̵�, �ǰ�, ���� ����
IdleState* IdleState::instance;
MoveState* MoveState::instance;
BeHitState* BeHitState::instance;
DeadState* DeadState::instance;



// ���
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();

	return instance;
}

void IdleState::stateInit(Player* player)
{
	cout << "IdleState::init" << endl;
	player->getIsStateCheck().reset(2);

	if (player->getPlayerWeapon() == WEAPONTYPE::SWORD)
	{
		player->setPlayerImg(IMG("p_idle_oneHand"));
	}
	else if (player->getPlayerWeapon() == WEAPONTYPE::AX)
	{
		player->setPlayerImg(IMG("p_idle_twoHand"));
	}

}

void IdleState::stateUpdate(Player* player)
{
	cout << "IdleState::update" << endl;

	// ������ �ƴҶ� �̵�
	if ( !(player->getIsStateCheck().test(2)) &&
		(KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		cout << "get moveInstance" << endl;
		SetPlayerState(player, MoveState::getInstance());
	}

	// ����
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get AttackInstance!" << endl;

		if ((player->getPlayerWeapon() == WEAPONTYPE::SWORD) ||
			(player->getPlayerWeapon() == WEAPONTYPE::AX))
		{
			SetPlayerState(player, OneHandWeaponCombo::getInstance());
		}
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}

	// ��ų
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// â�� �����ϰ� ������ ��ų��
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			SetPlayerState(player, SpearStrike::getInstance());
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	// �ǰ�
	if (player->getIsStateCheck().test(3))
	{ 
		cout << "�ǰݴ���!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	// ����
	if (player->getStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}

}

void IdleState::stateRelease()
{
	cout << "IdleState::release" << endl;
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

// �̵�
MoveState* MoveState::getInstance()
{
	if (instance == nullptr) instance = new MoveState();
	return instance;
}

void MoveState::stateInit(Player * player)
{
	cout << "MoveState::init" << endl;
	player->getIsStateCheck().set(1);

	player->setPlayerImg(IMG("p_move"));


	// Y�����Ӹ� ����
	player->setPlayerFrameY(static_cast<int>(player->getPlayerDirection()));
	
}

void MoveState::stateUpdate(Player * player)
{
	cout << "MoveState::update" << endl;

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
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) )
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
	if (KEYMANAGER->isStayKeyDown(VK_UP) )
	{
		player->setPlayerPosY(player->getPlayerPosY() - player->getPlayerSpeed());
		player->setPlayerDirection(PLAYERDIRECTION::UP);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
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
			player->getIsStateCheck().reset(0);
			player->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}

	//����Ű �Է� ����
	if (KEYOKU(VK_LEFT) || KEYOKU(VK_UP) || KEYOKU(VK_DOWN))
	{
		player->getIsStateCheck().reset(1);
		SetPlayerState(player, IdleState::getInstance());
	}
	if (KEYOKU(VK_RIGHT))
	{
		player->getIsStateCheck().reset(1);
		SetPlayerState(player, IdleState::getInstance());
	}

	// ����
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get AttackInstance!" << endl;

		if ((player->getPlayerWeapon() == WEAPONTYPE::SWORD) ||
			(player->getPlayerWeapon() == WEAPONTYPE::AX))
		{
			SetPlayerState(player, OneHandWeaponCombo::getInstance());
		}
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}

	// ��ų
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// â�� �����ϰ� ������ ��ų��
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			SetPlayerState(player, SpearStrike::getInstance());
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		cout << "get 3rd Skill Instance" << endl;
	}

	// �ǰ�
	if (player->getIsStateCheck().test(3))
	{
		cout << "�ǰݴ���!" << endl;
		SetPlayerState(player, BeHitState::getInstance());
	}

	// ����
	if (player->getStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}




}

void MoveState::stateRelease()
{
	cout << "MoveState::release" << endl;

	if (instance)
	{
		delete instance;
		instance = 0;
	}
}



// �ǰ�
BeHitState* BeHitState::getInstance()
{
	if (instance == nullptr) instance = new BeHitState();
	return instance;
}

void BeHitState::stateInit(Player * player)
{
	cout << "BeHitState::Init" << endl;
	player->getIsStateCheck().set(3);

	player->setPlayerImg(IMG("p_hit"));

	// Y�����Ӹ� ����
	if (player->getIsStateCheck().test(0))
	{
		player->setPlayerFrameY(0);
	}
	else player->setPlayerFrameY(1);
}

void BeHitState::stateUpdate(Player * player)
{
	cout << "�¾��� �ФФФФФ�" << endl;
	// ������ �����ð� ����

	// ���ʿ��� ������ ���������� �ణ �̵� 
	if (player->getIsStateCheck().test(0))
	{
		player->setPlayerPosX(player->getPlayerPosX() + (player->getPlayerSpeed()*0.5));
	}
	else player->setPlayerPosX(player->getPlayerPosX() - (player->getPlayerSpeed()*0.5));
}

void BeHitState::stateRelease()
{
	cout << "BeHitState::release" << endl;

	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

DeadState * DeadState::getInstance()
{
	if (instance == nullptr) instance = new DeadState();
	return instance;
}

void DeadState::stateInit(Player * player)
{

	cout << "DeadState::init" << endl;
	player->getIsStateCheck().reset(4);

	player->setPlayerImg(IMG("p_down"));

	// Y�����Ӹ� ����
	if (player->getIsStateCheck().test(0))
	{
		player->setPlayerFrameY(0);
	}
	else player->setPlayerFrameY(1);

}

void DeadState::stateUpdate(Player * player)
{
	// ������ �̹��� ������ �� Ÿ��Ʋ�� �̵�
	cout << "����;;;;;;;;;;;;;;;;;;;;;;;" << endl; 

}

void DeadState::stateRelease()
{
	cout << "DeadState::release" << endl;

	if (instance)
	{
		delete instance;
		instance = 0;
	}
}



