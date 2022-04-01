#pragma once
#include "ProgressBar.h"

enum class WEAPONTYPE
{
	SWORD, AX, SPEAR//, WAND
};

enum class PLAYERDIRECTION
{
	UP, DOWN, LEFT, RIGHT,
	LEFTUP, RIGHTUP, LEFTDOWN, RIGHTDOWN
};

enum class PLAYERSTATE
{
	IDLE, MOVE, BEHIT, DEAD,
	ONEHANDCOMBO_ONE, ONEHANDCOMBO_TWO, ONEHANDCOMBO_THREE,
	TWOHANDCOMBO_ONE, TWOHANDCOMBO_TWO,
	SKILL_SOULCAPTURE,SKILL_SPEARSTRIKE
	//SKILL1, SKILL2, SKILL3
};

struct tagInventory
{

};

struct tagEquip
{

};

struct tagPlayerStatus
{
	int curHp;
	int curSp;
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

struct tagWeaponData
{
	float posX, posY;
	RECT rc;
	int frameX;
	int frameY;
};

class Player :public GameNode
{
private:
	char _strName[128];
	WEAPONTYPE _weaponType;			  // 플레이어 무기타입
	PLAYERSTATE _playerState;		  // 플레이어 상태
	PLAYERDIRECTION _playerDirection; // 플레이어 방향
	tagPlayerStatus _status;		  // 플레이어 스탯
	tagWeaponData _playerWeapon;	  // 플레이어 무기+이펙트
	Image* _faceImg;	 // 플레이어 얼굴 이미지
	Image* _playerImage; // 플레이어 이미지
	Image* _weaponimage; // 무기 이미지
	
	int _abyss;
	int _stage;

	// 렌더관련 변수
	int _timeCount;
	int _frameX;
	int _frameY;
	int _width; // 이미지 마다 맞춰 줄 가로세로
	int _height;
	int _speed;

	// 위치
	POINT _pos;
	RECT _rcPlayer;

	// 카메라 관련 
	RECT _rcCamera;
	float _left, _top;			   // 플레이어 용
	float _weaponLeft, _weaponTop; // 무기 용

	// 1 = true;
	// 000001 : isLeft		// 0
	// 000010 :	isRunnig	// 1
	// 000100 : isAttack	// 2
	// 001000 : isHit		// 3
	// 010000 : isLive		// 4
	// 100000 : render_weaponTop(playerDirectionDown) // 5
	bitset<6> _isStateCheck;



public:
	// 상태패턴
	STATE* _pStatePattern; 
	void setPlayerState(STATE* state); 
	void stateUpdate(); 
	void stateRender(); 

public:
	Player() {}
	~Player() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// 상태패턴용 겟셋 =====================

	RECT& getPRect() { return _rcPlayer; }
	RECT& getCRect() { return _rcCamera; }
	POINT& getPPos() { return _pos; }
	int& getPFrameX() { return _frameX; }
	int& getPFrameY() { return _frameY; }
	Image* getPImg() { return _playerImage; }
	Image* getWImg() { return _weaponimage; }
	bitset<6>& getPState() { return _isStateCheck; }


	//=====================================

	Image getPlayerSumImg() { return *(this->_faceImg); }
	tagPlayerStatus getStatus() { return this->_status; }
	//void setStatus(tagPlayerStatus status,int value) { status.curExp = value;	}
	//오퍼레이터 필요

	PLAYERDIRECTION getPlayerDirection() { return this->_playerDirection; }
	int getPlayerDirectionWhitInt() { return static_cast<int>(this->_playerDirection); }
	void setPlayerDirection(PLAYERDIRECTION state) { _playerDirection = state; }

	RECT getPlayerRect() { return _rcPlayer; }
	void setCameraRect(RECT rc);

	int getPlayerPosX() { return this->_pos.x; }
	int getPlayerPosY() { return this->_pos.y; }
	void setPlayerPosX(float x) { _pos.x = x; }
	void setPlayerPosY(float y) { _pos.y = y; }
	int getPlayerFrameX() { return this->_frameX; }
	int getPlayerFrameY() { return this->_frameX; }
	void setPlayerFrameX(int x) { _frameX = x; }
	void setPlayerFrameY(int y) { _frameX = y; }
	int getPlayerSpeed() { return this->_speed; }
	WEAPONTYPE getPlayerWeapon() { return this->_weaponType; }
	void setPlayerWeapon(tagWeaponData value) { _playerWeapon = value; }
	Image* setPlayerWeaponImg(Image* image) { return this->_weaponimage; }
	Image* setPlayerImg(Image* image) { return this->_playerImage; }

	bitset<6> getIsStateCheck() { return this->_isStateCheck; }
	unsigned int getIsStateCheck(int value) { return this->_isStateCheck[value]; }

	int getAbyss() { return this->_abyss; }
	int getStage() { return this->_stage; }
	void setAbyss(int num);
	void setStage(int num);
	void inStageSetting();

	
};

