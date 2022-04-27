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
	RECT	recognitionRc;		// 플레이어를 향해 다가갈 인식 범위
	int		movePosX, movePosY; // rc업데이트
	int		frameX, frameY;
	int		speed;
	int		distance;
	float	angle;				// 플레이어를 향해 다가갈 각도
	float	rndTimeCount;
	float	worldTimeCount;
	float	atkCoolTime;		// 몬스터 공격 주기
	bool	playerCheck;		// 플레이어를 인식했는지 여부
	Image*  image;				// 몬스터 이미지
};

class Monster : public GameNode
{
protected:
	MONSTERSTATE _state;
	MONSTERDIRECTION _direction;

	//tagMonsterData	_monster;	// 몬스터 정보
	tagPixel		_pixel;		// 몬스터 픽셀충돌
	tagCollisionRc  _collision; // 몬스터 렉트충돌
	
	int		_maxHp;
	int		_curHp;
	int		_curAtt;
 	int		_dropExp;
	int		_dropLufia;
	int		_dropItemIndex;

	RECT	_moveRc;
	RECT	_recognitionRc;		// 플레이어를 향해 다가갈 인식 범위
	int		_movePosX;
	int 	_movePosY;			// rc업데이트
	int		_frameX;
	int		_frameY;			// rc-frame업데이트
	int		_atkRange;			// 공격사거리
	float	_speed;				// 플레이어 쫒아오게
	float	_distance;			
	float	_angle;				
	float	_rndTimeCount;		// 각 객체별 프레임 렌더 시간 다르게 
	float	_worldTimeCount;
	float	_atkCoolTime;		// 몬스터 공격 상태로 변환 주기
	float	_atkTimeCount;		// 몬스터 대기 상태로 변환 주기
	bool	_playerCheck;		// 플레이어를 인식했는지 여부
	bool	_atkStart;			// 플레이어와 일정거리 이하일때 공격
	bool	_backToPos;			// 인식범위와 닿으면 무조건 소환위치로
	Image*  _image;				// 몬스터 이미지

	int _count;

	// 
	int _stateChangeTime;		// 일정 시간 이상이면 상태변경

public:
	Monster(void);
	virtual ~Monster() {};

	HRESULT init(void);
	HRESULT init(POINT position);
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void setDirection(void);		// 플레이어 바라보기
	virtual void move(void);
	virtual void attack(void);
	virtual void imgUpdate(void);
	virtual void rectUpdate(void);
	virtual void draw(void);

	// 이동관련 함수 
	void monsterMoveToPlayer(void); // 플레이어 추적->공격으로 전환
	void backToInitialPos(void);    // 최조 인식범위 체크->벗어나면 귀환 
	void pixelCollision(void);		// 픽셀 충돌
	bool pixelColorCheck(int getPixelX, int getPixelY);

	void changeState(); // 일정시간 주기로 몬스터 상태 변경

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




