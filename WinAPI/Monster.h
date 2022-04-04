#pragma once

enum class MONSTERDIRECTION
{
	UP, DOWN, LEFT, RIGHT,
};

enum class MOSTERSTATE
{
	IDLE, MOVE, HIT, DEAD, ATTACK
};

struct tagMosterStatus
{
	int ID;
	int curHp;
	int curSp;
	int maxHp;
	int maxSp;
	int dropExp;
	int dropLufia;
	int dropItemID;
};

struct tagMosterData
{
	RECT	moveRc;
	RECT	drawRc;
	int		movePosX, movePosY; 
	int		drawPosX, drawPosY;  
	int		frameX, frameY;
	int		width, height;  
	int		speed;
	Image*  image;	  
};


class Monster
{
protected:
	MOSTERSTATE _state;
	MONSTERDIRECTION _direction;
	tagMosterData _monster;
	tagMosterStatus _status;

public:

};

