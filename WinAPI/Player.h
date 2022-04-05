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
	IDLE, MOVE, HIT, DEAD,
	ONEHANDCOMBO_ONE, ONEHANDCOMBO_TWO, ONEHANDCOMBO_THREE,
	TWOHANDCOMBO_ONE, TWOHANDCOMBO_TWO,
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
	// 001 0000 �������� �� 1~5
	// 010 0000 �������� �� 6~10
	// 100 0001 1�� ����
	// 100 0010 2�� ����
	bitset<6> blockCheck[9 * 4];
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
	int gold;
	int iAtt; //����
	int iDef; //����
	int iInt; //����
	int iMen; //����
	int iAgi; //�ӵ�
	int iLuk; //ũ��

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
	int	probeTop;
	int probeDown;
	int probeLeft;
	int probeRight;
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

	Image* _pixelMap;
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
	
	bitset<6> getIsStateCheck()					 { return this->_isStateCheck; }
	unsigned int getIsStateCheck(int value)		 { return this->_isStateCheck[value]; }

	tagAbyssData&	 getPlayerAbyss()			 { return _abyss; }
	tagPlayerStatus& getPlayerStatus()			 { return _status; }
	tagPlayerData&	 getPlayer()				 { return _player; }
	tagWeaponData&   getPlayerWeapon()			 { return _weapon; }
	tagCamera&		 getPlayerCAM()				 { return _camera; }
	tagPixel&		 getPlayerPixel()			 { return _pixel; }

	// function
	void inStageWeaponSetting();
	void setPixelMap(char* image) { _pixelMap = IMG(image); };
	Image* getMapImage() { return _pixelMap; }

	//�ӽ�
	int getItemNum() { return itemNum; }
};

