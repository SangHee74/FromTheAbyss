#pragma once
#include "GameNode.h"
#include "Animation.h"

#pragma region player Animation

class PlayerMoveAni : public GameNode
{
private:
	// 이동 이미지 _aI
	Image* _aIPlayerMove;		// p_move

	// 이동 에니메이션 _aM
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
