#include "Stdafx.h"
#include "STATE.h"

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
