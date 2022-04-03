#pragma once
#include "Player.h"
//class Player;

class STATE
{
public:
	STATE() {}
	virtual ~STATE() {}

	// 상태패턴 함수
	virtual void stateInit(Player* player)=0;
	virtual void stateRelease()=0;
	virtual void stateUpdate(Player* player)=0;
	virtual void stateRender(Player* player)=0;
 
	//void linkMember(Player* player) { _pl = player; }

protected:

	//Player* _pl;
	void SetPlayerState(Player* player, STATE* state)
	{
		player->setPlayerState(state);
	}

};


