#include "Stdafx.h"
#include "Effect.h"


void Effect::dmgEffSetting(int damage, POINT pos, DAMAGECOLOR color)
{
	// 기본 레드
	damageFontImg = IMG("Num_R");

	switch (color)
	{
	case DAMAGECOLOR::DAMAGE_WHITE:
		damageFontImg = IMG("Num_W");
		break;
	case DAMAGECOLOR::DAMAGE_RED:
		damageFontImg = IMG("Num_R");
		break;
	case DAMAGECOLOR::DAMAGE_GREEN:
		damageFontImg = IMG("Num_G");
		break;
	case DAMAGECOLOR::DAMAGE_BLUE:
		damageFontImg = IMG("Num_B");
		break;
	case DAMAGECOLOR::DAMAGE_END:
		damageFontImg = IMG("none2");
		damage = 0; pos = { 0,0 };
		break;
	}
	
	numPosX = pos.x;
	numPosY = pos.y;
	damageNum = damage;
}

void Effect::baseEffSetting(RECT rc, EFFECT_TYPE type)
{
	img = IMG("none");
	int tempPosX, tempPosY;
	tempPosX = tempPosY = 0;
	switch (type)
	{
		// player
	case EFFECT_TYPE::P_ATKACK_ATKMOTION:
		break;
	case EFFECT_TYPE::P_ATKACK_COLLISION:
		img = IMG("eff_Collision2");
		tempPosX = tempPosY = 40;
		break;

		// monster 
	case EFFECT_TYPE::M_ATKACK_ATKMOTION:
		break;
	case EFFECT_TYPE::M_ATKACK_COLLISION:
		img = IMG("eff_Collision2");
		break;
	case EFFECT_TYPE::M_DEFFENSE_DIE:
		img = IMG("monsterDie");
		break;
	case EFFECT_TYPE::M_DEFFENSE_BOSSDIE:
		img = IMG("bossDie");
		break;

		//end
	case EFFECT_TYPE::EFFECT_END:
		img = IMG("none2");
		tempPosX = tempPosY = 0;
		break;

	}

	// 카메라 적용 
	rc = RectMake(rc.left - CAM->getScreenRect().left - tempPosX,
		rc.top - CAM->getScreenRect().top - tempPosY,
		rc.right - CAM->getScreenRect().left - tempPosX,
		rc.top - CAM->getScreenRect().top - tempPosY);

	onEffect = true;
	count = frameX = 0;
}

void Effect::effUpdate()
{
	count++;

	cout << "이펙트 카운트 : " << count << endl;
	if (count % 30 == 0)
	{
		count = 0;
		frameX++;
		if (frameX >= img->getMaxFrameX())
		{
			img = IMG("none");
			onEffect = false;
		}
	}
}

void Effect::dmgEffRender()
{
	int tempX = 18;

	// 최대 9999
	if (damageNum > 999)	 damageFontImg->frameRender(damageFontImg->getMemDC(), numPosX - tempX * 2, numPosY, damageNum / 1000 % 10, 0);
	if (damageNum > 99)		 damageFontImg->frameRender(damageFontImg->getMemDC(), numPosX - tempX, numPosY, damageNum / 100 % 10, 0);
	if (damageNum > 9)		 damageFontImg->frameRender(damageFontImg->getMemDC(), numPosX,			numPosY, damageNum / 10 % 10, 0);
							 damageFontImg->frameRender(damageFontImg->getMemDC(), numPosX + tempX, numPosY, damageNum % 10, 0);
	if (damageNum <= 0)		 damageFontImg->frameRender(damageFontImg->getMemDC(), numPosX + tempX, numPosY, 0, 0);

}

void Effect::baseEffRender()
{
	if (DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRangeUpdate)
	{
			DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkEffImg->render(
			DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkEffImg-> getMemDC(),
			DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRc.left - CAM->getScreenRect().left,
			DATAMANAGER->getPlayer()->getPlayerCollisionRc().atkRc.top - CAM->getScreenRect().top);
	}


	img->frameRender(img->getMemDC(), rc.left, rc.top, frameX,0);

	cout << "rc.left : " << rc.left << " ," << "rc.top : " << rc.left << endl;
}


// ================================================================================================
// before Player Effect
// ================================================================================================

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

// show에서 조정한 이펙트rc를 바탕으로 이미지가 출력 됨 .
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


// 이펙트 벡터에 이펙트 추가하기.
// 이펙트 이미지, 범위렉트(+카메라조정) 업데이트 
void PlayerEffect::createEff(RECT rc, EFFECT_TYPE type)
{
	tagEffect effect;
	effect.img = new Image;
	switch (type)
	{
	case EFFECT_TYPE::P_ATKACK_COLLISION:
		effect.img->init("Resources/Images/Effect/eff_Collision2.bmp", 0.0f, 0.0f, 210, 98, 2, 1, MGT);

		break;
	}

	// 카메라 적용 
	effect.rc = RectMake(rc.left - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40,
		rc.right - CAM->getScreenRect().left - 40,
		rc.top - CAM->getScreenRect().top - 40);

	effect.onEffect = true;
	_vEffect.push_back(effect);
}
