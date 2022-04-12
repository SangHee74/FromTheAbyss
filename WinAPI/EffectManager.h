#pragma once
#include "SingletonBase.h"
#include "Effect.h"

class EffectManager :public SingletonBase<DataManager>
{
private: 
	PlayerEffect* _playereEffect;
	MosterEffect* _monsterEffect;

public:
	EffectManager() {}
	~EffectManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PlayerEffect& getPlayerEff() { return (*_playereEffect); }
	MosterEffect& getMosterEff() { return (*_monsterEffect); }

};

