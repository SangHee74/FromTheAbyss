#pragma once
#include "Player.h"



class STATE
{
public:
	STATE() {}
	virtual ~STATE() {}

	// 상태패턴 함수
	virtual void stateInit(Player* player)=0;
	virtual void stateUpdate(Player* player)=0;
	virtual void stateRelease()=0;
	virtual void stateRender(Player* player)=0;
 

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


#pragma region attack
// 공격 상태 - 무기타입에 따라 콤보 공격횟수가 달라진다.
class OneHandWeaponCombo : public STATE
{
	static OneHandWeaponCombo* instance;
	int timeCount;
	bitset<3> combo;
public:
	static OneHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제

	void comboOne(Player* player);
	void comboTwo(Player* player);
	void comboThree(Player* player);
};


class TwoHandWeaponCombo : public STATE
{
	static TwoHandWeaponCombo* instance;
	int timeCount;
public:
	static TwoHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};

#pragma region Skill

class SoulCapture : public STATE
{
	static SoulCapture* instance;
	int timeCount;
public:
	static SoulCapture* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};

class SpearStrike : public STATE
{
	static SpearStrike* instance;
	int timeCount;
public:
	static SpearStrike* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};
#endif

#pragma endregion 


