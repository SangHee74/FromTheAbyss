#include "Stdafx.h"
#include "STATE.h"
#include "Player.h"

#ifdef STATEPATTERN

STATE::~STATE()
{
}




void Idle::enterState()
{
	//���¿� ������ �� ���¸��� �ʱ�ȭ�� ���ݴϴ� 
	//������ ���¿� ���� �̹��� ����� ���� index�� �ʱ�ȭ
	//_p->setPlayerFrameX(0);

}

void Idle::updateState()
{
	count++;
	// 30ī��Ʈ�� ������ ������ ���� �ٽ� 0���� �ʱ�ȭ �˴ϴ�
	// 30ī��Ʈ(0.5��)������ �� ���Է��ϸ� �����޺� ���°� �ǰ� ������ϴ�


	// ��� -> ����Ű ������ ������
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
	if (KEYMANAGER->isOnceKeyDown('X')) // �Ϲ� ����
	{
		_p->setState(PLAYERSTATE::ATT);
	}
}

void Idle::exitState()
{
	count = 0; // ���¸� Ż���Ҷ� ����ǿ� ī��Ʈ�� �ʱ�ȭ�ϰ� �߽��ϴ�.
}













#else
IdleState* IdleState::instance;
MoveState* MoveState::instance;
AttackState* AttackState::instance;
BeHitState* BeHitState::instance;


// ���
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

// �̵�
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

// ����
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

// �ǰ�
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

