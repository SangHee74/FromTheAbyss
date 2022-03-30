#pragma once
//#include "Player.h"
#define STATEPATTERN


#ifdef STATEPATTERN

class Player;

class STATE
{
protected:
	Player* _p;
	// 각각의 상태들에게 플레이어를 링크로 받아올 수 있게 만들었습니다
public:
	~STATE();
	virtual void enterState() = 0;
	virtual void updateState() = 0;
	virtual void exitState() = 0;

	void linkMemberAdress(Player* player) { _p = player; }

};



class Idle : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};




#else 
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
	virtual void move(Player* player);	 // 대기 중 이동 -> 상태변화(움직이기)
	virtual void attack(Player* player); // 대기 중 공격 -> 상태변화(공격하기)
	virtual void beHit(Player* player);	 // 대기 중 피격 -> 상태변화(피격모션)

};

// 이동 상태 
class MoveState : public STATE
{
	static MoveState* instance;
public:
	static MoveState* GetInstance();
	virtual void idle(Player* player);	 // 이동 중 대기 -> 상태변화(대기하기)
	virtual void move(Player* player);	 // 이동 중 이동
	virtual void attack(Player* player); // 이동 중 공격 -> 상태변화(공격하기)
	virtual void beHit(Player* player);  // 이동 중 피격 -> 상태변화(피격모션)
};

// 공격 상태 - 무기타입에 따라 콤보 공격횟수가 달라진다.
class AttackState : public STATE
{
	static AttackState* instance;
public:
	static AttackState* GetInstance();
	virtual void idle(Player* player);	 // 공격 중 대기 -> 상태변화(대기하기)
	virtual void move(Player* player);	 // 공격 중 이동 -> 상태변화(이동하기)
	virtual void attack(Player* player); // 공격 중 공격 
	virtual void beHit(Player* player);  // 공격 중 피격 -> 상태변화(피격모션)

};

// 피격 상태 - 일정시간동안 움직일 수 없고, 키 입력이 없는 경우 대기한다.
class BeHitState : public STATE
{
	static BeHitState* instance;
public:
	static BeHitState* GetInstance();
	virtual void idle(Player* player);	 // 피격 중 대기 -> 상태변화(대기하기)
	virtual void move(Player* player);	 // 피격 중 이동 -> 상태변화(이동하기)
	virtual void attack(Player* player); // 피격 중 공격 -> 상태변화(공격하기)
	virtual void beHit(Player* player);  // 피격 중 피격 
};
#endif // STATEPATTERN