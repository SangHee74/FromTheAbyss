#include "Stdafx.h"
#include "ObjectManager.h"
#include "Player.h"
#include "EnemyManager.h"

HRESULT ObjectManager::init(void)
{
	_player = new Player();
	_player->init();

	_em = new EnemyManager();
	_em->init();

	return S_OK;
}

void ObjectManager::release(void)
{
	_player->release();
	SAFE_DELETE(_player);

	_em->release();
	SAFE_DELETE(_em);
}

void ObjectManager::update(void)
{

}

void ObjectManager::render(void)
{
}
