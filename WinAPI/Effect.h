#pragma once
#include "GameNode.h"

enum class EFFECT_TYPE
{
	P_ATKACK_ATKMOTION, // 상태에서 직접 관리
	P_ATKACK_COLLISION,	  // 플레이어->몬스터 타격성공

	M_ATKACK_ATKMOTION,	  // 몬스터 공격모션
	M_ATKACK_COLLISION,	  // 몬스터->플레이어 타격성공

	M_DEFFENSE_DIE,		  // 필드몬스터 죽음
	M_DEFFENSE_BOSSDIE,	  // 보스몬스터 죽음
	EFFECT_END
};
enum class DAMAGECOLOR
{
	DAMAGE_WHITE, DAMAGE_RED, DAMAGE_GREEN, DAMAGE_BLUE,
	DAMAGE_END
};

struct tagEffect
{
	Image* img;
	RECT rc;
	int count;
	int curFrameX;
	int curFrameY;
	float x, y;
	bool onEffect;
};

class PlayerEffect :public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createEff(RECT rc, EFFECT_TYPE type); // 이펙트 이미지, 범위렉트(+카메라조정) 업데이트 
	void draw(void);
	void removeEffect(int arrNum);

	void centerDamageEffect(int damage, POINT pos, DAMAGECOLOR color);

	PlayerEffect() {}
	~PlayerEffect() {}
};


class MonsterEffect :public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createEff(RECT rc, EFFECT_TYPE type); // 이펙트 이미지, 범위렉트(+카메라조정) 업데이트 
	void draw(void);
	void removeEffect(int arrNum);

	void centerDamageEffect(int damage, POINT pos);

	MonsterEffect() {}
	~MonsterEffect() {}
};
