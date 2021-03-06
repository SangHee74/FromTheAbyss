#include "Stdafx.h"
#include "StateBase.h"
#include "StateAttack.h"
#include "Player.h"

// 대기, 이동, 피격, 죽음 상태
IdleState* IdleState::instance;
MoveState* MoveState::instance;
DefState* DefState::instance;
DeadState* DeadState::instance;

// 대기
IdleState* IdleState::getInstance()
{
	if (instance == nullptr) instance = new IdleState();
	return instance;
}

void IdleState::stateInit(Player* player)
{
	// 이미지 이닛, 프레임 초기화, 에니메이션 초기화 등
	// 대기 : 이동, 공격, 피격 초기화
	player->getIsStateCheck().reset(1);
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);

	player->getState() =PLAYERSTATE::IDLE;

	// 플레이어 무기타입(image), 방향(frameX), 무기번호(frameY)+ 무기좌표 세팅
	player->weaponinStageSetting();

	// 공격범위 초기화
	player->getPlayerCollisionRc().atkEffectImg = IMG("weapon_none");
	player->getPlayerCollisionRc().atkEffFrameX = 0;
	player->getPlayerCollisionRc().atkEffFrameY = 0;
	player->getPlayerCollisionRc().atkWidth = 0;
	player->getPlayerCollisionRc().atkHeight = 0;

}

void IdleState::stateUpdate(Player* player)
{
#pragma region player

	// 이동
	if (!(player->getIsStateCheck().test(2)) &&
		( KEYMANAGER->isStayKeyDown(VK_LEFT)) || (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		|| (KEYMANAGER->isStayKeyDown(VK_UP)) || (KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		SetPlayerState(player, MoveState::getInstance());
	}

	// 공격
	if (KEYMANAGER->isOnceKeyDown('X'))
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


	// 피격
	if (player->getIsStateCheck().test(3))
	{
		SetPlayerState(player, DefState::getInstance());
	}

	// 죽음
	if (player->getPlayerStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}


	
#pragma endregion

#pragma region weapon

	// 무기변환 테스트
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SWORD;
		player->weaponinStageSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::AX;
		player->weaponinStageSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		player->getPlayerWeapon().type = WEAPONTYPE::SPEAR;
		player->weaponinStageSetting();

	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
	}

#pragma endregion

	player->getPlayer().frameX = 0;


}

void IdleState::stateRelease()
{

}

void IdleState::stateRender(Player* player)
{
}

// 이동
MoveState* MoveState::getInstance()
{
	if (instance == nullptr) instance = new MoveState();
	return instance;
}

void MoveState::stateInit(Player * player)
{
	// 이동 : 공격, 피격 초기화
	player->getIsStateCheck().reset(2);
	player->getIsStateCheck().reset(3);
	player->getIsStateCheck().set(1);

	player->getState() = PLAYERSTATE::MOVE;

	timeCount = 0;
	frameIndexX = 0;

}

void MoveState::stateUpdate(Player* player)
{
	timeCount++;
	player->getPlayer().image = IMG("p_move");
	
	// 상
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->getPlayer().movePosY -= player->getPlayer().speed;
		player->getDirection() = PLAYERDIRECTION::UP;

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->getDirection() = PLAYERDIRECTION::LEFTUP;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->getDirection() = PLAYERDIRECTION::LEFTUP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->getDirection() = PLAYERDIRECTION::RIGHTUP;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->getDirection() = PLAYERDIRECTION::RIGHTUP;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		SetPlayerState(player, IdleState::getInstance());
	}
	// 하
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->getPlayer().movePosY += player->getPlayer().speed;
		player->getDirection() = PLAYERDIRECTION::DOWN;

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->getDirection() = PLAYERDIRECTION::LEFTDOWN;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->getDirection() = PLAYERDIRECTION::RIGHTDOWN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			player->getIsStateCheck().set(0);
			player->getDirection() = PLAYERDIRECTION::LEFTDOWN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			player->getIsStateCheck().reset(0);
			player->getDirection() = PLAYERDIRECTION::RIGHTDOWN;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		SetPlayerState(player, IdleState::getInstance());
	}
	// 좌
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->getIsStateCheck().set(0);
		player->getPlayer().movePosX -= player->getPlayer().speed;
		player->getDirection() = PLAYERDIRECTION::LEFT;

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->getDirection() = PLAYERDIRECTION::LEFTUP;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			player->getDirection() = PLAYERDIRECTION::LEFTUP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->getDirection() = PLAYERDIRECTION::LEFTDOWN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			player->getDirection() = PLAYERDIRECTION::LEFTDOWN;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		SetPlayerState(player, IdleState::getInstance());
	}
	// 우
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->getIsStateCheck().reset(0);
		player->getPlayer().movePosX += player->getPlayer().speed;
		player->getDirection() = PLAYERDIRECTION::RIGHT;

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player->getDirection() = PLAYERDIRECTION::RIGHTUP;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			player->getDirection() = PLAYERDIRECTION::RIGHTUP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player->getDirection() = PLAYERDIRECTION::RIGHTDOWN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			player->getDirection() = PLAYERDIRECTION::RIGHTDOWN;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		SetPlayerState(player, IdleState::getInstance());
	}

	// 키입력 후 픽셀충돌
	pixelCollision(player);

	// 최종 캐릭터 좌표를 받는 무기 좌표 
	player->getPlayerWeapon().movePosX = player->getPlayer().movePosX;
	player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;




	// 공격
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

	// 피격
	if (player->getIsStateCheck().test(3))
	{
		cout << "피격당함!" << endl;
		SetPlayerState(player, DefState::getInstance());
	}

	// 죽음
	if (player->getPlayerStatus().curHp <= 0)
	{
		SetPlayerState(player, DeadState::getInstance());
	}


	if (timeCount % 10 == 0)
	{
		// 플레이어 왼쪽
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
		

		// 초기화 : 1초
		if (timeCount==60) timeCount = 0;
	}

	player->getPlayer().frameX = frameIndexX;
	player->getPlayerWeapon().image = IMG("weapon_none");
}

void MoveState::stateRelease()
{

}

void MoveState::stateRender(Player* player)
{
}


void MoveState::pixelCollision(Player* player)
{
	//탐지
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

	case PLAYERDIRECTION::RIGHTUP: // 수정 필요
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

// 픽셀체크할 맵 이미지, 컬러체크할 X, Y 
bool MoveState::pixelColorCheck(int getPixelX, int getPixelY)
{
	DATAMANAGER->getMapData().pixelMap->getMemDC();

	COLORREF color = GetPixel(DATAMANAGER->getMapData().pixelMap->getMemDC(), getPixelX, getPixelY);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);


	if (!(r == 255 && g == 0 && b == 255))
	{
		// 마젠타가 아니면, 픽셀 충돌임.
		return true;
	}
	else return false;

}


// 피격
DefState* DefState::getInstance()
{
	if (instance == nullptr) instance = new DefState();
	return instance;
}

void DefState::stateInit(Player* player)
{
	player->getIsStateCheck().set(3);
	player->getState() =PLAYERSTATE::DEF;

	// 공격범위 초기화
	player->getPlayerCollisionRc().atkEffectImg = IMG("weapon_none");
	player->getPlayerCollisionRc().atkEffFrameX = 0;
	player->getPlayerCollisionRc().atkEffFrameY = 0;

//	player->playerCollisionAttDataSetting(player->getPlayerCollisionRc().atkEffFrameX);


}

void DefState::stateUpdate(Player* player)
{
	timeCount++;
	player->getPlayer().image = IMG("p_def");
	player->getPlayerWeapon().image = IMG("weapon_none");

	// 왼쪽에서 맞으면 오른쪽으로 약간 이동 
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

	// 이동 후 픽셀충돌 필요
	//pixelCollision(player);

	// 최종 캐릭터 좌표를 받는 무기 좌표 
	player->getPlayerWeapon().movePosX = player->getPlayer().movePosX;
	player->getPlayerWeapon().movePosY = player->getPlayer().movePosY;

	// 1초 간 피격모션
	if (timeCount % 60 == 0)
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
	// 공격범위 초기화
	player->getPlayerCollisionRc().atkEffectImg = IMG("weapon_none");
	player->getPlayerCollisionRc().atkEffFrameX = 0;
	player->getPlayerCollisionRc().atkEffFrameY = 0;

	//player->playerCollisionAttDataSetting(player->getPlayerCollisionRc().atkEffFrameX);

}

void DeadState::stateUpdate(Player* player)
{
	// 쓰러진 이미지 보여준 후 타이틀로 이동
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


	// 3초 
	if (timeCount % 180 == 0)
	{
		player->getIsStateCheck().reset(4);
		player->getState() =PLAYERSTATE::DEAD;
	}
}

void DeadState::stateRelease()
{
	cout << "DeadState::release" << endl;


}

void DeadState::stateRender(Player* player)
{
}

#if 0

#endif
