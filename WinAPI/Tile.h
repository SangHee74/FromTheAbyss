#pragma once


//Ÿ�� �Ӽ�
enum groundType // �̵�����, �̵��Ұ� ����
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

