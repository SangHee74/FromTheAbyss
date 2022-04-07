#pragma once
#include "SingletonBase.h"
#include "Player.h"

class DataManager :public SingletonBase<DataManager>
{
private:

	Player* _player;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Player* getPlayer() { return _player; }
	void setPlayer(Player* User) { _player = User; }
	void clearPlayer() { _player = nullptr; }

};

