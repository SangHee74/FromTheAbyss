#pragma once
#include "ProgressBar.h"

enum PLAYERTYPE
{
	ONE//,TWO,THREE,FORE
};

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
	SKILL1,SKILL2,SKILL3
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

class Player :public GameNode
{
private:
	char _strName[128];
	PLAYERTYPE _playerType;
	WEAPONTYPE _weaponType;
	PLAYERDIRECTION _playerDirection;
	PLAYERSTATE _playerState; // �÷��̾� ����
	tagPlayerStatus _status;
	Image* _faceImg;
	Image* _weaponImg;
	Image* _playerImg;


	int _abyss;
	int _stage;

	POINT _pos;
	int w, h; // �ӽ�
	int _frameX;
	int _frameY;

	RECT _rcPlayer;
	RECT _rcCamera;

	bool _isLeft;
	bool _isLive;
	bool _isRunnig;
	bool _isAttacking;
	bool _isHit;
	bool _isFrameImg;
	

	int _speed;
	int _tempFrameY; // �ӽ�
	int _tempFrameX;
	int _tempCount;

public: // ��������
	STATE* _pStatePattern; // �������� �̳�(����) 

#ifdef STATEPATTERN

	void setState(PLAYERSTATE state);
	void stateUpdate2();
	void stateRender();
	//PLAYERSTATE getPlayerState() { return this->_playerState; }

#else
	// �������� �Լ�(�ൿ)
	void setPlayerState(STATE* state);

	void stateInit();
	void stateUpdate();
	void stateRelease();

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

	// �ּҰ� ������ �ټ� ���ÿ�
	//int& getPosY() { return _posY; }

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

	bool getIsLeft() { return this->_isLeft; }
	void setIsLeft(bool state) { _isLeft = state; }
	bool getIsLive() { return this->_isLive; }
	void setIsLive(bool state) { _isLive = state; }
	bool getIsRunning() { return this->_isRunnig; }
	void setIsRunning(bool state) { _isRunnig = state; }
	bool getIsAttacking() { return this->_isAttacking; }
	void setIsAttacking(bool state) { _isAttacking = state; }
	bool getIsHit() { return this->_isHit; }
	void setIsHit(bool state) { _isHit = state; }
	bool getIsFrameImg() { return this->_isFrameImg; }
	void setIsFrameImg(bool state) { _isFrameImg = state; }


};

