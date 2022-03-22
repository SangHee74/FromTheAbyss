#pragma once
#include "GameNode.h"
class SoundScene :public GameNode
{
public:
	SoundScene() {}
	~SoundScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

