#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init(void)
{


	return S_OK;
}

void EffectManager::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->release();
		SAFE_DELETE(*_viEffect);
		_vEffect.erase(_viEffect);
	}

}

void EffectManager::update(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->update();

		//if (! (*_viEffect)->getOnEffect() )
		//{
		//	(*_viEffect)->release();
		//	SAFE_DELETE(*_viEffect);
		//	_vEffect.erase(_viEffect);
		//	break;
		//}
	}

}

void EffectManager::render(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render();
	}
}


void EffectManager::createEffect(const char* imageKey, RECT rc)
{
	Effect* effect = new Effect;
	effect->init(imageKey, rc);
	_vEffect.push_back(effect);

}


void EffectManager::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum]);
	_vEffect.erase(_vEffect.begin() + arrNum);
}

