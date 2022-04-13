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

	// ���������� �νĹ����� ���� ��κ�. 
	_monster.recognitionRc = RectMakeCenter
	(DATAMANAGER->getMapData().map->getWidth()*0.5, DATAMANAGER->getMapData().map->getHeight()*0.5, 1690, 1060);
}


void Minotaur::move()
{
	if (_monster.playerCheck)
	{
		cout << "�ν���! ������ ����" << endl;
		cout << "�÷��̾� ��ǥ X : " << DATAMANAGER->getPlayer()->getPlayer().drawPosX << " , Y : " << DATAMANAGER->getPlayer()->getPlayer().drawPosY<< endl;
		monsterMovetoPlayer();
	}

	// Ž��
	//cout << "���� �ν� ����: " << _monster.angle*57.32484 << endl;

	if (_monster.playerCheck)
	{
		// �÷��̾ ã�� ���
		// ����(�÷��̾���� �Ÿ�)�� Ÿ�ݷ�Ʈ�� �������� ���̰� �̵��Ѵ�
		// �̵��ϴ� ������ ��,��  ->  ��,�� (�̵��Ÿ��� ª��������� ���� �����̰�?)

		//int tempWidth = _monster.image->getFrameWidth();
		//int tempHeight = _monster.image->getFrameHeight();
		//bool firstMoveUpDown = false;
		
		// ���η� �� �ָ��ִٸ� 
		// ���θ��� ������ �� ���η� �̵�

		//if (tempWidth > tempHeight) firstMoveUpDown = true;

		// ���θ��� �̵�

		//if (firstMoveUpDown)
		{
			//for (; _monster.range <= _monster.image->getFrameWidth()*0.5; )
			{

				//for (; _monster.range <= _monster.image->getFrameHeight()*0.5; )
				{
				//	if (_direction == MONSTERDIRECTION::UP) _monster.movePosY -= _monster.speed;
				//	if (_direction == MONSTERDIRECTION::DOWN) _monster.movePosY += _monster.speed;

				}

				//if (_direction == MONSTERDIRECTION::LEFT) _monster.movePosX -= _monster.speed;
				//if (_direction == MONSTERDIRECTION::RIGHT) _monster.movePosX += _monster.speed;

			}

			// �� �����ϸ� ���ݻ��·� ����
			//_state = MONSTERSTATE::ATT;
		}


		
	}
	else
	{
		// �÷��̾ �ν����� ���� ���
		// �������� �̵��Ѵ�. 

	}



	
}


// �÷��̾� �ǰ� ������ �νĹ��� �ȿ� ��������
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

void Minotaur::setCollisionRange()
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.defWidth = 185;
		_collision.defHeight = 168;

		_collision.attPosX = _monster.movePosX;
		_collision.attPosY = _monster.moveRc.top - 20;
		_collision.attWidth = 100;
		_collision.attHeight = 50;
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.defWidth = 185;
		_collision.defHeight = 168;

		_collision.attPosX = _monster.movePosX;
		_collision.attPosY = _monster.moveRc.top - 20;
		_collision.attWidth = 100;
		_collision.attHeight = 50;

		break;
	case MONSTERDIRECTION::LEFT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;

		_collision.attPosX = _monster.moveRc.left - 20;
		_collision.attPosY = _monster.movePosY;
		_collision.attWidth = 50;
		_collision.attHeight = 100;
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;

		_collision.attPosX = _monster.moveRc.left - 20;
		_collision.attPosY = _monster.movePosY;
		_collision.attWidth = 50;
		_collision.attHeight = 100;
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


