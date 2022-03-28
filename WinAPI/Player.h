#pragma once
#include "ProgressBar.h"

enum PLAYERTYPE
{
	ONE=1,TWO,THREE,FORE
};

enum WEAPONTYPE
{
	SWORD, AX, SPEAR, WAND, BOW
};

enum class PLAYERSTATE
{
	IDLE,RUN,ATT,BEHIT,DIE
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

	tagEquip tEquip[3];
	tagInventory tInven;
};


class Player :public GameNode
{
private:
	char _strName[128];
	PLAYERTYPE _playerType;
	WEAPONTYPE _weaponType;
	tagPlayerStatus _status;
	Image* _faceImg;

	int _abyss;
	int _stage;

	ProgressBar* _UIBar;

	POINT _pos;
	int w, h; // �ӽ�

	RECT _rcPlayer;
	RECT _rcCamera;

	bool _isLeft;
	bool _isLive;

	int _speed;

public:
	Player() {}
	~Player() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Image getPlayerSumImg() { return *(this->_faceImg); }
	tagPlayerStatus getStatus() { return this->_status; }
	void setStatus(tagPlayerStatus status) { _status = status;	}

	RECT getPlayerRect();
	void setCameraRect(RECT rc);

	float getPlayerPosX();
	float getPlayerPosY();
	void setPlayerPosX(float x);
	void setPlayerPosY(float y);

	int getAbyss() { return this->_abyss; }
	int getStage() { return this->_stage; }
	void setAbyss(int num);
	void setStage(int num);

	bool getIsLeft() { return this->_isLeft; }
	void setIsLeft(bool state) { _isLeft = state; }
	bool getIsLive() { return this->_isLive; }
	void setIsLive(bool state) { _isLive = state; }
};

