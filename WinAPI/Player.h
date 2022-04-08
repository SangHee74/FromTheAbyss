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
	// -> ���డ���� �ܰ�
	// int AbyssHall[abyss][stage];
	int abyss; // ���尡�� ���
	int stage; // ���尡�� �������� 
	int block; // Ŭ������ ��

	// �� ���� ����� ���� �� ��� �غ� ��.
	// 0000 0000 �������� �� 0~3
	// 0001 0000 �������� �� 4~7
	// 0010 0000 �������� �� 8~11
	// 0100 0000 �������� �� 12~15

	// 1000 0001 1�� ����
	// 1000 0010 2�� ����
	bitset<6> blockCheck[8 * 4]; // 8��� 4��������
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
	int iAtt; //����
	int iDef; //����
	int iInt; //����
	int iMen; //����
	int iAgi; //�ӵ�
	int iLuk; //ũ��
	int iStatusPoint; 
	int lufia; //������

	tagEquip tEquip;
	tagInventory tInven;
};

struct tagPlayerData
{
	RECT	moveRc;
	RECT	drawRc;
	int		movePosX, movePosY; // rc������Ʈ
	int		drawPosX, drawPosY; // �̹��� ����(LT)
	int		frameX, frameY;
	int		width, height;   // �̹��� ���� ���� �� ���μ���
	int		speed;
	Image*  face;	 // �÷��̾� �� �̹���
	Image*  image;	 // �÷��̾� �̹���
};

// player Weapon
struct tagWeaponData
{
	WEAPONTYPE type;			  // �÷��̾� ����Ÿ��
	RECT moveRc;
	RECT drawRc;
	int movePosX, movePosY;		  // �̵� ��ǥ
	int drawPosX, drawPosY;		  // ���� ��ǥ
	int frameX, frameY;
	int width, height;			  // �̹��� ���� ���� �� ���μ���
	Image* image;
};

// camera 
struct tagCamera
{
	RECT rc;
	int playerLeft, playerTop;
	int weaponLeft, weaponTop;
};

// �ȼ��浹
struct tagPixel
{
	int probeUp;
	int probeDown;
	int probeLeft;
	int probeRight;
};

// ��Ʈ�浹
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

class STATE;  // ��������(��ȣ����-���漱��)

class Player :public GameNode
{
private:
	PLAYERSTATE		_state;		// �÷��̾� ����
	PLAYERDIRECTION _direction; // �÷��̾� ����
	
	tagAbyssData	_abyss;		// ���� ����
	tagPlayerStatus _status;	// �÷��̾� ����
	tagPlayerData	_player;	// �÷��̾� ����
	tagWeaponData	_weapon;	// �÷��̾� ����+����Ʈ
	tagCamera		_camera;	// �÷��̾� ī�޶�
	tagPixel		_pixel;		// �÷��̾� �ȼ��浹
	tagCollisionRc  _collision; // �÷��̾� ��Ʈ�浹

	// ������ �ӽ� ����
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
	// ��������
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


		
	//�ӽ�
	int getItemNum() { return itemNum; }

};

