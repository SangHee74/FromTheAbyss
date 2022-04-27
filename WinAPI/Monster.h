#pragma once
#include "GameNode.h"

enum class MONSTERDIRECTION
{
	UP, DOWN, LEFT, RIGHT
};

enum class MONSTERSTATE
{
	IDLE, MOVE, DEF, DEAD, ATK
};

 struct tagMonsterData
{
	RECT	moveRc;
	RECT	recognitionRc;		// �÷��̾ ���� �ٰ��� �ν� ����
	int		movePosX, movePosY; // rc������Ʈ
	int		frameX, frameY;
	int		speed;
	int		distance;
	float	angle;				// �÷��̾ ���� �ٰ��� ����
	float	rndTimeCount;
	float	worldTimeCount;
	float	atkCoolTime;		// ���� ���� �ֱ�
	bool	playerCheck;		// �÷��̾ �ν��ߴ��� ����
	Image*  image;				// ���� �̹���
};

class Monster : public GameNode
{
protected:
	MONSTERSTATE _state;
	MONSTERDIRECTION _direction;

	//tagMonsterData	_monster;	// ���� ����
	tagPixel		_pixel;		// ���� �ȼ��浹
	tagCollisionRc  _collision; // ���� ��Ʈ�浹
	
	int		_maxHp;
	int		_curHp;
	int		_curAtt;
 	int		_dropExp;
	int		_dropLufia;
	int		_dropItemIndex;

	RECT	_moveRc;
	RECT	_recognitionRc;		// �÷��̾ ���� �ٰ��� �ν� ����
	int		_movePosX;
	int 	_movePosY;			// rc������Ʈ
	int		_frameX;
	int		_frameY;			// rc-frame������Ʈ
	int		_atkRange;			// ���ݻ�Ÿ�
	float	_speed;				// �÷��̾� �i�ƿ���
	float	_distance;			
	float	_angle;				
	float	_rndTimeCount;		// �� ��ü�� ������ ���� �ð� �ٸ��� 
	float	_worldTimeCount;
	float	_atkCoolTime;		// ���� ���� ���·� ��ȯ �ֱ�
	float	_atkTimeCount;		// ���� ��� ���·� ��ȯ �ֱ�
	bool	_playerCheck;		// �÷��̾ �ν��ߴ��� ����
	bool	_atkStart;			// �÷��̾�� �����Ÿ� �����϶� ����
	bool	_backToPos;			// �νĹ����� ������ ������ ��ȯ��ġ��
	Image*  _image;				// ���� �̹���

	int _count;

	// 
	int _stateChangeTime;		// ���� �ð� �̻��̸� ���º���

public:
	Monster(void);
	virtual ~Monster() {};

	HRESULT init(void);
	HRESULT init(POINT position);
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void setDirection(void);		// �÷��̾� �ٶ󺸱�
	virtual void move(void);
	virtual void attack(void);
	virtual void imgUpdate(void);
	virtual void rectUpdate(void);
	virtual void draw(void);

	// �̵����� �Լ� 
	void monsterMoveToPlayer(void); // �÷��̾� ����->�������� ��ȯ
	void backToInitialPos(void);    // ���� �νĹ��� üũ->����� ��ȯ 
	void pixelCollision(void);		// �ȼ� �浹
	bool pixelColorCheck(int getPixelX, int getPixelY);

	void changeState(); // �����ð� �ֱ�� ���� ���� ����

	// get/set
	MONSTERSTATE&	  getState()			  { return _state; }
	MONSTERDIRECTION& getDirection()		  { return _direction; }

	//tagMonsterData&	  getMonster()			  { return _monster; }
	tagPixel&		  getMonsterPixel()		  { return _pixel; }
	tagCollisionRc&   getMonsterCollisionRc() { return _collision; }

	void setHp(int hp) { _curHp-=hp; }
	int	 getHp()	   { return _curHp; }
	int	 getMaxHp()	   { return _maxHp; }
	int  getAtt()	   { return _curAtt; }
	int  getExp()	   { return _dropExp; }
	int  getLufia()	   { return _dropLufia; }
	int  getItem()	   { return _dropItemIndex; }

	RECT&  getMoveRc()		 { return _moveRc; }
	RECT&  getReconitionRc() { return _recognitionRc; }
	int&   getMovePosX()	 { return _movePosX; }
	int&   getMovePosY()	 { return _movePosY; }
	int&   getFrameX()		 { return _frameX; }
	int&   getFrameY()		 { return _frameY; }
	float& getSpeed()		 { return _speed; }
	float& getDistance()	 { return _distance; }
	float& getAngle()		 { return _angle; }
	bool&  getPlayerCheck()  { return _playerCheck; }
	bool&  getAtkStart()  { return _atkStart; }
	Image* getImage()		 { return _image; }

	float timeCount = 0.0f;
};




