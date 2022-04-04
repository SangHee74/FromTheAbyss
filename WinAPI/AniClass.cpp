#include "Stdafx.h"
#include "AniClass.h"

HRESULT PlayerMoveAni::init(void)
{
	// ���ϸ��̼� �̹��� ã��
	_aIPlayerMove = IMG("p_move");

	// ���ϸ��̼� Ŭ���� init()
	_aMPlayerMove = new Animation;
	_aMPlayerMove->init(_aIPlayerMove->getWidth(), _aIPlayerMove->getHeight(),30, 50);

	// ���ϸ��̼� Ŭ���� ����(������,����)
	_aMPlayerMove->setDefPlayFrame(false, true);
	_aMPlayerMove->setFPS(12);


	return S_OK;
}

void PlayerMoveAni::release(void)
{
	// ���ϸ��̼� Ŭ���� ����
	_aMPlayerMove->release();
	SAFE_DELETE(_aMPlayerMove);
}

void PlayerMoveAni::update(void)
{
	// ���ϸ��̼� ������ ������Ʈ 
	_aMPlayerMove->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void PlayerMoveAni::render(int x, int y)
{
	// ���ϸ��̼� �ִϷ���
	_aIPlayerMove->aniRender(getMemDC(), x, y, _aMPlayerMove);
}

#pragma endregion



