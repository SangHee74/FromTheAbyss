#pragma once
#include "ProgressBar.h"

enum PLAYERTYPE
{
	ONE//,TWO,THREE,FORE
};

enum class WEAPONTYPE
{
	SWORD, AX //, SPEAR, WAND, BOW
};

enum class PLAYERDIRECTION
{
	UP, DOWN, LEFT, RIGHT,
	LEFTUP, RIGHTUP, LEFTDOWN, RIGHTDOWN
};

enum class PLAYERSTATE
{
	IDLE, MOVE, ATT, BEHIT, DEAD
};

struct tagInventory
{

};

struct tagEquip
{

};

struct tagPlayerStatus
{
	int curHp ;
	int curSp ;
	int curExp;
	int maxHp;
	int maxSp;
	int maxExp;

	int lv;
	int gold;
	int iAtt; //물공
	int iDef; //물방
	int iInt; //마공
	int iMen; //마방
	int iAgi; //속도
	int iLuk; //크리

	tagEquip tEquip;
	tagInventory tInven;
};

class STATE;

class Player :public GameNode
{
private:
	char _strName[128];
	PLAYERTYPE _playerType;
	WEAPONTYPE _weaponType;
	PLAYERDIRECTION _playerDirection;
	PLAYERSTATE _playerState; // 플레이어 상태
	STATE* _pStatePattern; // 상태패턴 이넘(상태) 
	tagPlayerStatus _status;
	Image* _faceImg;
	Image* _weaponImg;


	int _abyss;
	int _stage;

	POINT _pos;
	int w, h; // 임시
	int _frameX;
	int _frameY;

	RECT _rcPlayer;
	RECT _rcCamera;

	bool _isLeft;
	bool _isLive;
	bool _isRunnig;
	bool _isAttacking;

	int _speed;
	int _tempFrameY; // 임시
	int _tempFrameX;
	int _tempCount;


public:
	Player() {}
	~Player() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Image getPlayerSumImg() { return *(this->_faceImg); }
	tagPlayerStatus getStatus() { return this->_status; }
	//void setStatus(tagPlayerStatus status,int value) { status.curExp = value;	}
	//오퍼레이터 필요

	void setPlayerDirection(PLAYERDIRECTION state)
	{
		_playerDirection = state;
	}

	// 상태패턴
	void setState(PLAYERSTATE state);
	void stateUpdate();
	void stateRender();
	//PLAYERSTATE getPlayerState() { return this->_playerState; }
	//void setPlayerState(STATE* state);

	RECT getPlayerRect();
	void setCameraRect(RECT rc);

	float getPlayerPosX();
	float getPlayerPosY();
	void setPlayerPosX(float x);
	void setPlayerPosY(float y);
	int getPlayerFrameX() { return this->_frameX; }
	int getPlayerFrameY() { return this->_frameX; }
	void setPlayerFrameX(int x) { _frameX = x; }
	void setPlayerFrameY(int y) { _frameX = y; }

	int getAbyss() { return this->_abyss; }
	int getStage() { return this->_stage; }
	void setAbyss(int num);
	void setStage(int num);

	bool getIsLeft() { return this->_isLeft; }
	void setIsLeft(bool state) { _isLeft = state; }
	bool getIsLive() { return this->_isLive; }
	void setIsLive(bool state) { _isLive = state; }

	// 상태패턴 함수(행동)
	void idle();
	void move();
	void attack();
	void beHit();
};

