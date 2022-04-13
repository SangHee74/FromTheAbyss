#pragma once
#include "GameNode.h"

enum class MONSTERDIRECTION
{
	UP, DOWN, LEFT, RIGHT
};

enum class MONSTERSTATE
{
	IDLE, MOVE, DEF, DEAD, ATT
};

struct tagMonsterData
{
	RECT	moveRc;
	RECT	recognitionRc;		// 플레이어를 향해 다가갈 인식 범위
	int		movePosX, movePosY; // rc업데이트
	int		frameX, frameY;
	int		speed;
	int		distance;
	float	angle;				// 플레이어를 향해 다가갈 각도
	float	rndTimeCount;
	float	worldTimeCount;
	float	attCoolTime;		// 몬스터 공격 주기
	bool	playerCheck;		// 플레이어를 인식했는지 여부
	Image*  image;				// 몬스터 이미지
};

class Monster : public GameNode
{
protected:
	MONSTERSTATE _state;
	MONSTERDIRECTION _direction;

	tagMonsterData	_monster;	// 몬스터 정보
	tagPixel		_pixel;		// 몬스터 픽셀충돌
	tagCollisionRc  _collision; // 몬스터 렉트충돌
	
	int  _maxHp;
	int  _curHp;
	int  _curAtt;
 	int  _dropExp;
	int  _dropLufia;
	int  _dropItemIndex;

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
	virtual void setCollisionRange(void);
	virtual void drawEffect(void);
	void draw(void);
	void animation(void);
	void setDirection(void);
	void pixelCollision();
	bool pixelColorCheck(int getPixelX, int getPixelY);


	// get/set
	MONSTERSTATE&	  getState()			  { return _state; }
	MONSTERDIRECTION& getDirection()		  { return _direction; }

	tagMonsterData&	  getMonster()			  { return _monster; }
	tagPixel&		  getMonsterPixel()		  { return _pixel; }
	tagCollisionRc&   getMonsterCollisionRc() { return _collision; }

	void setHp(int hp) { _curHp-=hp; }
	int	 getHp()	   { return _curHp; }
	int	 getMaxHp()	   { return _maxHp; }
	int  getAtt()	   { return _curAtt; }
	int  getExp()	   { return _dropExp; }
	int  getLufia()	   { return _dropLufia; }
	int  getItem()	   { return _dropItemIndex; }

	float timeCount = 0.0f;
};




