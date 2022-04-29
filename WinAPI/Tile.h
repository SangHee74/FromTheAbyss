#pragma once


//타일 속성
enum groundType // 이동가능, 이동불가 지형
{ 
	GROUND,WALL
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

	bool ptInRect;
	groundType _moveCheck;
	abyssType _abyssType;

	void toString(void)
	{
		cout << rc.left		<<",";
		cout << rc.top 		<<",";
		cout << rc.right	<<",";
		cout << rc.bottom	<<",";
		cout << pos.x		<<",";
		cout << pos.y		<<",";
		cout << fX 			<<",";
		cout << fY 			<<",";
		cout << ptInRect 	<<",";
		cout << _abyssType	<<",";
		cout << _moveCheck	<<endl;
	}
	Tile() : rc{ 0,0,0,0 },
		pos{0,0},
		fX(0),
		fY(0),
		ptInRect(0),
		_moveCheck(GROUND),
		_abyssType(NONE)
	{}
	~Tile() {}
};

