#include "Stdafx.h"
#include "EffectManager.h"



HRESULT EffectManager::init(void)
{
	_playereEffect = new PlayerEffect();
	_playereEffect->init();

	_monsterEffect = new MosterEffect();
	_monsterEffect->init();

	return S_OK;
}

void EffectManager::release(void)
{
	_playereEffect->release();
	SAFE_DELETE(_playereEffect);

	_monsterEffect->release();
	SAFE_DELETE(_monsterEffect);
}

void EffectManager::update(void)
{
	_playereEffect->update();
	_monsterEffect->update();
}

void EffectManager::render(void)
{
	_monsterEffect->render();
	_playereEffect->render();
}
