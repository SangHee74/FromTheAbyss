#pragma once
#include "GameNode.h"

enum BUTTONNUM
{
	BUTTON_ONE,
	BUTTON_TWO,
	BUTTON_THREE,
	BUTTON_END
};
enum AbyssIdx : UINT8
{
	BEFORE,
	ABYSS,
	STAGE
};


class Abyss :public GameNode
{
private:

	RECT _buttonRc[BUTTON_END];
	RECT _backButton;
	AbyssIdx _abyssIdx;
	bool _isStage;
	tagOnlyText _index[3];
	int _abyss;
	int _stage;
	int _maxAbyss;
	int _maxStage;

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

	int getAbyss() { return _abyss; }
	int getStage() { return _stage; }
};