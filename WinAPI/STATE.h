#pragma once
#include "Player.h"

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
 
protected:

	void SetPlayerState(Player* player, STATE* state)
	{
		player->setPlayerState(state);
	}

};


