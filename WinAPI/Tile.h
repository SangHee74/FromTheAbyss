#pragma once

//타일 사이즈
#define TILESIZE_X 26
#define TILESIZE_Y 26

//타일 갯수
#define TILEMAX_X 50
#define TILEMAX_Y 50

//타일 속성
enum groundType // 이동가능, 이동불가 지형
{ 
	GROUND,WALL
};

enum tileStage // 스테이지 별 타일셋
{
	ABYSS1,ABYSS2,ABYSS3,ABYSS4,ABYSS5,ABYSS6,ABYSS7,ABYSS8
};




class Tile
{
public:
	int x;
	int y;
	int fX;
	int fY;
	int nX;
	int nY;

	bool inTile;
	groundType moveCheck;

};

