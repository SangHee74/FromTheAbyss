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
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void EffectManager::update(void)
{

}

void EffectManager::render(void)
{
	draw();
}

void EffectManager::draw(void)
{

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(_viEffect->img->getMemDC(), _viEffect->rc.left, _viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 4 == 0)  // 몬스터는 8
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);

			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void EffectManager::removeEffect(int arrNum)
{
}

void EffectManager::show(int x, int y)
{
	
}

void EffectManager::addEff(RECT rc, EFFECT_TYPE type)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));

	effect.img = new Image;

	switch (type)
	{
	case EFFECT_TYPE::P_EFFECT_COLLISION:
		effect.img->init("Resources/Images/Object/eff_collision.bmp", 0.0f, 0.0f, 
			525, 385, 5, 4, MGT);

		// 카메라 적용 
		effect.rc = RectMake(rc.left - CAM->getScreenRect().left - 40,
			rc.top - CAM->getScreenRect().top - 40,
			rc.right - CAM->getScreenRect().left - 40,
			rc.top - CAM->getScreenRect().top - 40);

		break;
	case EFFECT_TYPE::M_EFFECT_ATTMOTION:
		break;
	case EFFECT_TYPE::M_EFFECT_COLLISION:
		effect.img->init("Resources/Images/Object/eff_bossCollision.bmp", 0.0f, 0.0f,
			210, 98 ,2,1, MGT);

		// 카메라 적용 
		effect.rc = RectMake(rc.left - CAM->getScreenRect().left - 40,
			rc.top - CAM->getScreenRect().top - 40,
			rc.right - CAM->getScreenRect().left - 40,
			rc.top - CAM->getScreenRect().top - 40);
		
		break;
	case EFFECT_TYPE::M_EFFECT_DIE:
		effect.img->init("Resources/Images/Object/monsterDie.bmp", 0.0f, 0.0f,
			160 , 32  , 5, 1, MGT);

		effect.rc = RectMake(rc.left - CAM->getScreenRect().left + 20,
			rc.top - CAM->getScreenRect().top + 30,
			rc.right - CAM->getScreenRect().left + 20,
			rc.top - CAM->getScreenRect().top + 30);
		break;
	case EFFECT_TYPE::M_EFFECT_BOSSDIE:
		effect.img->init("Resources/Images/Object/BossDie.bmp", 0.0f, 0.0f,
			160, 30, 5, 1, MGT);

		effect.rc = RectMake(rc.left - CAM->getScreenRect().left + 20,
			rc.top - CAM->getScreenRect().top + 30,
			rc.right - CAM->getScreenRect().left + 20,
			rc.top - CAM->getScreenRect().top + 30);
		break;
	}
	

	_vEffect.push_back(effect);
}

