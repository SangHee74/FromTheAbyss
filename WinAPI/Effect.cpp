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
		SAFE_DELETE(_viEffect->img);
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

	effect.img = new Image;
	effect.img->init("Resources/Images/Object/monsterDie.bmp", 0.0f, 0.0f,
		160 * MAGNI, 32 * MAGNI, 5, 1, MGT);

	effect.x = rc.left + (rc.right - rc.left) / 2;
	effect.y = rc.top;
	effect.rc = RectMakeCenter(effect.x, effect.y,
		effect.img->getFrameWidth(), effect.img->getFrameHeight());

	_vEffect.push_back(effect);
}

void PlayerEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 4 == 0)
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

void PlayerEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);
	_vEffect.erase(_vEffect.begin());
}
#pragma endregion 



#pragma region Monster

HRESULT MosterEffect::init(void)
{
	return S_OK;
}

void MosterEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void MosterEffect::update(void)      
{
}

void MosterEffect::render(void)
{
}

void MosterEffect::show(RECT rc)
{
	init("Resources/Images/Object/monsterDie.bmp", 0.0f, 0.0f,
		160 * MAGNI, 32 * MAGNI, 5, 1, MGT);
}

void MosterEffect::draw(void)
{
}

void MosterEffect::removeEffect(int arrNum)
{
}


#pragma endregion 