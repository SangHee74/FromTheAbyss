#pragma once
#include "STATE.h"

class Player;

// 공격 상태 - 무기타입에 따라 콤보 공격횟수가 달라진다.
class OneHandWeaponCombo : public STATE
{
	static OneHandWeaponCombo* instance;
	//int _timeCount; 
	float _comboInputMinTime; // 최소 키 입력 시간
	float _comboInputMaxTime; // 최대 키 입력 시간
	float _playerMotionTime; // 최대 키 입력 시간

	// 001 : 1단 콤보
	// 010 : 2단 콤보
	// 100 : 3단 콤보 
	bitset<3> _comboStart;
	bitset<3> _comboEnd;

public:
	static OneHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // 초기화
	virtual void stateUpdate(Player* player);  // 업데이트 
	virtual void stateRelease(); // 해제
	virtual void stateRender(Player* player);


	void comboOne(Player* player);
	void comboTwo(Player* player);
	void comboThree(Player* player);
	void weaponAttFrameSetting(Player* player);
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
	virtual void stateRender(Player* player);

};

#if 0

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
	virtual void stateRender(Player* player);

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
	virtual void stateRender(Player* player);
};


#endif