#include "Stdafx.h"
#include "Effect.h"


Effect::Effect()
{
}

HRESULT Effect::init(void)
{
	return S_OK;
}

HRESULT Effect::init(const char* imageKey, RECT rc)
{
	_collisionEff.image = IMAGEMANAGER->findImage(imageKey);
	_collisionEff.x = rc.left + (rc.right - rc.left) / 2;
	_collisionEff.y = rc.top;
	_collisionEff.rc = RectMakeCenter(_collisionEff.x, _collisionEff.y, _collisionEff.image->getFrameWidth(), _collisionEff.image->getFrameHeight());
	_collisionEff.onEffect = true;

	return S_OK;
}

void Effect::release(void)
{

}

void Effect::update(void)
{
}

void Effect::render(void)
{
	draw();
	animation();
}


void Effect::draw(void)
{
	_collisionEff.image->frameRender(getMemDC(),
		_collisionEff.rc.left - CAM->getScreenRect().left, 
		_collisionEff.rc.top - CAM->getScreenRect().top, _collisionEff.curFrameX, _collisionEff.curFrameY);
}

void Effect::animation(void)
{

}

void Effect::aniEff(tagEffect eff, int speed)
{
	// 오버라이딩 내용 
	eff.count++;

	if (eff.count % speed == 0)
	{
		if (eff.curFrameX == eff.image->getMaxFrameX())
		{
			eff.curFrameX = 0;
		}
		else
		{
			eff.curFrameX++;
		}

		if (eff.image->getMaxFrameY() < eff.curFrameY)
		{
			eff.onEffect = false;
		}

		eff.count = 0;
	}
}


void Effect::centerDamageEffect(int damage, POINT pos, DAMAGECOLOR color)
{
	// 기본 화이트
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

	// 최대 9999
	if (damage > 999)		 damageFontImg->frameRender(getMemDC(), pos.x - tempX * 2, pos.y, damage / 1000 % 10, 0);
	if (damage > 99)		 damageFontImg->frameRender(getMemDC(), pos.x - tempX, pos.y, damage / 100 % 10, 0);
	if (damage > 9)			 damageFontImg->frameRender(getMemDC(), pos.x, pos.y, damage / 10 % 10, 0);
							 damageFontImg->frameRender(getMemDC(), pos.x + tempX, pos.y, damage % 10, 0);
	if (damage <= 0)		 damageFontImg->frameRender(getMemDC(), pos.x + tempX, pos.y, 0, 0);
}


#pragma region player
HRESULT PlayerEffect::init(void)
{
	return S_OK;
}

void PlayerEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->image);
	}
	_vEffect.clear();
}

void PlayerEffect::update(void)
{
}

void PlayerEffect::render(void)
{
	draw();
}


void PlayerEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));

	effect.image = new Image;
	//IMAGEMANAGER->addFrameImage("eff_collision", "Resources/Images/Object/eff_collision.bmp", 525, 385, 5, 4, MGT);
	effect.image->init("Resources/Images/Object/eff_collision.bmp", 0.0f, 0.0f,
		525, 385, 5, 4, MGT);

	// 카메라 적용 
	effect.rc = RectMake(rc.left - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40,
		rc.right - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40);

	cout << "플레이어 effect x:  " << effect.x << " , y : " << effect.y << endl;

	_vEffect.push_back(effect);
}

void PlayerEffect::show(RECT rc, const char* imageKey)
{
	tagEffect effect;
	effect.image = IMG(imageKey);

	// 카메라 적용 
	effect.rc = RectMake(rc.left - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40,
		rc.right - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40);

	cout << "플레이어 effect x:  " << effect.x << " , y : " << effect.y << endl;

	_vEffect.push_back(effect);
}

void PlayerEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->image->frameRender(_viEffect->image->getMemDC(), _viEffect->rc.left, _viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 4 == 0)
		{
			_viEffect->image->setFrameX(_viEffect->image->getFrameX() + 1);

			if (_viEffect->image->getFrameX() >= _viEffect->image->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void PlayerEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].image);
	_vEffect.erase(_vEffect.begin());
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
		SAFE_DELETE(_viEffect->image);
	}
	_vEffect.clear();
}

void MonsterEffect::update(void)
{
}

void MonsterEffect::render(void)
{
	draw();
}

void MonsterEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));

	effect.image = new Image;
	//IMAGEMANAGER->addFrameImage("monsterDie", "Resources/Images/Object/monsterDie.bmp", 160 * MAGNI, 32 * MAGNI, 5, 1, MGT);
	effect.image->init("Resources/Images/Object/monsterDie.bmp", 0.0f, 0.0f,
		160 * MAGNI, 32 * MAGNI, 5, 1, MGT);



	effect.rc = RectMake(rc.left - CAM->getScreenRect().left + 20,
		rc.top - CAM->getScreenRect().top + 30,
		rc.right - CAM->getScreenRect().left + 20,
		rc.top - CAM->getScreenRect().top + 30);




	_vEffect.push_back(effect);
}

void MonsterEffect::show(RECT rc, const char * imageKey)
{

	tagEffect effect;
	effect.image = IMG(imageKey);

	// 카메라 적용 
	effect.rc = RectMake(rc.left - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40,
		rc.right - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40);

	cout << "플레이어 effect x:  " << effect.x << " , y : " << effect.y << endl;

	_vEffect.push_back(effect);
}

void MonsterEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->image->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 8 == 0)
		{
			_viEffect->image->setFrameX(_viEffect->image->getFrameX() + 1);

			if (_viEffect->image->getFrameX() >= _viEffect->image->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void MonsterEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].image);
	_vEffect.erase(_vEffect.begin());
}


#pragma endregion 