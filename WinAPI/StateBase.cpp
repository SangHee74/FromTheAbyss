#include "Stdafx.h"
#include "StateBase.h"
#include "Player.h"


// ���, �̵�, �ǰ�, ���� ����
IdleState* IdleState::instance;
MoveState* MoveState::instance;
//BeHitState* BeHitState::instance;
//DeadState* DeadState::instance;


// ���
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();

	return instance;
}

void IdleState::stateInit(Player* player)
{
	cout << "IdleState::init" << endl;

	// �̹��� �̴�, ������ �ʱ�ȭ, ���ϸ��̼� �ʱ�ȭ ��
	// ��� : �̵�, ����, �ǰ� �ʱ�ȭ
	player->getIsStateCheck().reset(1);
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);

	player->setState(PLAYERSTATE::IDLE);

}

void IdleState::stateUpdate(Player* player)
{
	// timeCount 60 = 1��
	timeCount++;
	if (timeCount % 60 == 0); cout << "IdleState::update" << endl;

	// ������ �ƴҶ� �̵�
	if (!(player->getIsStateCheck().test(2)) &&
		( KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		cout << "get moveInstance" << endl;
		SetPlayerState(player, MoveState::getInstance());
	}

	/*
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
			//SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}

	// ��ų
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// â�� �����ϰ� ������ ��ų��
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
			//SetPlayerState(player, SpearStrike::getInstance());
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
	*/

	
	PLAYERDIRECTION _tempDirection;
	_tempDirection = player->getDirection();

	// ����� ���� ��ǥ ������Ʈ 
	switch (_tempDirection)
	{
	case PLAYERDIRECTION::UP:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::DOWN:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::LEFT:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::RIGHT:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::LEFTUP:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::RIGHTUP:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::LEFTDOWN:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	case PLAYERDIRECTION::RIGHTDOWN:
		player->getPlayerWeapon().drawPosX = player->getPlayerWeapon().movePosX - 23;
		player->getPlayerWeapon().drawPosY = player->getPlayerWeapon().movePosY - 27;
		break;
	}
	
	// ���⺯ȯ �׽�Ʈ
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SWORD;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::AX;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SPEAR;
	}

	// �̹��� ���Ƴ���
	if (player->getPlayerWeapon().type == WEAPONTYPE::SWORD) player->getPlayer().image = IMG("p_idle_oneHand");
	else if (player->getPlayerWeapon().type == WEAPONTYPE::AX) player->getPlayer().image = IMG("p_idle_oneHand");
	else if (player->getPlayerWeapon().type == WEAPONTYPE::SPEAR) player->getPlayer().image = IMG("p_idle_twoHand");
	player->getPlayer().image->setFrameX(0); // ���� �����۳ѹ� ��������

}

void IdleState::stateRelease()
{
	cout << "IdleState::release" << endl;
	//if (instance )
	//{
	//	delete instance;
	//	instance = 0;	
	//}
}

void IdleState::stateRender(Player* player)
{
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

	// �̵� : ����, �ǰ� �ʱ�ȭ

	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);
	player->getIsStateCheck().set(1);

	player->setState(PLAYERSTATE::MOVE);

}

// !!!!!!!!!!!!!!!! ���� �����̵� ������ ������Ʈ ����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void MoveState::stateUpdate(Player * player)
{
	timeCount++;
	if (timeCount % 60 == 0); cout << "MoveState::update" << endl;

	
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->getPlayer().movePosY -= player->getPlayer().speed;
		player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;
		
		player->setDirection(PLAYERDIRECTION::UP);

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->setDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->setDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->setDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->setDirection(PLAYERDIRECTION::RIGHTUP);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		cout << "get idleInstance" << endl;
		SetPlayerState(player, IdleState::getInstance());
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->getPlayer().movePosY += player->getPlayer().speed;
		player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;
		player->setDirection(PLAYERDIRECTION::DOWN);


		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->setDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->setDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->setDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->setDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		cout << "get idleInstance" << endl;
		SetPlayerState(player, IdleState::getInstance());
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->getIsStateCheck().set(0);
		player->getPlayer().movePosX -= player->getPlayer().speed;
		player->getPlayerWeapon().movePosX = player->getPlayer().movePosX;

		player->setDirection(PLAYERDIRECTION::LEFT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->setDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			player->setDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->setDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			player->setDirection(PLAYERDIRECTION::LEFTDOWN);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		cout << "get idleInstance" << endl;
		SetPlayerState(player, IdleState::getInstance());
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->getIsStateCheck().reset(0);
		player->getPlayer().movePosX += player->getPlayer().speed;
		player->getPlayerWeapon().movePosX = player->getPlayer().movePosX;
		player->setDirection(PLAYERDIRECTION::RIGHT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->setDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			player->setDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->setDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			player->setDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		cout << "get idleInstance" << endl;
		SetPlayerState(player, IdleState::getInstance());
	}


	/*
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
		//	SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}

	// ��ų
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//SetPlayerState(player, SoulCapture::getInstance());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		// â�� �����ϰ� ������ ��ų��
		if (player->getPlayerWeapon() == WEAPONTYPE::SPEAR)
		{
		//	SetPlayerState(player, SpearStrike::getInstance());
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

	*/

	if (timeCount % 30 == 0)
	{
		// �÷��̾� ����
		if (player->getIsStateCheck().test(0))
		{
			player->getPlayer().frameX += 1;
			if ( player->getPlayer().frameX >= 3)
			{
				player->getPlayer().frameX = 0;
			}
		}
		else
		{
			player->getPlayer().frameX -= 1;
			if (player->getPlayer().frameX < 0)
			{
				player->getPlayer().frameX = 3;
			}
		}
	}


}

void MoveState::stateRelease()
{
	cout << "MoveState::release" << endl;

	//if (instance)
	//{
	//	delete instance;
	//	instance = 0;
	//}
}

void MoveState::stateRender(Player* player)
{
}


#if 0
// �ǰ�
BeHitState* BeHitState::getInstance()
{
	if (instance == nullptr) instance = new BeHitState();
	return instance;
}

void BeHitState::stateInit(Player * player)
{
	if (timeCount % 180 == 0) cout << "BeHitState::Init" << endl;
	player->getIsStateCheck().set(3);


}

void BeHitState::stateUpdate(Player * player)
{
	timeCount++;
	if (timeCount % 120 == 0) cout << "�¾��� �ФФФФФ�" << endl;
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



#endif
