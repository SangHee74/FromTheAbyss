#include "Stdafx.h"
#include "AniClass.h"

HRESULT PlayerAniClass::init(void)
{
	// 에니메이션 이미지 찾기
	_aIplayerMoveDownImg	= IMG("p_run_6");
	_aIplayerMoveUpImg		= IMG("p_run_12");
	_aIplayerMoveLRImg		= IMG("p_run_9");
	_aIplayerMoveLRUpImg	= IMG("p_run_11");
	_aIplayerMoveLRDownImg	= IMG("p_run_7");

	// 에니메이션 클래스 init()
	_aMplayerMoveDownImg = new Animation;
	_aMplayerMoveDownImg->init(_aIplayerMoveDownImg->getWidth(), _aIplayerMoveDownImg->getHeight(),200, 92);
	_aMplayerMoveUpImg = new Animation;
	_aMplayerMoveUpImg->init(_aIplayerMoveUpImg->getWidth(), _aIplayerMoveUpImg->getHeight(), 260, 180);
	_aMplayerMoveLRImg = new Animation;
	_aMplayerMoveLRImg->init(_aIplayerMoveLRImg->getWidth(), _aIplayerMoveLRImg->getHeight(), 310, 190);
	_aMplayerMoveLRUpImg = new Animation;
	_aMplayerMoveLRUpImg->init(_aIplayerMoveLRUpImg->getWidth(), _aIplayerMoveLRUpImg->getHeight(), 270, 32);
	_aMplayerMoveLRDownImg = new Animation;
	_aMplayerMoveLRDownImg->init(_aIplayerMoveLRDownImg->getWidth(), _aIplayerMoveLRDownImg->getHeight(),260 ,180 );

	// 에니메이션 클래스 세팅
	_aMplayerMoveDownImg->setDefPlayFrame(false, true);
	_aMplayerMoveDownImg->setFPS(12);
	_aMplayerMoveUpImg->setDefPlayFrame(false, true);
	_aMplayerMoveUpImg->setFPS(12);
	_aMplayerMoveLRImg->setDefPlayFrame(false, true);
	_aMplayerMoveLRImg->setFPS(12);
	_aMplayerMoveLRUpImg->setDefPlayFrame(false, true);
	_aMplayerMoveLRUpImg->setFPS(12);
	_aMplayerMoveLRDownImg->setDefPlayFrame(false, true);
	_aMplayerMoveLRDownImg->setFPS(12);


	return S_OK;
}

void PlayerAniClass::release(void)
{
	// 에니메이션 클래스 해제
	_aMplayerMoveDownImg->release();
	_aMplayerMoveUpImg->release();
	_aMplayerMoveLRImg->release();
	_aMplayerMoveLRUpImg->release();
	_aMplayerMoveLRDownImg->release();
	SAFE_DELETE(_aMplayerMoveDownImg);
	SAFE_DELETE(_aMplayerMoveUpImg);
	SAFE_DELETE(_aMplayerMoveLRImg);
	SAFE_DELETE(_aMplayerMoveLRUpImg);
	SAFE_DELETE(_aMplayerMoveLRDownImg);
}

void PlayerAniClass::update(void)
{
	// 에니메이션 프레임 업데이트 
	_aMplayerMoveDownImg  ->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_aMplayerMoveUpImg    ->frameUpdate(TIMEMANAGER->getElapsedTime() * 1); 
	_aMplayerMoveLRImg    ->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_aMplayerMoveLRUpImg  ->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_aMplayerMoveLRDownImg->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void PlayerAniClass::render(int x, int y)
{
	// 에니메이션 애니렌더
	_aIplayerMoveDownImg->aniRender(getMemDC(), x, y, _aMplayerMoveDownImg);
	_aIplayerMoveUpImg->aniRender(getMemDC(), x, y, _aMplayerMoveUpImg);
	_aIplayerMoveLRImg->aniRender(getMemDC(), x, y, _aMplayerMoveLRImg);
	_aIplayerMoveLRUpImg->aniRender(getMemDC(), x, y, _aMplayerMoveLRUpImg);
	_aIplayerMoveLRDownImg->aniRender(getMemDC(), x, y, _aMplayerMoveLRDownImg);
}

#pragma endregion



