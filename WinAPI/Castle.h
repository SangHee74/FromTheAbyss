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

	// ��񽺸��� ������ ��簡 �ٸ���
	// � ��縶�� ��(�̹����� �޶���)


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
