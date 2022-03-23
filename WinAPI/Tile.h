#pragma once


//타일 속성
enum groundType // 이동가능, 이동불가 지형
{ 
	GROUND,WALL
};

class Tile
{
public:
	float drawX; 
	float drawY;
	int x;
	int y;
	int fX; // frame X
	int fY; // frame Y
	int nX; 
	int nY;

	bool inTile;
	groundType moveCheck;

};

