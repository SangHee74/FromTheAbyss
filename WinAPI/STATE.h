#pragma once
#include "Player.h"
//#define STATEPATTERN

// 각 해제 필요

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

#pragma region 상태 클래스
// 대기/이동/피격/죽음
class Idle : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Move : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class BeHit : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class DEAD : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

// 공격 =============================================================
class Att1 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Att2 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Att3 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

// 스킬 =============================================================
class Skill1 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Skill2 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};

class Skill3 : public STATE
{
private:
	int count;
public:
	void enterState();
	void updateState();
	void exitState();
};



#pragma endregion

#else 
class STATE
{
public:
	STATE() {}
	virtual ~STATE() {}

	// 상태패턴 함수
	virtual void stateInit(Player* player)=0;
	virtual void stateUpdate(Player* player)=0;
	virtual void stateRelease()=0;

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
	static IdleState* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제

};


// 이동 상태 
class MoveState : public STATE
{
	static MoveState* instance;
public:
	static MoveState* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};


// 피격 상태 - 일정시간동안 움직일 수 없고, 키 입력이 없는 경우 대기한다.
class BeHitState : public STATE
{
	static BeHitState* instance;
public:
	static BeHitState* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};

// 다운 상태 - 일정시간동안 쓰러진 모션 후 타이틀로 돌아간다
class DeadState : public STATE
{
	static DeadState* instance;
public:
	static DeadState* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};


#pragma region attack
// 공격 상태 - 무기타입에 따라 콤보 공격횟수가 달라진다.
class OneHandWeaponCombo : public STATE
{
	static OneHandWeaponCombo* instance;
public:
	static OneHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};


class TwoHandWeaponCombo : public STATE
{
	static TwoHandWeaponCombo* instance;
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
public:
	static SoulCapture* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};

class SpearStrike : public STATE
{
	static SpearStrike* instance;
public:
	static SpearStrike* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
};


#pragma endregion 


#endif // STATEPATTERN