#pragma once
#include "SingletonBase.h"
#include "Effect.h"

enum class EFFECT_TYPE
{
	//P_EFFECT_ATTMOTION, // 상태에서 직접 관리
	P_EFFECT_COLLISION,	  // 플레이어->몬스터 타격성공

	M_EFFECT_ATTMOTION,	  // 몬스터 공격모션
	M_EFFECT_COLLISION,	  // 몬스터->플레이어 타격성공

	M_EFFECT_DIE,		  // 필드몬스터 죽음
	M_EFFECT_BOSSDIE,	  // 보스몬스터 죽음
	EFFECT_END
};


class EffectManager :public SingletonBase<EffectManager>
{
private: 
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

	int _x;
	int _y;
	int _countSpeed;

public:
	EffectManager() {}
	~EffectManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(int x, int y );
	void addEff(RECT rc, EFFECT_TYPE type);
	void draw(void);
	void removeEffect(int arrNum);



};

