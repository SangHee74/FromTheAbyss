#include "Stdafx.h"
#include "BossMonster.h"


Minotaur::Minotaur()
{
	_curHp = 300;
	_curAtt = 30;
	_dropExp = 50;
	_dropLufia = RND->getFromIntTo(80,100);
	_dropItemIndex = 0; // �ӽ�

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
	// Ž��

	// ����

	// �ǰݷ�Ʈ ����
}


// �÷��̾� �ǰ� ������ �νĹ��� �ȿ� ��������
// �� �������� ���� ���� ���߱� 
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
		if (_monster.frameX > IMG("mino_att")->getMaxFrameX() && timeCount > 90) // ���ݸ�� ���� �� �����ð��� ������ ����
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