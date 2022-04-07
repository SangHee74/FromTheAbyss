#pragma once
#include "SingletonBase.h"
#include "Player.h"

class DataManager :public SingletonBase<DataManager>
{
private:

	Player* player;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Player* getPlayer() { return player; }
	void setPlayer(Player* User) { player = User; }
	void clearPlayer() { player = nullptr; }

};

