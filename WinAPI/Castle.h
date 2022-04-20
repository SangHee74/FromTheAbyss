#pragma once
#include "GameNode.h"

struct tagQueenDialogue
{
	tagOnlyText abyss1Text[10];
	tagOnlyText abyss8Text[10];

	bitset<8> abyssCheck;
};

class Castle :public GameNode
{
private:

	// 어비스마다 나오는 대사가 다르고
	// 어떤 대사마다 얼굴(이미지가 달라짐)


	tagQueenDialogue _castleText;

	int _textIndex;
	bool _isQueenSmile; 


public:
	Castle();
	~Castle() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
