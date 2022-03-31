#pragma once
#include "ProgressBar.h"

enum class WEAPONTYPE
{
	SWORD, AX //, SPEAR, WAND
};

enum class PLAYERDIRECTION
{
	UP, DOWN, LEFT, RIGHT,
	LEFTUP, RIGHTUP, LEFTDOWN, RIGHTDOWN
};

enum class PLAYERSTATE
{
	IDLE, MOVE, BEHIT, DEAD,
	ATT1, ATT2, ATT3,
	SKILL1, SKILL2, SKILL3
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
	int iAtt; //����
	int iDef; //����
	int iInt; //����
	int iMen; //����
	int iAgi; //�ӵ�
	int iLuk; //ũ��

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

	//RECT effectRc;
};

class Player :public GameNode
{
private:
	char _strName[128];
	WEAPONTYPE _weaponType; // �÷��̾� ����Ÿ��
	PLAYERDIRECTION _playerDirection; // �÷��̾� ����
	PLAYERSTATE _playerState; // �÷��̾� ����
	tagPlayerStatus _status; // �÷��̾� ����
	tagWeaponData _playerWeapon; // �÷��̾� ����+����Ʈ
	Image* _faceImg;   // �÷��̾� �� �̹���
	Image* _weaponimage; // ����
	Image* _playerImg; // �÷��̾�


	int _abyss;
	int _stage;

	POINT _pos;
	RECT _rcPlayer;
	int _frameX;
	int _frameY;
	int _width; // �̹������� ������ ���μ���
	int _height;

	RECT _rcCamera;

	// 1 = true;
	// 000001 : isLeft		// 0
	// 000010 :	isRunnig	// 1
	// 000100 : isAttack	// 2
	// 001000 : isHit		// 3
	// 010000 : isLive		// 4
	// 100000 : playerImage = FrameImage // 5
	bitset<6> _isStateCheck;
	bitset<6> getIsCheck() { return this->_isStateCheck; }
	unsigned int getIsCheck(int value) { return this->_isStateCheck[value]; }



	int _speed;
	int _tempFrameY; // �ӽ�
	int _tempFrameX;
	int _tempCount;


#ifdef STATEPATTERN

	void setState(PLAYERSTATE state);
	void stateUpdate2();
	void stateRender();
	//PLAYERSTATE getPlayerState() { return this->_playerState; }

#else
public:
	STATE* _pStatePattern; // �������� 
	void setPlayerState(STATE* state); // ���� ������Ʈ
	void stateUpdate(); // �������� ������Ʈ



#endif // STATEPATTERN

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
	//���۷����� �ʿ�

	PLAYERDIRECTION getPlayerDirection() { return this->_playerDirection; }
	int getPlayerDirectionWhitInt() { return static_cast<int>(this->_playerDirection); }
	void setPlayerDirection(PLAYERDIRECTION state) { _playerDirection = state; }

	RECT getPlayerRect() { return this->getPlayerRect(); }
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
	Image* setPlayerImg(Image* image) { return this->_playerImg; }

	int getAbyss() { return this->_abyss; }
	int getStage() { return this->_stage; }
	void setAbyss(int num);
	void setStage(int num);


};

