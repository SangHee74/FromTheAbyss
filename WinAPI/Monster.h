#pragma once
#include "GameNode.h"

enum class MONSTERDIRECTION
{
	UP, DOWN, LEFT, RIGHT
};

enum class MOSTERSTATE
{
	IDLE, MOVE, HIT, DEAD, ATTACK
};


class Monster : public GameNode
{
protected:
	MOSTERSTATE _state;
	MONSTERDIRECTION _direction;

	int  _curHp;
	//int  _curSp;
	int  _dropExp;
	int  _dropLufia;
	int  _dropItemIndex;

	RECT	_moveRc;
	int		_movePosX, _movePosY;
	int		_frameX, _frameY;
	//int		_width, _height;
	int		_speed;
	float	_rndTimeCount;
	float	_worldTimeCount;
	Image*  _image;

public:
	Monster(void);
	virtual ~Monster() {};

	HRESULT init(void);
	HRESULT init(POINT position);
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	virtual void attack(void);
	void draw(void);
	void animation(void);

	// get/set
	MOSTERSTATE getState()			 { return _state; }
	MONSTERDIRECTION getDirection()  { return _direction; }

	void setHp(int hp) { _curHp = hp; }
	int  getExp()	   { return _dropExp; }
	int  getLufia()	   { return _dropLufia; }
	int  getItem()	   { return _dropItemIndex; }

	RECT getRc() { return _moveRc; }
	int  getMovePosX() { return _movePosX; }
	int  getMovePosY() { return _movePosY; }
	int  getFrameX() { return _frameX; }
	int  getFrameY() { return _frameY; }
	int  getSpeed() { return _speed; }

};




