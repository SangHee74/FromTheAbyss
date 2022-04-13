#include "Stdafx.h"
#include "BossMonster.h"


Minotaur::Minotaur()
{
	_curHp = 300;
	_curAtt = 30;
	_dropExp = 50;
	_dropLufia = RND->getFromIntTo(80,100);
	_dropItemIndex = 0; // 임시

	_state = MONSTERSTATE::IDLE;
	_direction = MONSTERDIRECTION::DOWN;
	_monster.speed = 2;
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;
	_monster.image = IMG("mino_idle");

	_collision.defRc = CollisionAreaResizing(_monster.moveRc, 40, 40);

}


void Minotaur::move()
{
	// 탐색

	// 멈춤

	// 피격렉트 세팅
}


// 플레이어 피격 범위가 인식범위 안에 들어왔을때
// ㄴ 스테이지 에서 조건 맞추기 
void Minotaur::attack()
{
	_state = MONSTERSTATE::ATT;
	_monster.image = IMG("mino_att");
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;

	int timeCount = 0;

	timeCount++;
	if (timeCount % 60 == 0)
	{
		setAttackRc();
		_monster.frameX++;
		if (_monster.frameX > IMG("mino_att")->getMaxFrameX() && timeCount > 90) // 공격모션 변경 후 일정시간이 지나야 종료
		{
			_state = MONSTERSTATE::IDLE;
			_monster.image = IMG("mino_idle");
			_monster.frameX = 0;
			_monster.frameY = (int)_direction;
		}
	}

	
}

void Minotaur::speedUp()
{
	_monster.speed = 4;
}

void Minotaur::setAttackRc()
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.attPosX = _monster.movePosX;
		_collision.attPosY = _monster.moveRc.top - 20;
		_collision.attWidth = 100;
		_collision.attHeight = 50;


		break;
	case MONSTERDIRECTION::DOWN:
		break;
	case MONSTERDIRECTION::LEFT:
		_collision.attPosX = _monster.moveRc.left - 20;
		_collision.attPosY = _monster.movePosY;
		_collision.attWidth = 50;
		_collision.attHeight = 100;
		break;
	case MONSTERDIRECTION::RIGHT:
		break;

	}

	_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);

}