#pragma once
#include "SingletonBase.h"
#include "Effect.h"

enum class EFFECT_TYPE
{
	//P_EFFECT_ATTMOTION, // 惑怕俊辑 流立 包府
	P_EFFECT_COLLISION,

	M_EFFECT_ATTMOTION,
	M_EFFECT_COLLISION,

	M_EFFECT_DIE,
	M_EFFECT_BOSSDIE,
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
	void show(RECT rc, EFFECT_TYPE type);
	void draw(void);
	void removeEffect(int arrNum);



};

