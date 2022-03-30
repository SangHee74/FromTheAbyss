#include "Stdafx.h"
#include "STATE.h"
#include "Player.h"

#ifdef STATEPATTERN

STATE::~STATE()
{
}




void Idle::enterState()
{
	//상태에 들어오면 각 상태마다 초기화를 해줍니다 
	//각각의 상태에 따라 이미지 재생을 위한 index를 초기화
	//_p->setPlayerFrameX(0);

}

void Idle::updateState()
{
	count++;
	// 30카운트가 지나면 저장한 값은 다시 0으로 초기화 됩니다
	// 30카운트(0.5초)지나기 전 재입력하면 다음콤보 상태가 되게 해줬습니다


	// 대기 -> 방향키 누르면 움직임
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_p->setState(PLAYERSTATE::MOVE);
		_p->setPlayerDirection(PLAYERDIRECTION::LEFT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_p->setState(PLAYERSTATE::MOVE); 
		_p->setPlayerDirection(PLAYERDIRECTION::RIGHT);

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_p->setState(PLAYERSTATE::MOVE);
		_p->setPlayerDirection(PLAYERDIRECTION::UP);

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::LEFTUP);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::RIGHTUP);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_p->setState(PLAYERSTATE::MOVE);
		_p->setPlayerDirection(PLAYERDIRECTION::DOWN);

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::LEFTDOWN);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_p->setPlayerDirection(PLAYERDIRECTION::RIGHTDOWN);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('X')) // 일반 공격
	{
		_p->setState(PLAYERSTATE::ATT);
	}
}

void Idle::exitState()
{
	count = 0; // 상태를 탈출할때 대기모션용 카운트를 초기화하게 했습니다.
}













#else
IdleState* IdleState::instance;
MoveState* MoveState::instance;
AttackState* AttackState::instance;
BeHitState* BeHitState::instance;


// 대기
IdleState* IdleState::GetInstance()
{
	if (instance == nullptr) instance = new IdleState();
	return instance;
}

void IdleState::idle(Player* player)
{
	cout << "IdleState::idle" << endl;

}

void IdleState::move(Player* player)
{
	cout << "IdleState::move" << endl;

}

void IdleState::attack(Player* player)
{
	cout << "IdleState::attack" << endl;

}

void IdleState::beHit(Player* player)
{
	cout << "IdleState::beHit" << endl;
}

// 이동
MoveState* MoveState::GetInstance()
{
	if (instance == nullptr) instance = new MoveState();
	return instance;
}

void MoveState::idle(Player* player)
{
	cout << "MoveState::idle" << endl;

}

void MoveState::move(Player* player)
{
	cout << "MoveState::move" << endl;

}

void MoveState::attack(Player* player)
{
	cout << "MoveState::attack" << endl;

}

void MoveState::beHit(Player* player)
{
	cout << "MoveState::beHit" << endl;
}

// 공격
AttackState* AttackState::GetInstance()
{
	if (instance == nullptr) instance = new AttackState();
	return instance;
}

void AttackState::idle(Player* player)
{
	cout << "AttackState::idle" << endl;

}

void AttackState::move(Player* player)
{
	cout << "AttackState::move" << endl;

}

void AttackState::attack(Player* player)
{
	cout << "AttackState::attack" << endl;

}

void AttackState::beHit(Player* player)
{
	cout << "AttackState::beHit" << endl;
}

// 피격
BeHitState* BeHitState::GetInstance()
{
	if (instance == nullptr) instance = new BeHitState();
	return instance;
}

void BeHitState::idle(Player* player)
{
	cout << "BeHitState::idle" << endl;

}

void BeHitState::move(Player* player)
{
	cout << "BeHitState::move" << endl;

}

void BeHitState::attack(Player* player)
{
	cout << "BeHitState::attack" << endl;

}

void BeHitState::beHit(Player* player)
{
	cout << "BeHitState::beHit" << endl;
}
#endif // STATEPATTERN

