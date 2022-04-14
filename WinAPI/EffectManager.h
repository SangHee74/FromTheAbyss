#pragma once
#include "GameNode.h"
#include "Effect.h"


class EffectManager : public GameNode
{
private:
	typedef vector<Effect*> vEffect;
	typedef vector<Effect*>::iterator viEffect;
private: 
	vEffect _vEffect;
	viEffect _viEffect;

public:
	EffectManager() {}
	~EffectManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createEffect(const char* imageKey, RECT rc);
	void removeEffect(int arrNum);

	vector<Effect*> getEffects(void) { return _vEffect; }


};

