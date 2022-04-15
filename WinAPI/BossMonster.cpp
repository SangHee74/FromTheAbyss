#include "Stdafx.h"
#include "BossMonster.h"

// �ʱ�ȭ ���� 
Minotaur::Minotaur()
{
	_maxHp = 300;
	_curHp = 300;
	_curAtt = 10;
	_dropExp = 50;
	_dropLufia = RND->getFromIntTo(80,100);
	_dropItemIndex = 0; // �ӽ�

	_state = MONSTERSTATE::IDLE;
	_direction = MONSTERDIRECTION::DOWN;
	_speed = 5;
	_frameX = 0;
	_frameY = (int)_direction;
	_atkRange = 40;
	_image = IMG("mino_idle");
	_collision.atkEffectImg = IMG("none2");
	_collision.atkEffFrameX = 0;
	_collision.atkEffFrameY = 0;
	_collision.atkPosX = _movePosX;
	_collision.atkPosY = _collision.defRc.bottom + 35;
	_collision.atkWidth = 300;
	_collision.atkHeight = 80;

	_pixel.space.LR = 105;
	_pixel.space.TB = 70;

	_atkTimeCount = 0;

	// �ʱ� ��Ʈ �ʱ�ȭ : �νķ�Ʈ, �̵���Ʈ(�����ӷ���), Ÿ�ݹ�����Ʈ, �ǰݹ�����Ʈ 
	_recognitionRc	 = RectMakeCenter
	(DATAMANAGER->getMapData().map->getWidth()*0.5, DATAMANAGER->getMapData().map->getHeight()*0.5, 1900, 1350);
	
	_collision.defWidth = 185; 	_collision.defHeight = 168;

	_moveRc			 = RectMakeCenter(_movePosX, _movePosY, 30, 30);
	_collision.defRc = RectMakeCenter(_movePosX, _movePosY - 30, _collision.defWidth, _collision.defHeight);
	_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
	


	_atkStart = false;
}


void Minotaur::move()
{
	// �ǰݷ�Ʈ �缳��
	setCollisionDefRange();


	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		_movePosX = DATAMANAGER->getPlayer()->getPlayer().drawPosX + 40;
		_movePosY = DATAMANAGER->getPlayer()->getPlayer().drawPosY + 90;
	}
	
}


// �÷��̾� �ǰ� ������ �νĹ��� �ȿ� ��������
void Minotaur::atkack()
{
	//_atkCoolTime = 0;
	_image = IMG("mino_attack");
	_frameX = 0;
	_frameY = (int)_direction;

	_atkTimeCount += TIMEMANAGER->getElapsedTime();


	if (_atkTimeCount >= 1.0f)
	{
		_frameX++;
		// ���ݷ�Ʈ ���� 
		setCollisionAttRange();
		
		// ����Ʈ �ֱ�� ���缭 ���ݷ�Ʈ �ʱ�ȭ
		if (_atkTimeCount >= 2.5f)
		{
			_collision.atkWidth = _collision.atkHeight = 0;
			_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
		}

		if (_frameX >= IMG("mino_attack")->getMaxFrameX() 
			&& _atkTimeCount >= 4.0f) // ���ݸ�� ���� �� �����ð��� ������
		{
			_atkTimeCount = 0;
			_atkCoolTime = 0;
			_atkStart = false;
			_state = MONSTERSTATE::IDLE; // ��������
			_image = IMG("mino_idle");
			_frameX = 0;
			_frameY = (int)_direction;
		}
	}

}

void Minotaur::speedUp()
{
	_speed = _speed * 1.5;
}

void Minotaur::setCollisionAttRange()
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.atkPosX = _movePosX;
		_collision.atkPosY = _collision.defRc.top-35;
		_collision.atkWidth = 300;
		_collision.atkHeight = 80;
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.atkPosX = _movePosX;
		_collision.atkPosY = _collision.defRc.bottom + 35;
		_collision.atkWidth = 300;
		_collision.atkHeight = 80;

		break;
	case MONSTERDIRECTION::LEFT:
		_collision.atkPosX = _collision.defRc.left - 35;
		_collision.atkPosY = _movePosY;
		_collision.atkWidth = 80;
		_collision.atkHeight = 300;
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.atkPosX = _collision.defRc.right + 35;
		_collision.atkPosY = _movePosY;
		_collision.atkWidth = 80;
		_collision.atkHeight = 300;
		break;
	}

	if(_state != MONSTERSTATE::ATK) 	_collision.atkWidth = _collision.atkHeight = 0;
	_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);

}
void Minotaur::setCollisionDefRange()
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.defWidth = 185;
		_collision.defHeight = 168;
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.defWidth = 185;
		_collision.defHeight = 168;
		break;
	case MONSTERDIRECTION::LEFT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;
		break;
	}

	if (_state != MONSTERSTATE::ATK) 	_collision.atkWidth = _collision.atkHeight = 0;
	_collision.defRc = RectMakeCenter(_movePosX, _movePosY - 30, _collision.defWidth, _collision.defHeight);

}

void Minotaur::drawEffect()
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.atkEffectImg = IMG("eff_bossAttUp");
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.atkEffectImg = IMG("eff_bossAttDown");
		break;
	case MONSTERDIRECTION::LEFT:
		_collision.atkEffectImg = IMG("eff_bossAttLeft");
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.atkEffectImg = IMG("eff_bossAttRight");
		break;
	}

	if (_atkTimeCount >= 1.0f  &&  _state == MONSTERSTATE::ATK)
	{
		_collision.atkEffectImg->render(getMemDC(),
			_collision.atkRc.left - CAM->getScreenRect().left, 
			_collision.atkRc.top - CAM->getScreenRect().top);
	}
	else _collision.atkEffectImg = IMG("none");

			
}




// ������
#if 0 


// �ʱ�ȭ ���� 
Minotaur::Minotaur()
{
	_curHp = 300;
	_curAtt = 10;
	_dropExp = 50;
	_dropLufia = RND->getFromIntTo(80, 100);
	_dropItemIndex = 0; // �ӽ�

	_state = MONSTERSTATE::IDLE;
	_direction = MONSTERDIRECTION::DOWN;
	_monster.speed = 20;
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;
	_monster.image = IMG("mino_idle");
	_collision.atkEffectImg = IMG("none2");
	_collision.atkEffFrameX = 0;
	_collision.atkEffFrameY = 0;
	_collision.atkPosX = _monster.movePosX;
	_collision.atkPosY = _collision.defRc.bottom + 35;
	_collision.atkWidth = 300;
	_collision.atkHeight = 80;

	_atkTimeCount = 0;

	// ���������� �νĹ����� ���� ��κ�.
	// �ʱ� �ǰݷ�Ʈ �ʱ�ȭ
	_collision.defWidth = 185; 	_collision.defHeight = 168;
	_collision.defRc = RectMakeCenter(_monster.movePosX, _monster.movePosY - 30, _collision.defWidth, _collision.defHeight);
	_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);

	_monster.recognitionRc = RectMakeCenter
	(DATAMANAGER->getMapData().map->getWidth()*0.5, DATAMANAGER->getMapData().map->getHeight()*0.5, 1900, 1350);
	//(DATAMANAGER->getMapData().map->getWidth()*0.5, DATAMANAGER->getMapData().map->getHeight()*0.5, 1690, 1060);

	_atkStart = false;
}


void Minotaur::move()
{
	if (_monster.playerCheck)
	{
		monsterMovetoPlayer();



		// �� �����ϸ� ���ݻ��·� ����
		if (_atkStart && _monster.atkCoolTime >= 180.0f && _state != MONSTERSTATE::DEAD)
		{
			_state = MONSTERSTATE::ATK;
		}
	}
	else
	{
		// �÷��̾ �ν����� ���� ���
		// �������� �̵��Ѵ�. 

	}

	// ������ �ƴϸ�(������) ��Ÿ�� 
	if (_state != MONSTERSTATE::ATK) _monster.atkCoolTime++;



}


// �÷��̾� �ǰ� ������ �νĹ��� �ȿ� ��������
void Minotaur::atkack()
{
	_monster.image = IMG("mino_atkack");
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;

	_atkTimeCount++;

	if (_atkTimeCount >= 120)
	{
		_monster.frameX++;
		// ���ݷ�Ʈ ���� 
		setCollisionRange();

		// ����Ʈ �ֱ�� ���缭 ���ݷ�Ʈ �ʱ�ȭ
		if (_atkTimeCount >= 210)
		{
			_collision.atkWidth = _collision.atkHeight = 0;
			_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
		}

		if (_monster.frameX >= IMG("mino_atkack")->getMaxFrameX()
			&& _atkTimeCount >= 240) // ���ݸ�� ���� �� �����ð��� ������
		{
			_atkTimeCount = 0;

			_state = MONSTERSTATE::IDLE; // ��������
			_monster.atkCoolTime = 0;
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

		_collision.atkPosX = _monster.movePosX;
		_collision.atkPosY = _collision.defRc.top - 35;
		_collision.atkWidth = 300;
		_collision.atkHeight = 80;
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.defWidth = 185;
		_collision.defHeight = 168;

		_collision.atkPosX = _monster.movePosX;
		_collision.atkPosY = _collision.defRc.bottom + 35;
		_collision.atkWidth = 300;
		_collision.atkHeight = 80;

		break;
	case MONSTERDIRECTION::LEFT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;

		_collision.atkPosX = _collision.defRc.left - 35;
		_collision.atkPosY = _monster.movePosY;
		_collision.atkWidth = 80;
		_collision.atkHeight = 300;
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;

		_collision.atkPosX = _collision.defRc.right + 35;
		_collision.atkPosY = _monster.movePosY;
		_collision.atkWidth = 80;
		_collision.atkHeight = 300;
		break;
	}

	if (_state != MONSTERSTATE::ATK) 	_collision.atkWidth = _collision.atkHeight = 0;
	_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
	_collision.defRc = RectMakeCenter(_monster.movePosX, _monster.movePosY - 30, _collision.defWidth, _collision.defHeight);

}

void Minotaur::monsterMovetoPlayer()
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		if (_monster.movePosY > DATAMANAGER->getPlayer()->getPlayer().drawPosY + 30)
		{
			_monster.movePosY -= _monster.speed;
		}






		if (_monster.movePosY >= DATAMANAGER->getPlayer()->getPlayer().drawPosY + 50) _atkStart = true;

		break;
	case MONSTERDIRECTION::DOWN:
		if (_monster.movePosY < DATAMANAGER->getPlayer()->getPlayer().drawPosY + 30)
		{
			_monster.movePosY += _monster.speed;
		}
		if (_monster.movePosY <= DATAMANAGER->getPlayer()->getPlayer().drawPosY + 50) _atkStart = true;

		break;
	case MONSTERDIRECTION::LEFT:
		if (_monster.movePosX > DATAMANAGER->getPlayer()->getPlayer().drawPosX + 30)
		{
			_monster.movePosX -= _monster.speed;
		}
		if (_monster.movePosX >= DATAMANAGER->getPlayer()->getPlayer().drawPosX + 60) _atkStart = true;
		break;
	case MONSTERDIRECTION::RIGHT:
		if (_monster.movePosX < DATAMANAGER->getPlayer()->getPlayer().drawPosX + 30)
		{
			_monster.movePosX += _monster.speed;
		}
		if (_monster.movePosX <= DATAMANAGER->getPlayer()->getPlayer().drawPosX + 60) _atkStart = true;

		break;

	}



}

void Minotaur::drawEffect()
{
	_collision.atkEffectImg = IMG("none");

	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.atkEffectImg = IMG("eff_bossAttUp");
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.atkEffectImg = IMG("eff_bossAttDown");
		break;
	case MONSTERDIRECTION::LEFT:
		_collision.atkEffectImg = IMG("eff_bossAttLeft");
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.atkEffectImg = IMG("eff_bossAttRight");
		break;
	}

	if (_state == MONSTERSTATE::ATK)
	{
		_collision.atkEffectImg->render(getMemDC(),
			_collision.atkRc.left - CAM->getScreenRect().left,
			_collision.atkRc.top - CAM->getScreenRect().top);
	}

}

#endif
