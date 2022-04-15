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
	ATT_ONEHANDCOMBO, ATT_TWOHANDCOMBO,
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
	int effectLeft, effectTop;
};

// �ȼ��浹
struct tagPixel
{
	int probeUp;
	int probeDown;
	int probeLeft;
	int probeRight;

	// ���Ϳ� ������
	struct tagDirectionSpace
	{
		int LR;
		int TB;
	}; 
	tagDirectionSpace space;
};

// ��Ʈ�浹
struct tagCollisionRc
{
	// �浹 ���� ���� 
	RECT defRc;
	int defWidth;
	int defHeight;

	Image* attEffectImg;
	RECT attRc;
	int attPosX;
	int attPosY;
	int attWidth;
	int attHeight;
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
	// 001000 : isDefense 	// 3
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
	PLAYERSTATE&	 getState()						 { return _state; }
	PLAYERDIRECTION& getDirection()				 { return _direction; }
	
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
	void weaponinStageSetting();
	void playerAttSetting(bitset<3> combo);
	int playerRandomDamage();
		
	//�ӽ�
	int getItemNum() { return itemNum; }

};

