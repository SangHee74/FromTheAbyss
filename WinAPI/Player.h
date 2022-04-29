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
	// -> ���డ���� �ܰ�
	// int AbyssHall[abyss][stage];
	int abyss; // ���尡�� ���
	int stage; // ���尡�� �������� 
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
	int iAtk; //����
	int iDef; //����
	int iInt; //����
	int iMen; //����
	int iAgi; //�ӵ�
	int iLuk; //ũ��
	int iStatusPoint; 
	int lufia; //������
};
	
struct tagPlayerData
{
	RECT	moveRc;
	RECT	drawRc;
	int		movePosX, movePosY; // rc������Ʈ
	int		drawPosX, drawPosY; // �̹��� ����(LeftTop)
	int		frameX, frameY;
	int		width, height;      // �̹��� ���� ���� �� ���μ���
	int		speed;
	Image*  face;				// �÷��̾� �� �̹���
	Image*  image;				// �÷��̾� �̹���
};

// player Weapon
struct tagWeaponData
{
	WEAPONTYPE type;			// �÷��̾� ����Ÿ��
	RECT moveRc;
	RECT drawRc;
	int movePosX, movePosY;		// �̵� ��ǥ
	int drawPosX, drawPosY;		// ���� ��ǥ
	int frameX, frameY;
	int width, height;			// �̹��� ���� ���� �� ���μ���
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

class STATE;  // ��������(��ȣ����-���漱��)

class Player :public GameNode
{
private:

	char name[128];
	string _name;

	PLAYERSTATE		_state;		// �÷��̾� ����
	PLAYERDIRECTION _direction; // �÷��̾� ����
	
	tagAbyssData	_abyss;		// ���� ����
	tagPlayerStatus _status;	// �÷��̾� ����
	tagPlayerData	_player;	// �÷��̾� ����
	tagWeaponData	_weapon;	// �÷��̾� ����+����Ʈ
	tagCamera		_camera;	// �÷��̾� ī�޶�
	tagPixel		_pixel;		// �÷��̾� �ȼ��浹
	tagCollisionRc  _collision; // �÷��̾� ��Ʈ�浹

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
	// �κ��丮
	//Inventory* _inven;
	
	// ������ �ӽ� ����
	int itemNum;

public:
	// ��������
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
		
	//�ӽ�
	int getItemNum() { return itemNum; }

};

