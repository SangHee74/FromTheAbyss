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
		L"�ʷα�.",
		L"������ � ���迡 �����Ұž�?",
		L""
	}
	{}
	~Abyss() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};