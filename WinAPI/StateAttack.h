#pragma once
#include "STATE.h"

class Player;

#if 0

// ���� ���� - ����Ÿ�Կ� ���� �޺� ����Ƚ���� �޶�����.
class OneHandWeaponCombo : public STATE
{
	static OneHandWeaponCombo* instance;
	int timeCount;
	bitset<3> combo;
public:
	static OneHandWeaponCombo* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����

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

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};

#pragma region Skill

class SoulCapture : public STATE
{
	static SoulCapture* instance;
	int timeCount;
public:
	static SoulCapture* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};

class SpearStrike : public STATE
{
	static SpearStrike* instance;
	int timeCount;
public:
	static SpearStrike* getInstance();

	virtual void stateInit(Player* player);	  // �ʱ�ȭ
	virtual void stateUpdate(Player* player);  // ������Ʈ 
	virtual void stateRelease(); // ����
};


#endif