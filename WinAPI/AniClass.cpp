#include "Stdafx.h"
#include "AniClass.h"

HRESULT PlayerMoveAni::init(void)
{
	// 에니메이션 이미지 찾기
	_aIPlayerMove = IMG("p_move");

	// 에니메이션 클래스 init()
	_aMPlayerMove = new Animation;
	_aMPlayerMove->init(_aIPlayerMove->getWidth(), _aIPlayerMove->getHeight(),30, 50);

	// 에니메이션 클래스 세팅(리버스,루프)
	_aMPlayerMove->setDefPlayFrame(false, true);
	_aMPlayerMove->setFPS(12);


	return S_OK;
}

void PlayerMoveAni::release(void)
{
	// 에니메이션 클래스 해제
	_aMPlayerMove->release();
	SAFE_DELETE(_aMPlayerMove);
}

void PlayerMoveAni::update(void)
{
	// 에니메이션 프레임 업데이트 
	_aMPlayerMove->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void PlayerMoveAni::render(int x, int y)
{
	// 에니메이션 애니렌더
	_aIPlayerMove->aniRender(getMemDC(), x, y, _aMPlayerMove);
}

#pragma endregion



