#pragma once
#include "GameNode.h"

class ImageClass;

class StartScene : public GameNode
{
private:

	ImageClass* _img;

public:
	StartScene() {}
	~StartScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

