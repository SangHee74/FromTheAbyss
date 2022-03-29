#pragma once
#include "Player.h"

class STATE
{
public:
	// 상태에 따른 행동은 함수로
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

// 대기 상태 
class IdleState : public STATE
{
	static IdleState* instance;
public:
	static IdleState* GetInstance();
	virtual void idle(Player* player);	 // 대기 중 대기 
	virtual void move(Player* player);	 // 대기 중 이동 -> 상태변화
	virtual void attack(Player* player); // 대기 중 공격 -> 상태변화
};

// 이동 상태 
class MoveState : public STATE
{
	static MoveState* instance;
public:
	static MoveState* GetInstance();
	virtual void idle(Player* player);	 // 이동 중 대기 -> 상태변화
	virtual void move(Player* player);	 // 이동 중 이동
	virtual void attack(Player* player); // 이동 중 공격 -> 상태변화
};

// 공격 상태 
class AttackState : public STATE
{
	static AttackState* instance;
public:
	static AttackState* GetInstance();
	virtual void idle(Player* player);	 // 공격 중 대기 -> 상태변화
	virtual void move(Player* player);	 // 공격 중 이동 -> 상태변화
	virtual void attack(Player* player); // 공격 중 공격 
};

// 피격 상태 
class BeHitState : public STATE
{
	static BeHitState* instance;
public:
	static BeHitState* GetInstance();
	virtual void idle(Player* player);	 // 피격 중 대기 -> 상태변화
	virtual void move(Player* player);	 // 피격 중 이동 -> 상태변화
	virtual void attack(Player* player); // 피격 중 공격 -> 상태변화
};