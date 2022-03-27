#pragma once


//Ÿ�� �Ӽ�
enum groundType // �̵�����, �̵��Ұ� ����
{ 
	GROUND,WALL,GROUND_END
};

enum  abyssType
{
	NONE,ABYSS1, ABYSS2, ABYSS3, ABYSS4, ABYSS5,
	ABYSS6, ABYSS7, ABYSS8, ABYSS9,
};

class Tile
{
public:
	RECT rc;
	POINT pos; // n��° x,y 
	//POINT drawPos; // �׷��� x,y
	int fX; // frame X
	int fY; // frame Y

	bool onDraw;
	bool ptInRect;
	abyssType _abyssType;
	groundType _moveCheck;
};

