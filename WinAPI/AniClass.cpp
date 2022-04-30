#include "Stdafx.h"
#include "AniClass.h"

HRESULT PlayerMoveAni::init(void)
{
	_aIPlayerMove = IMG("p_move");

	_aMPlayerMove = new Animation;
	_aMPlayerMove->init(_aIPlayerMove->getWidth(), _aIPlayerMove->getHeight(),30, 50);

	_aMPlayerMove->setDefPlayFrame(false, true);
	_aMPlayerMove->setFPS(12);


	return S_OK;
}

void PlayerMoveAni::release(void)
{
	_aMPlayerMove->release();
	SAFE_DELETE(_aMPlayerMove);
}

void PlayerMoveAni::update(void)
{
	_aMPlayerMove->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void PlayerMoveAni::render(int x, int y)
{
	_aIPlayerMove->aniRender(getMemDC(), x, y, _aMPlayerMove);
}

#pragma endregion



