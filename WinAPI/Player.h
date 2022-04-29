#pragma once
#include "GameNode.h"
//#include "Inventory.h"

#pragma region playerEnumStruct

enum PLAYERNUMBER
{
	PLAYER_ONE, PLAYER_TWO, PLAYER_THREE, PLAYER_END
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
	ATK_ONEHANDCOMBO, ATK_TWOHANDCOMBO,
	SKILL_SOULCAPTURE,SKILL_SPEARSTRIKE
	//SKILL1, SKILL2, SKILL3
};

// player data
struct tagAbyssData
{
	// -> 진행가능한 단계
	// int AbyssHall[abyss][stage];
	int abyss; // 입장가능 어비스
	int stage; // 입장가능 스테이지 
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
	int iAtk; //물공
	int iDef; //물방
	int iInt; //마공
	int iMen; //마방
	int iAgi; //속도
	int iLuk; //크리
	int iStatusPoint; 
	int lufia; //소지금
};
	
struct tagPlayerData
{
	RECT	moveRc;
	RECT	drawRc;
	int		movePosX, movePosY; // rc업데이트
	int		drawPosX, drawPosY; // 이미지 렌더(LeftTop)
	int		frameX, frameY;
	int		width, height;      // 이미지 마다 맞춰 줄 가로세로
	int		speed;
	Image*  face;				// 플레이어 얼굴 이미지
	Image*  image;				// 플레이어 이미지
};

// player Weapon
struct tagWeaponData
{
	WEAPONTYPE type;			// 플레이어 무기타입
	RECT moveRc;
	RECT drawRc;
	int movePosX, movePosY;		// 이동 좌표
	int drawPosX, drawPosY;		// 렌더 좌표
	int frameX, frameY;
	int width, height;			// 이미지 마다 맞춰 줄 가로세로
	Image* image;
};

// camera 
struct tagCamera
{
	RECT rc;
	int playerLeft, playerTop;
	int weaponLeft, weaponTop;
	int effectLeft, effectTop;
};

// 픽셀충돌
struct tagPixel
{
	int probeUp;
	int probeDown;
	int probeLeft;
	int probeRight;

	// 몬스터용 조정값
	struct tagDirectionSpace
	{
		int LR;
		int TB;
	}; 
	tagDirectionSpace space;
};

// 렉트충돌
struct tagCollisionRc
{
	// 충돌 범위 조정 
	RECT defRc;
	int defWidth;
	int defHeight;

	Image* atkEffImg; // notFrameImg
	Image* atkEffectImg;
	RECT atkRc;
	int atkPosX;
	int atkPosY;
	int atkWidth;
	int atkHeight;
	int atkEffFrameX;
	int atkEffFrameY;

	bool atkRangeUpdate;
};

#pragma endregion

class STATE;  // 상태패턴(상호참조-전방선언)

class Player :public GameNode
{
private:

	char name[128];
	string _name;

	PLAYERSTATE		_state;		// 플레이어 상태
	PLAYERDIRECTION _direction; // 플레이어 방향
	
	tagAbyssData	_abyss;		// 던전 정보
	tagPlayerStatus _status;	// 플레이어 스탯
	tagPlayerData	_player;	// 플레이어 정보
	tagWeaponData	_weapon;	// 플레이어 무기+이펙트
	tagCamera		_camera;	// 플레이어 카메라
	tagPixel		_pixel;		// 플레이어 픽셀충돌
	tagCollisionRc  _collision; // 플레이어 렉트충돌

	// 1 = true;
	// 000001 : isLeft		// 0
	// 000010 :	isRunnig	// 1
	// 000100 : isAttack	// 2
	// 001000 : isDefense 	// 3
	// 010000 : isLive		// 4
	// 100000 : render_isweaponTop(playerDirectionDown) // 5
	bitset<6> _isStateCheck;

	int _shadowAlpha;
	
private:
	// 인벤토리
	//Inventory* _inven;
	
	// 아이템 임시 변수
	int itemNum;

public:
	// 상태패턴
	STATE* _pStatePatkern; 
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
	//Inventory*		 getInventory()				 { return _inven; }
	PLAYERSTATE&	 getState()					 { return _state; }
	PLAYERDIRECTION& getDirection()				 { return _direction; }
	
	bitset<6>&		 getIsStateCheck()			 { return _isStateCheck; }
	tagAbyssData&	 getPlayerAbyss()			 { return _abyss; }
	tagPlayerStatus& getPlayerStatus()			 { return _status; }
	tagPlayerData&	 getPlayer()				 { return _player; }
	tagWeaponData&   getPlayerWeapon()			 { return _weapon; }
	tagCamera&		 getPlayerCAM()				 { return _camera; }
	tagPixel&		 getPlayerPixel()			 { return _pixel; }
	tagCollisionRc&  getPlayerCollisionRc()		 { return _collision; }
	//char			 getName()					 { return name[128];}
	//string		 getName2()					 { return _name;}

	// function
	void playerInStageSetting(int playerX, int playerY, PLAYERDIRECTION direction);
	void weaponinStageSetting();
	void playerAttSetting(bitset<3> combo);
	void playerAttSetting() { _collision.atkRc = { 0,0,0,0 };  }
	void drawEffect();
	int  playerRandomDamage();
		
	//임시
	int getItemNum() { return itemNum; }

};

