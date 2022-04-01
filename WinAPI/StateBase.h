#pragma once
#include "STATE.h"

class Player;

// 대기 상태 
class IdleState : public STATE
{
	static IdleState* instance;
	int timeCount;
public:
	static IdleState* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
	virtual void stateRender(Player* player);

};


// 이동 상태 
class MoveState : public STATE
{
	static MoveState* instance;
	int timeCount;
public:
	static MoveState* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
	virtual void stateRender(Player* player);
};


#if 0

// 피격 상태 - 일정시간동안 움직일 수 없고, 키 입력이 없는 경우 대기한다.
class BeHitState : public STATE
{
	static BeHitState* instance;
	int timeCount;

public:
	static BeHitState* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
	virtual void stateRender();
};

// 다운 상태 - 일정시간동안 쓰러진 모션 후 타이틀로 돌아간다
class DeadState : public STATE
{
	static DeadState* instance;
	int timeCount;

public:
	static DeadState* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
	virtual void stateRender();
};


#endif





