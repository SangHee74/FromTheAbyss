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
	_speed = 200;
	_frameX = 0;
	_frameY = (int)_direction;
	_image = IMG("mino_move");
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

	_atkStart = false;
	_offEff = false;
}

void Minotaur::move()
{
	_image = IMG("mino_move");
	
	Monster::move();
}

void Minotaur::attack()
{
	Monster::attack();

	if (_atkCoolTime > 0) return;

	int temp = 0;

	_atkStart = true;
	_image = IMG("mino_attack");

	timePlus: // �ð� �����ִ� goto

	_atkTimeCount += TIMEMANAGER->getElapsedTime(); // ���� �ð� üũ 

	if (_atkTimeCount >= 0.04f)
	{
		_frameX++;

		_offEff = false;
		imgUpdate(); // direction - attack effect update
	}
	
	if (_atkTimeCount >= 0.06f)
	{
		// ���� ����Ʈ �� ���� ���� �ʱ�ȭ
		_offEff = true;
		imgUpdate();
		_collision.atkWidth = _collision.atkHeight = 0;
		_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);

		if ( _atkTimeCount >= 0.4f) // ���ݸ�� ���� �� �����ð��� ������
		{
			_atkTimeCount = 0.0f;
			_atkCoolTime = 2.5f;
			_state = MONSTERSTATE::IDLE; // ��������
			_image = IMG("mino_idle");
			_frameX = 0;
			cout << "��������" << endl;
		}
	}

	// ���� ���ε� ���ڱ� �̵��ϸ� 
	if (_atkStart);

	
	if (_state == MONSTERSTATE::ATK) cout << "���� �� - ���ݻ��� " << endl;
	if (_state == MONSTERSTATE::MOVE) cout << "���� �� - �̵����� " << endl;
	if (_state == MONSTERSTATE::IDLE) cout << "���� �� - ������ " << endl;


	if (_frameX <= _image->getMaxFrameX())  goto timePlus;

}

void Minotaur::speedUp()
{
	_speed = _speed * 1.5;
}


void Minotaur::imgUpdate()
{
	

	if (_offEff)
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
	}
	else
	{
		_collision.atkEffectImg = IMG("none2");
	}

	if (_state == MONSTERSTATE::DEAD)
	{
		_image = IMG("bossDie");
	}

	Monster::imgUpdate();
}

void Minotaur::rectUpdate()
{
	Monster::rectUpdate();

	switch (_direction)
		{
		case MONSTERDIRECTION::UP:
			_collision.atkPosX = _movePosX;
			_collision.atkPosY = _collision.defRc.top - 25;

			_collision.atkWidth = 300;
			_collision.atkHeight = 80;

			_collision.defWidth = 185;
			_collision.defHeight = 168;
			break;
		case MONSTERDIRECTION::DOWN:
			_collision.atkPosX = _movePosX;
			_collision.atkPosY = _collision.defRc.bottom + 35;

			_collision.atkWidth = 300;
			_collision.atkHeight = 80;

			_collision.defWidth = 185;
			_collision.defHeight = 168;
			break;
		case MONSTERDIRECTION::LEFT:
			_collision.atkPosX = _collision.defRc.left - 35;
			_collision.atkPosY = _movePosY;

			_collision.atkWidth = 80;
			_collision.atkHeight = 300;

			_collision.defWidth = 140;
			_collision.defHeight = 168;
			break;
		case MONSTERDIRECTION::RIGHT:
			_collision.atkPosX = _collision.defRc.right + 35;
			_collision.atkPosY = _movePosY;

			_collision.atkWidth = 80;
			_collision.atkHeight = 300;

			_collision.defWidth = 140;
			_collision.defHeight = 168;
			break;
		}
	
		
	_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
	_collision.defRc = RectMakeCenter(_movePosX, _movePosY - 30, _collision.defWidth, _collision.defHeight);

}

void Minotaur::draw()
{
	Monster::draw();

	if (_offEff)
	{
		_collision.atkEffectImg->render(getMemDC(),
			_collision.atkRc.left - CAM->getScreenRect().left,
			_collision.atkRc.top - CAM->getScreenRect().top);
	}
}