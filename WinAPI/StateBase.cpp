#include "Stdafx.h"
#include "StateBase.h"
#include "StateAttack.h"
#include "Player.h"

// ���, �̵�, �ǰ�, ���� ����
IdleState* IdleState::instance;
MoveState* MoveState::instance;
DefState* DefState::instance;
DeadState* DeadState::instance;

// ���
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();
	return instance;
}

void IdleState::stateInit(Player* player)
{
	// �̹��� �̴�, ������ �ʱ�ȭ, ���ϸ��̼� �ʱ�ȭ ��
	// ��� : �̵�, ����, �ǰ� �ʱ�ȭ
	player->getIsStateCheck().reset(1);
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);

	player->setState(PLAYERSTATE::IDLE);

	// �÷��̾� ����Ÿ��(image), ����(frameX), �����ȣ(frameY)+ ������ǥ ����
	player->inStageWeaponSetting();

	// ���ݹ��� �ʱ�ȭ
	player->setPlayerCollisionAttRc(0, 0, 0, 0);
}

void IdleState::stateUpdate(Player* player)
{
#pragma region player

	// �̵�
	if (!(player->getIsStateCheck().test(2)) &&
		( KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		SetPlayerState(player, MoveState::getInstance());
	}

	// ����
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		if ((player->getPlayerWeapon().type == WEAPONTYPE::SWORD) ||
			(player->getPlayerWeapon().type == WEAPONTYPE::AX))
		{
			SetPlayerState(player, OneHandWeaponCombo::getInstance());
		}
		if (player->getPlayerWeapon().type == WEAPONTYPE::SPEAR)
		{
			SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}

	/*
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
	*/

	// �ǰ�
	if (player->getIsStateCheck().test(3))
	{
		SetPlayerState(player, DefState::getInstance());
	}

	// ����
	if (player->getPlayerStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}


	
#pragma endregion

#pragma region weapon

	// ���⺯ȯ �׽�Ʈ
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SWORD;
		player->inStageWeaponSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::AX;
		player->inStageWeaponSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SPEAR;
		player->inStageWeaponSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
	}

#pragma endregion

	player->getPlayer().frameX = 0;
}

void IdleState::stateRelease()
{
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
	// �̵� : ����, �ǰ� �ʱ�ȭ
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);
	player->getIsStateCheck().set(1);

	player->setState(PLAYERSTATE::MOVE);

	timeCount = 0;
	frameIndexX = 0;

	player->setPlayerCollisionAttRc(0, 0, 0, 0);

}

void MoveState::stateUpdate(Player* player)
{
	timeCount++;
	player->getPlayer().image = IMG("p_move");
	
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->getPlayer().movePosY -= player->getPlayer().speed;
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
		SetPlayerState(player, IdleState::getInstance());
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->getPlayer().movePosY += player->getPlayer().speed;
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
		SetPlayerState(player, IdleState::getInstance());
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->getIsStateCheck().set(0);
		player->getPlayer().movePosX -= player->getPlayer().speed;
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
		SetPlayerState(player, IdleState::getInstance());
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->getIsStateCheck().reset(0);
		player->getPlayer().movePosX += player->getPlayer().speed;
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
		SetPlayerState(player, IdleState::getInstance());
	}

	// Ű�Է� �� �ȼ��浹
	pixelCollision(player);

	// ���� ĳ���� ��ǥ�� �޴� ���� ��ǥ 
	player->getPlayerWeapon().movePosX = player->getPlayer().movePosX;
	player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;




	// ����
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		cout << "get AttackInstance!" << endl;

		if ((player->getPlayerWeapon().type == WEAPONTYPE::SWORD) ||
			(player->getPlayerWeapon().type == WEAPONTYPE::AX))
		{
			SetPlayerState(player, OneHandWeaponCombo::getInstance());
		}
		if (player->getPlayerWeapon().type == WEAPONTYPE::SPEAR)
		{
			SetPlayerState(player, TwoHandWeaponCombo::getInstance());
		}
	}
	/*
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

	*/

	// �ǰ�
	if (player->getIsStateCheck().test(3))
	{
		cout << "�ǰݴ���!" << endl;
		SetPlayerState(player, DefState::getInstance());
	}

	// ����
	if (player->getPlayerStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}


	if (timeCount % 10 == 0)
	{
		// �÷��̾� ����
		if (player->getIsStateCheck().test(0))
		{
			frameIndexX++;
			if (frameIndexX > 3) frameIndexX = 0;
		}
		else
		{
			frameIndexX--;
			if (frameIndexX < 0) frameIndexX = 3;
		}
		

		// �ʱ�ȭ : 1��
		if (timeCount==60) timeCount = 0;
	}

	player->getPlayer().frameX = frameIndexX;
	player->getPlayerWeapon().image = IMG("weapon_none");
}

void MoveState::stateRelease()
{
	//if (instance)
	//{
	//	delete instance;
	//	instance = 0;
	//}
}

void MoveState::stateRender(Player* player)
{
}


void MoveState::pixelCollision(Player* player)
{
	//Ž��
	player->getPlayerPixel().probeUp =	 (player->getPlayer().movePosY + player->getPlayer().image->getFrameHeight() / 2) -16;
	player->getPlayerPixel().probeDown = (player->getPlayer().movePosY + player->getPlayer().image->getFrameHeight() / 2) -8;
	player->getPlayerPixel().probeLeft = player->getPlayer().movePosX-20;
	player->getPlayerPixel().probeRight = player->getPlayer().movePosX+20;
	
	
	switch (player->getDirection())
	{
	case PLAYERDIRECTION::UP:
		if ( pixelColorCheck(player->getPlayer().movePosX, player->getPlayerPixel().probeUp))
		{
			player->getPlayer().movePosY += player->getPlayer().speed;
		}
		break;

	case PLAYERDIRECTION::DOWN:
		if (pixelColorCheck( player->getPlayer().movePosX, player->getPlayerPixel().probeDown))
		{
			player->getPlayer().movePosY -= player->getPlayer().speed;
		}
		break;

	case PLAYERDIRECTION::LEFT:
		if (pixelColorCheck( player->getPlayerPixel().probeLeft, player->getPlayerPixel().probeDown))
		{
			player->getPlayer().movePosX += player->getPlayer().speed;
		}
		break;

	case PLAYERDIRECTION::RIGHT:
		if (pixelColorCheck( player->getPlayerPixel().probeRight, player->getPlayerPixel().probeDown))
		{
			player->getPlayer().movePosX -= player->getPlayer().speed;
		}
		break;
		
	case PLAYERDIRECTION::LEFTUP:
		if (pixelColorCheck( player->getPlayerPixel().probeLeft, player->getPlayerPixel().probeUp))
		{
			player->getPlayer().movePosX += player->getPlayer().speed;
			player->getPlayer().movePosY += player->getPlayer().speed;
		}
		break;

	case PLAYERDIRECTION::RIGHTUP: // ���� �ʿ�
		if (pixelColorCheck( player->getPlayerPixel().probeRight, player->getPlayerPixel().probeUp))
		{
			player->getPlayer().movePosX -= player->getPlayer().speed;
			player->getPlayer().movePosY += player->getPlayer().speed;
		}

	case PLAYERDIRECTION::LEFTDOWN:
		if (pixelColorCheck( player->getPlayerPixel().probeLeft, player->getPlayerPixel().probeDown))
		{
			player->getPlayer().movePosX += player->getPlayer().speed;
			player->getPlayer().movePosY -= player->getPlayer().speed;
		}
		break;

	case PLAYERDIRECTION::RIGHTDOWN:
		if (pixelColorCheck( player->getPlayerPixel().probeRight, player->getPlayerPixel().probeDown))
		{
			player->getPlayer().movePosX -= player->getPlayer().speed;
			player->getPlayer().movePosY -= player->getPlayer().speed;
		}
		break;
	}
}

// �ȼ�üũ�� �� �̹���, �÷�üũ�� X, Y 
bool MoveState::pixelColorCheck(int getPixelX, int getPixelY)
{
	DATAMANAGER->getMapData().pixelMap->getMemDC();

	COLORREF color = GetPixel(DATAMANAGER->getMapData().pixelMap->getMemDC(), getPixelX, getPixelY);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);


	if (!(r == 255 && g == 0 && b == 255))
	{
		// ����Ÿ�� �ƴϸ�, �ȼ� �浹��.
		return true;
	}
	else return false;




}


// �ǰ�
DefState* DefState::getInstance()
{
	if (instance == nullptr) instance = new DefState();
	return instance;
}

void DefState::stateInit(Player* player)
{
	player->getIsStateCheck().set(3);
	player->setState(PLAYERSTATE::DEF);
	player->setPlayerCollisionAttRc(0, 0, 0, 0);

}

void DefState::stateUpdate(Player* player)
{
	timeCount++;
	player->getPlayer().image = IMG("p_def");
	player->getPlayerWeapon().image = IMG("weapon_none");

	// ���ʿ��� ������ ���������� �ణ �̵� 
	if (player->getIsStateCheck().test(0))
	{
		player->getPlayer().movePosX += (player->getPlayer().speed*0.1);
		player->getPlayer().frameY = 0;
	}
	else if (!player->getIsStateCheck().test(0))
	{
		player->getPlayer().movePosX -= (player->getPlayer().speed*0.1);
		player->getPlayer().frameY = 1;
	}


	player->getPlayer().frameX = 0;

	// �̵� �� �ȼ��浹 �ʿ�
	//pixelCollision(player);

	// ���� ĳ���� ��ǥ�� �޴� ���� ��ǥ 
	player->getPlayerWeapon().movePosX = player->getPlayer().movePosX;
	player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;

	// 0.5�� �� �ǰݸ��
	if (timeCount % 30 == 0)
	{
		SetPlayerState(player, IdleState::getInstance());
	}
	
}

void DefState::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void DefState::stateRender(Player* player)
{
}

DeadState* DeadState::getInstance()
{
	if (instance == nullptr) instance = new DeadState();
	return instance;
}

void DeadState::stateInit(Player * player)
{
	player->setPlayerCollisionAttRc(0, 0, 0, 0);

}

void DeadState::stateUpdate(Player* player)
{
	// ������ �̹��� ������ �� Ÿ��Ʋ�� �̵�
	timeCount++;
	player->getPlayer().image = IMG("p_down");
	player->getPlayerWeapon().image = IMG("weapon_none");


	if (player->getIsStateCheck().test(0))
	{
		player->getPlayer().frameY = 0;
	}
	else if (!player->getIsStateCheck().test(0))
	{
		player->getPlayer().frameY = 1;
	}
	player->getPlayer().frameX = 0;


	// 3�� 
	if (timeCount % 180 == 0)
	{
		player->getIsStateCheck().reset(4);
		player->setState(PLAYERSTATE::DEAD);
	}
}

void DeadState::stateRelease()
{
	cout << "DeadState::release" << endl;

	//if (instance)
	//{
	//	delete instance;
	//	instance = 0;
	//}
}

void DeadState::stateRender(Player* player)
{
}

#if 0

#endif
