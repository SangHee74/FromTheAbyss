#pragma once
#include "SingletonBase.h"
#include "Effect.h"

class EffectManager :public SingletonBase<EffectManager>
{
private: 
	PlayerEffect* _playereEffect;
	MonsterEffect* _monsterEffect;

public:
	EffectManager() {}
	~EffectManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PlayerEffect& getPlayerEff() { return (*_playereEffect); }
	MonsterEffect& getMonsterEff() { return (*_monsterEffect); }

};

