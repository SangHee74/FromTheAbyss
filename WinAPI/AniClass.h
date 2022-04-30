#pragma once
#include "GameNode.h"
#include "Animation.h"

#pragma region player Animation

class PlayerMoveAni : public GameNode
{
private:
	Image* _aIPlayerMove;		// p_move

	Animation* _aMPlayerMove;


public:
	PlayerMoveAni() {}
	~PlayerMoveAni() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(int x, int y);

};
#pragma endregion
