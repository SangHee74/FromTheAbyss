#pragma once
#include "GameNode.h"
#include "Animation.h"

#pragma region player Animation
class PlayerAniClass : public GameNode
{
private:
	// 이동 이미지 _aI
	Image* _aIplayerMoveDownImg;		//p_run_6
	Image* _aIplayerMoveUpImg;			//p_run_12
	Image* _aIplayerMoveLRImg;			//p_run_9
	Image* _aIplayerMoveLRUpImg;		//p_run_11
	Image* _aIplayerMoveLRDownImg;		//p_run_7

	// 이동 에니메이션 _aM
	Animation* _aMplayerMoveDownImg		;
	Animation* _aMplayerMoveUpImg		;
	Animation* _aMplayerMoveLRImg		;
	Animation* _aMplayerMoveLRUpImg		;
	Animation* _aMplayerMoveLRDownImg	;


	
	// 무기 에니메이션

public:
	PlayerAniClass() {}
	~PlayerAniClass() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(int x, int y);

};
#pragma endregion
