#pragma once
#include "GameNode.h"


enum AbyssIdx : UINT8
{
	BEFORE,
	ABYSS,
	STAGE
};


class Abyss :public GameNode
{
private:

	RECT _rc[3];
	RECT _back;
	AbyssIdx _abyssIdx;
	bool _isStage;
	tagOnlyText _index[3];

public:
	Abyss():
		_index
	{ 
		L"너로군.",
		L"오늘은 어떤 세계에 도전할거야?",
		L""
	}
	{}
	~Abyss() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};