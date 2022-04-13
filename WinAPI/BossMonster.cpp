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

	_attTimeCount = 0;
	setCollisionRange();

	// ���������� �νĹ����� ���� ��κ�. 
	_monster.recognitionRc = RectMakeCenter
	(DATAMANAGER->getMapData().map->getWidth()*0.5, DATAMANAGER->getMapData().map->getHeight()*0.5, 1690, 1060);
}


void Minotaur::move()
{
	if (_monster.playerCheck)
	{
		//cout << "�ν���! ������ ����" << endl;
		//cout << "�÷��̾� ��ǥ X : " << DATAMANAGER->getPlayer()->getPlayer().drawPosX << " , Y : " << DATAMANAGER->getPlayer()->getPlayer().drawPosY<< endl;
		//monsterMovetoPlayer();


		
		// �� �����ϸ� ���ݻ��·� ����
		if ( _monster.attCoolTime >= 180.0f) _state = MONSTERSTATE::ATT;
	}	
	else
	{
		// �÷��̾ �ν����� ���� ���
		// �������� �̵��Ѵ�. 

	}

	// ������ �ƴϸ�(������) ��Ÿ�� 
	if (_state != MONSTERSTATE::ATT) _monster.attCoolTime++;

}


// �÷��̾� �ǰ� ������ �νĹ��� �ȿ� ��������
void Minotaur::attack()
{
	_monster.image = IMG("mino_attack");
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;
	_collision.attWidth = _collision.attHeight = 0;

	_attTimeCount++;
	cout << "_attTimeCount : " << _attTimeCount << endl;

	if (_attTimeCount >= 120)
	{
		_monster.frameX++;
		// ���ݷ�Ʈ ���� 
		setCollisionRange();
	
		if (_monster.frameX >= IMG("mino_attack")->getMaxFrameX() 
			&& _attTimeCount >= 240) // ���ݸ�� ���� �� �����ð��� ������
		{
			_attTimeCount = 0;
			_state = MONSTERSTATE::IDLE; // ��������
			_monster.attCoolTime = 0;
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

void Minotaur::setCollisionRange()
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP: // ���⳪��
		_collision.defWidth = 185;
		_collision.defHeight = 168;

		_collision.attPosX = _monster.movePosX;
		_collision.attPosY = _collision.defRc.top-35;
		_collision.attWidth = 300;
		_collision.attHeight = 80;
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.defWidth = 185;
		_collision.defHeight = 168;

		_collision.attPosX = _monster.movePosX;
		_collision.attPosY = _collision.defRc.bottom + 35;
		_collision.attWidth = 300;
		_collision.attHeight = 80;

		break;
	case MONSTERDIRECTION::LEFT: // ���⳪��
		_collision.defWidth = 140;
		_collision.defHeight = 168;

		_collision.attPosX = _collision.defRc.left - 35;
		_collision.attPosY = _monster.movePosY;
		_collision.attWidth = 80;
		_collision.attHeight = 300;
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;

		_collision.attPosX = _collision.defRc.right + 35;
		_collision.attPosY = _monster.movePosY;
		_collision.attWidth = 80;
		_collision.attHeight = 300;
		break;
	}

	if(_state != MONSTERSTATE::ATT) 	_collision.attWidth = _collision.attHeight = 0;
	_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
	_collision.defRc = RectMakeCenter(_monster.movePosX, _monster.movePosY - 30, _collision.defWidth, _collision.defHeight);

}

void Minotaur::monsterMovetoPlayer()
{
	// �������� �̵�
	float lerpPercentage = 0;
	float time = 1.0f;
	float speed = TIMEMANAGER->getElapsedTime() * time;
	//			float speed = DATAMANAGER->getPlayer()->getPlayer().speed*1.2;
	lerpPercentage += speed;

	POINT start = { _monster.movePosX, _monster.movePosY };
	POINT end = { DATAMANAGER->getPlayer()->getPlayer().drawPosX, DATAMANAGER->getPlayer()->getPlayer().drawPosY };

	_monster.moveRc = RectMakeCenter(
		lerp(start, end, lerpPercentage).x, lerp(start, end, lerpPercentage).y,
		_monster.image->getFrameWidth(),
		_monster.image->getFrameWidth());

	//cout << "�������� �̵���Ʈ L : " << _monster.moveRc.left << ", T : " << _monster.moveRc.top << endl;
}


