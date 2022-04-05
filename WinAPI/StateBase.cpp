#include "Stdafx.h"
#include "StateBase.h"
#include "StateAttack.h"
#include "Player.h"

// ���, �̵�, �ǰ�, ���� ����
IdleState* IdleState::instance;
MoveState* MoveState::instance;
HitState* HitState::instance;
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
		cout << "�ǰݴ���!" << endl;
		SetPlayerState(player, HitState::getInstance());
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
}

void MoveState::stateUpdate(Player* player)
{
	timeCount++;
	player->getPlayer().image = IMG("p_move");
	
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
		SetPlayerState(player, IdleState::getInstance());
	}
	// ��
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->getPlayer().movePosY += player->getPlayer().speed;
		player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;
		player->setDirection(PLAYERDIRECTION::DOWN);

		//for (int i = player->getPlayerPixel().probeDown - 20; i < player->getPlayerPixel().probeDown + 20; i++)
		//{
		//	COLORREF color = GetPixel(player->getMapImage()->getMemDC(), player->getPlayer().movePosX, i);
		//	int r = GetRValue(color);
		//	int g = GetGValue(color);
		//	int b = GetBValue(color);
		//
		//	if (!(r == 255 && g == 0 && b == 255))
		//	{
		//		player->getPlayer().movePosY = i - player->getPlayer().image->getHeight() / 2;
		//		break;
		//	}
		//}



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
		SetPlayerState(player, IdleState::getInstance());
	}

	// �ȼ��浹
	pixelCollision(player);

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
		SetPlayerState(player, HitState::getInstance());
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
	player->getPlayerPixel().probeTop = player->getPlayer().movePosY - player->getPlayer().image->getHeight() / 2;
	player->getPlayerPixel().probeDown = player->getPlayer().movePosY + player->getPlayer().image->getHeight() / 2;
	player->getPlayerPixel().probeLeft = player->getPlayer().movePosX - player->getPlayer().image->getHeight() / 2;
	player->getPlayerPixel().probeRight = player->getPlayer().movePosX + player->getPlayer().image->getHeight() / 2;

	switch (player->getDirection())
	{
	case PLAYERDIRECTION::UP: cout << "�ȼ�UP " << endl;
		for (int i = player->getPlayerPixel().probeTop - 20; i < player->getPlayerPixel().probeTop + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), player->getPlayer().movePosX, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			// ����Ÿ�� �ƴϸ� 
			if (!(r == 255 && g == 0 && b == 255))
			{
				// posY = �Ʒ��� ����
				player->getPlayer().movePosY = i + player->getPlayer().image->getHeight() / 2;
				player->getPlayer().movePosY = i + player->getPlayer().image->getHeight() / 2;
				cout << "�ȼ��� : " << i + player->getPlayer().image->getHeight() / 2 << endl;
				break;
			}
		}
		break;

	case PLAYERDIRECTION::DOWN:cout << "�ȼ�down " << endl;
		for (int i = player->getPlayerPixel().probeDown - 20; i < player->getPlayerPixel().probeDown + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), player->getPlayer().movePosX, i);
			int r = GetRValue(color); 			
			int g = GetGValue(color); 			
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosY = i - player->getPlayer().image->getHeight() / 2;
				cout << "�ȼ��ٿ�" << i - player->getPlayer().image->getHeight() / 2 << endl;
				break;
			}
		}
		break;

	case PLAYERDIRECTION::LEFT:cout << "�ȼ�left " << endl;
		for (int i = player->getPlayerPixel().probeLeft - 20; i < player->getPlayerPixel().probeLeft + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), i, player->getPlayer().movePosY);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosX = i + player->getPlayer().image->getWidth() / 2;
				cout << "�ȼ����� : " <<  i + player->getPlayer().image->getWidth() / 2 << endl;

				break;
			}
		}
		break;

	case PLAYERDIRECTION::RIGHT:cout << "�ȼ�right " << endl;
		for (int i = player->getPlayerPixel().probeRight - 20; i < player->getPlayerPixel().probeRight + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), i, player->getPlayer().movePosY);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosX = i - player->getPlayer().image->getWidth() / 2;
				cout << "�ȼ������� : " <<  i - player->getPlayer().image->getWidth() / 2 << endl;

				break;
			}
		}
		break;

	case PLAYERDIRECTION::LEFTUP:
		for (int i = player->getPlayerPixel().probeLeft - 20; i < player->getPlayerPixel().probeLeft + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), i, player->getPlayer().movePosY);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosX = i + player->getPlayer().image->getWidth() / 2;
				break;
			}
		}
		for (int i = player->getPlayerPixel().probeTop - 20; i < player->getPlayerPixel().probeTop + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), player->getPlayer().movePosX, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			// ����Ÿ�� �ƴϸ� 
			if (!(r == 255 && g == 0 && b == 255))
			{
				// posY = �Ʒ��� ����
				player->getPlayer().movePosY = i + player->getPlayer().image->getHeight() / 2;
				break;
			}
		}
		break;

	case PLAYERDIRECTION::RIGHTUP:
		for (int i = player->getPlayerPixel().probeRight - 20; i < player->getPlayerPixel().probeRight + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), i, player->getPlayer().movePosY);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosX = i - player->getPlayer().image->getWidth() / 2;
				break;
			}
		}
		for (int i = player->getPlayerPixel().probeTop - 20; i < player->getPlayerPixel().probeTop + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), player->getPlayer().movePosX, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosY = i + player->getPlayer().image->getHeight() / 2;
				break;
			}
		}
		break;

	case PLAYERDIRECTION::LEFTDOWN:
		for (int i = player->getPlayerPixel().probeLeft - 20; i < player->getPlayerPixel().probeLeft + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), i, player->getPlayer().movePosY);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosX = i + player->getPlayer().image->getWidth() / 2;
				break;
			}
		}
		for (int i = player->getPlayerPixel().probeDown - 20; i < player->getPlayerPixel().probeDown + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), player->getPlayer().movePosX, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosY = i - player->getPlayer().image->getHeight() / 2;
				break;
			}
		}
		break;

	case PLAYERDIRECTION::RIGHTDOWN:
		for (int i = player->getPlayerPixel().probeRight - 20; i < player->getPlayerPixel().probeRight + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), i, player->getPlayer().movePosY);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosX = i - player->getPlayer().image->getWidth() / 2;
				break;
			}
		}
		for (int i = player->getPlayerPixel().probeDown - 20; i < player->getPlayerPixel().probeDown + 20; i++)
		{
			COLORREF color = GetPixel(player->getMapImage()->getMemDC(), player->getPlayer().movePosX, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				player->getPlayer().movePosY = i - player->getPlayer().image->getHeight() / 2;
				break;
			}
		}
		break;
	}

}


// �ǰ�
HitState* HitState::getInstance()
{
	if (instance == nullptr) instance = new HitState();
	return instance;
}

void HitState::stateInit(Player* player)
{
	player->getIsStateCheck().set(3);
	player->setState(PLAYERSTATE::HIT);


}

void HitState::stateUpdate(Player* player)
{
	timeCount++;
	player->getPlayer().image = IMG("p_hit");
	player->getPlayerWeapon().image = IMG("weapon_none");

	if (timeCount % 60 == 0) cout << "�¾��� �ФФФФФ�" << endl;
	// ������ �����ð� ����

	// ���ʿ��� ������ ���������� �ణ �̵� 
	if (player->getIsStateCheck().test(0))
	{
		
		player->getPlayer().movePosX -= (player->getPlayer().speed*0.5);
	}
	else if (!player->getIsStateCheck().test(0))
	{
		player->getPlayer().movePosX += (player->getPlayer().speed*0.5);
	}

	player->getPlayer().frameX = 0;
	
	// 2��
	if (timeCount % 120 == 0)
	{
		SetPlayerState(player, IdleState::getInstance());
	}


}

void HitState::stateRelease()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void HitState::stateRender(Player* player)
{
}

DeadState* DeadState::getInstance()
{
	if (instance == nullptr) instance = new DeadState();
	return instance;
}

void DeadState::stateInit(Player * player)
{

	player->setState(PLAYERSTATE::DEAD);
}

void DeadState::stateUpdate(Player* player)
{
	// ������ �̹��� ������ �� Ÿ��Ʋ�� �̵�
	timeCount++;
	player->getPlayer().image = IMG("p_down");
	player->getPlayerWeapon().image = IMG("weapon_none");

	player->getPlayer().frameX = 0;

	// 3�� 
	if (timeCount % 180 == 0)
	{
		player->getIsStateCheck().reset(4);
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
