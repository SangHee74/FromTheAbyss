#pragma once
#include "GameNode.h"

enum PLAYERNUMBER
{
	PLAYER_NONE, PLAYER_ONE, PLAYER_TWO, PLAYER_THREE, PLAYER_END
};

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
	IDLE, MOVE, DEF, DEAD,
	ATT_ONEHANDCOMBO, ATT_ONEHANDCOMBO_TWO, ATT_ONEHANDCOMBO_THREE,
	ATT_TWOHANDCOMBO_ONE, ATT_TWOHANDCOMBO_TWO,
	SKILL_SOULCAPTURE,SKILL_SPEARSTRIKE
	//SKILL1, SKILL2, SKILL3
};

// item data
struct tagInventory
{

};

struct tagEquip
{

};

// player data
struct tagAbyssData
{
	// -> 진행가능한 단계
	// int AbyssHall[abyss][stage];
	int abyss; // 입장가능 어비스
	int stage; // 입장가능 스테이지 
	int block; // 클리어한 블럭

	// 맵 오픈 방식은 조금 더 고민 해볼 것.
	// 0000 0000 스테이지 블럭 0~3
	// 0001 0000 스테이지 블럭 4~7
	// 0010 0000 스테이지 블럭 8~11
	// 0100 0000 스테이지 블럭 12~15

	// 1000 0001 1블럭 오픈
	// 1000 0010 2블럭 오픈
	bitset<6> blockCheck[8 * 4]; // 8어비스 4스테이지
};

struct tagPlayerStatus
{
	char name[128];
	
	int curHp;
	int curSp;
	int curExp;
	int maxHp;
	int maxSp;
	int maxExp;

	int lv;
	int iAtt; //물공
	int iDef; //물방
	int iInt; //마공
	int iMen; //마방
	int iAgi; //속도
	int iLuk; //크리
	int iStatusPoint; 
	int lufia; //소지금

	tagEquip tEquip;
	tagInventory tInven;
};

struct tagPlayerData
{
	RECT	moveRc;
	RECT	drawRc;
	int		movePosX, movePosY; // rc업데이트
	int		drawPosX, drawPosY; // 이미지 렌더(LT)
	int		frameX, frameY;
	int		width, height;   // 이미지 마다 맞춰 줄 가로세로
	int		speed;
	Image*  face;	 // 플레이어 얼굴 이미지
	Image*  image;	 // 플레이어 이미지
};

// player Weapon
struct tagWeaponData
{
	WEAPONTYPE type;			  // 플레이어 무기타입
	RECT moveRc;
	RECT drawRc;
	int movePosX, movePosY;		  // 이동 좌표
	int drawPosX, drawPosY;		  // 렌더 좌표
	int frameX, frameY;
	int width, height;			  // 이미지 마다 맞춰 줄 가로세로
	Image* image;
};

// camera 
struct tagCamera
{
	RECT rc;
	int playerLeft, playerTop;
	int weaponLeft, weaponTop;
};

// 픽셀충돌
struct tagPixel
{
	int probeUp;
	int probeDown;
	int probeLeft;
	int probeRight;
};

// 렉트충돌
struct tagCollisionRc
{

	RECT defRc;
	RECT attRc;
	int defWidth;
	int defHeight;
	int attPosX;
	int attPosY;
	int attWidth;
	int attHeight;
	Image* attEffectImg;
	int attEffFrameX;
	int attEffFrameY;
};

class STATE;  // 상태패턴(상호참조-전방선언)

class Player :public GameNode
{
private:
	PLAYERSTATE		_state;		// 플레이어 상태
	PLAYERDIRECTION _direction; // 플레이어 방향
	
	tagAbyssData	_abyss;		// 던전 정보
	tagPlayerStatus _status;	// 플레이어 스탯
	tagPlayerData	_player;	// 플레이어 정보
	tagWeaponData	_weapon;	// 플레이어 무기+이펙트
	tagCamera		_camera;	// 플레이어 카메라
	tagPixel		_pixel;		// 플레이어 픽셀충돌
	tagCollisionRc  _collision; // 플레이어 렉트충돌

	// 아이템 임시 변수
	int itemNum;

	// 1 = true;
	// 000001 : isLeft		// 0
	// 000010 :	isRunnig	// 1
	// 000100 : isAttack	// 2
	// 001000 : isHit		// 3
	// 010000 : isLive		// 4
	// 100000 : render_isweaponTop(playerDirectionDown) // 5
	bitset<6> _isStateCheck;

	int _shadowAlpha;
	
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

	// get/set
	PLAYERSTATE getState()						 { return _state; }
	void setState(PLAYERSTATE state)		     { _state = state; }
	
	PLAYERDIRECTION getDirection()				 { return _direction; }
	void setDirection(PLAYERDIRECTION direction) { _direction = direction; }
	
	bitset<6>&		 getIsStateCheck()			 { return _isStateCheck; }
	tagAbyssData&	 getPlayerAbyss()			 { return _abyss; }
	tagPlayerStatus& getPlayerStatus()			 { return _status; }
	tagPlayerData&	 getPlayer()				 { return _player; }
	tagWeaponData&   getPlayerWeapon()			 { return _weapon; }
	tagCamera&		 getPlayerCAM()				 { return _camera; }
	tagPixel&		 getPlayerPixel()			 { return _pixel; }
	tagCollisionRc&  getPlayerCollisionRc()		 { return _collision; }


	// function
	void playerInStageSetting(int playerX, int playerY, PLAYERDIRECTION direction);
	void inStageWeaponSetting();
	void setPlayerCollisionAttRc(int posX, int posY, int width, int height);


		
	//임시
	int getItemNum() { return itemNum; }

};

