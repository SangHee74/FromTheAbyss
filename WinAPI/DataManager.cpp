#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	_player = new Player();
	_player->init();


	return S_OK;
}

void DataManager::release(void)
{

	_player->release();
	SAFE_DELETE(_player);
}

void DataManager::update(void)
{
}

void DataManager::render(void)
{
}
