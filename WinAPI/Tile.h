#pragma once


//타일 속성
enum groundType // 이동가능, 이동불가 지형
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
	POINT pos; // n번째 x,y 
	//POINT drawPos; // 그려질 x,y
	int fX; // frame X
	int fY; // frame Y

	bool onDraw;
	bool ptInRect;
	abyssType _abyssType;
	groundType _moveCheck;
};

