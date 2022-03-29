#pragma once
#include "Player.h"

class STATE
{
public:
	// ���¿� ���� �ൿ�� �Լ���
	virtual void idle(Player* player) =0;
	virtual void move(Player* player) =0;
	virtual void attack(Player* player) =0;
	virtual void beHit(Player* player) = 0;

protected:

	void SetPlayerState(Player* player, STATE* state)
	{
		player->setPlayerState(state);
	}

};

// ��� ���� 
class IdleState : public STATE
{
	static IdleState* instance;
public:
	static IdleState* GetInstance();
	virtual void idle(Player* player);	 // ��� �� ��� 
	virtual void move(Player* player);	 // ��� �� �̵� -> ���º�ȭ
	virtual void attack(Player* player); // ��� �� ���� -> ���º�ȭ
};

// �̵� ���� 
class MoveState : public STATE
{
	static MoveState* instance;
public:
	static MoveState* GetInstance();
	virtual void idle(Player* player);	 // �̵� �� ��� -> ���º�ȭ
	virtual void move(Player* player);	 // �̵� �� �̵�
	virtual void attack(Player* player); // �̵� �� ���� -> ���º�ȭ
};

// ���� ���� 
class AttackState : public STATE
{
	static AttackState* instance;
public:
	static AttackState* GetInstance();
	virtual void idle(Player* player);	 // ���� �� ��� -> ���º�ȭ
	virtual void move(Player* player);	 // ���� �� �̵� -> ���º�ȭ
	virtual void attack(Player* player); // ���� �� ���� 
};

// �ǰ� ���� 
class BeHitState : public STATE
{
	static BeHitState* instance;
public:
	static BeHitState* GetInstance();
	virtual void idle(Player* player);	 // �ǰ� �� ��� -> ���º�ȭ
	virtual void move(Player* player);	 // �ǰ� �� �̵� -> ���º�ȭ
	virtual void attack(Player* player); // �ǰ� �� ���� -> ���º�ȭ
};