#include "Stdafx.h"
#include "Effect.h"

#pragma region player


HRESULT PlayerEffect::init(void)
{
	return S_OK;
}

void PlayerEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->release();
		SAFE_DELETE(_viEffect->img);
	}
}

void PlayerEffect::update(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->count++;
		if (_viEffect->count % 4 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);

			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				_viEffect->onEffect = false;
				break;
			}
		}
	}

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		if (!_viEffect->onEffect)
		{
			_viEffect->img->release();
			SAFE_DELETE(_viEffect->img);
			_vEffect.erase(_viEffect);
			break;
		}
	}
}

void PlayerEffect::render(void)
{
	draw();
}

// show���� ������ ����Ʈrc�� �������� �̹����� ��� �� .
void PlayerEffect::draw(void)
{
	if (DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRangeUpdate)
	{
		DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkEffImg->render(getMemDC(),
			DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRc.left - CAM->getScreenRect().left,
			DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRc.top - CAM->getScreenRect().top);
	}

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);
	}
}

void PlayerEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);
	_vEffect.erase(_vEffect.begin());
}


// ����Ʈ ���Ϳ� ����Ʈ �߰��ϱ�.
// ����Ʈ �̹���, ������Ʈ(+ī�޶�����) ������Ʈ 
void PlayerEffect::createEff(RECT rc, EFFECT_TYPE type)
{
	tagEffect effect;
	effect.img = new Image;
	switch (type)
	{
	case EFFECT_TYPE::P_ATKACK_COLLISION:
		//effect.img->init("Resources/Images/Effect/eff_collision.bmp", 0.0f, 0.0f, 525, 385, 5, 4, MGT);
		effect.img->init("Resources/Images/Effect/eff_Collision2.bmp", 0.0f, 0.0f, 210, 98, 2, 1, MGT);

		break;
	}

	// ī�޶� ���� 
	effect.rc = RectMake(rc.left - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40,
		rc.right - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40);

	effect.onEffect = true;
	_vEffect.push_back(effect);
}

void PlayerEffect::centerDamageEffect(int damage, POINT pos, DAMAGECOLOR color)
{
	// �⺻ ȭ��Ʈ
	Image* damageFontImg = IMG("Num_W");
	int tempX = 18;
	//int tempY = 0;

	switch (color)
	{
	case DAMAGECOLOR::DAMAGE_RED:
		damageFontImg = IMG("Num_R");
		break;
	case DAMAGECOLOR::DAMAGE_GREEN:
		damageFontImg = IMG("Num_G");
		break;
	case DAMAGECOLOR::DAMAGE_BLUE:
		damageFontImg = IMG("Num_B");
		break;
	}

	// �ִ� 9999
	if (damage > 999)		 damageFontImg->frameRender(getMemDC(), pos.x - tempX * 2, pos.y, damage / 1000 % 10, 0);
	if (damage > 99)		 damageFontImg->frameRender(getMemDC(), pos.x - tempX, pos.y, damage / 100 % 10, 0);
	if (damage > 9)			 damageFontImg->frameRender(getMemDC(), pos.x, pos.y, damage / 10 % 10, 0);
							 damageFontImg->frameRender(getMemDC(), pos.x + tempX, pos.y, damage % 10, 0);
	if (damage <= 0)		 damageFontImg->frameRender(getMemDC(), pos.x + tempX, pos.y, 0, 0);
}

#pragma endregion 



#pragma region Monster

HRESULT MonsterEffect::init(void)
{
	return S_OK;
}

void MonsterEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->release();
		SAFE_DELETE(_viEffect->img);
	}
}

void MonsterEffect::update(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->count++;
		if (_viEffect->count % 8 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);

			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				_viEffect->onEffect = false;
				break;
			}
		}
	}

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		if (!_viEffect->onEffect)
		{
			_viEffect->img->release();
			SAFE_DELETE(_viEffect->img);
			_vEffect.erase(_viEffect);
			break;
		}
	}
}

void MonsterEffect::render(void)
{
	draw();
}


void MonsterEffect::draw(void)
{

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);
	}

}

void MonsterEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);
	_vEffect.erase(_vEffect.begin());
}

void MonsterEffect::createEff(RECT rc, EFFECT_TYPE type)
{
	tagEffect effect;
	effect.img = new Image;

	switch (type)
	{
	case EFFECT_TYPE::M_ATKACK_COLLISION:
		effect.img->init("Resources/Images/Object/eff_Collision2.bmp", 210, 98, 2, 1, MGT);
		break;
	case EFFECT_TYPE::M_DEFFENSE_DIE:
		effect.img->init("Resources/Images/Object/monsterDie.bmp", 160 * MAGNI, 32 * MAGNI, 5, 1, MGT);
		break;
	case EFFECT_TYPE::M_DEFFENSE_BOSSDIE:
		effect.img->init("Resources/Images/Object/BossDie.bmp", 160 * MAGNI, 30 * MAGNI, 5, 1, MGT);
		break;
	}


	// ī�޶� ���� 
	effect.rc = RectMake(rc.left - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40,
		rc.right - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40);


	_vEffect.push_back(effect);
}

void MonsterEffect::centerDamageEffect(int damage, POINT pos)
{
	// �⺻ ����
	Image* damageFontImg = IMG("Num_R");
	int tempX = 18;
	

	// �ִ� 9999
	if (damage > 999)		 damageFontImg->frameRender(getMemDC(), pos.x - tempX * 2, pos.y, damage / 1000 % 10, 0);
	if (damage > 99)		 damageFontImg->frameRender(getMemDC(), pos.x - tempX, pos.y, damage / 100 % 10, 0);
	if (damage > 9)			 damageFontImg->frameRender(getMemDC(), pos.x, pos.y, damage / 10 % 10, 0);
							 damageFontImg->frameRender(getMemDC(), pos.x + tempX, pos.y, damage % 10, 0);
	if (damage <= 0)		 damageFontImg->frameRender(getMemDC(), pos.x + tempX, pos.y, 0, 0);

}


#pragma endregion 

HRESULT MonstersEffect::init(RECT rc, EFFECT_TYPE type)
{


	return S_OK;
}

void MonstersEffect::release(void)
{
}

void MonstersEffect::update(void)
{
}

void MonstersEffect::render(void)
{
}
