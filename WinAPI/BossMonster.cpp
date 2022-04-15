#include "Stdafx.h"
#include "BossMonster.h"

// 초기화 정리 
Minotaur::Minotaur()
{
	_curHp = 300;
	_curAtt = 10;
	_dropExp = 50;
	_dropLufia = RND->getFromIntTo(80,100);
	_dropItemIndex = 0; // 임시

	_state = MONSTERSTATE::IDLE;
	_direction = MONSTERDIRECTION::DOWN;
	_speed = 20;
	_frameX = 0;
	_frameY = (int)_direction;
	_image = IMG("mino_idle");
	_collision.attEffectImg = IMG("none2");
	_collision.attEffFrameX = 0;
	_collision.attEffFrameY = 0;
	_collision.attPosX = _movePosX;
	_collision.attPosY = _collision.defRc.bottom + 35;
	_collision.attWidth = 300;
	_collision.attHeight = 80;

	_pixel.space.LR = 105;
	_pixel.space.TB = 70;

	_attTimeCount = 0;

	// 초기 렉트 초기화 : 인식렉트, 이동렉트(프레임렌더), 타격범위렉트, 피격범위렉트 

	// 보스몬스터의 인식범위는 맵의 대부분.
	_recognitionRc	 = RectMakeCenter
	(DATAMANAGER->getMapData().map->getWidth()*0.5, DATAMANAGER->getMapData().map->getHeight()*0.5, 1900, 1350);
	
	_collision.defWidth = 185; 	_collision.defHeight = 168;

	_moveRc			 = RectMakeCenter(_movePosX, _movePosY, 30, 30);
	_collision.defRc = RectMakeCenter(_movePosX, _movePosY - 30, _collision.defWidth, _collision.defHeight);
	_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
	


	_attStart = false;
}


void Minotaur::move()
{
	if (_playerCheck)
	{
		//cout << "인식중! 보스가 따라감" << endl;
		//cout << "플레이어 좌표 X : " << DATAMANAGER->getPlayer()->getPlayer().drawPosX << " , Y : " << DATAMANAGER->getPlayer()->getPlayer().drawPosY<< endl;
		//monsterMovetoPlayer();


		
		// 다 도착하면 공격상태로 변경
		if ( _attStart && _attCoolTime >= 180.0f && _state != MONSTERSTATE::DEAD)
		{
			_state = MONSTERSTATE::ATT;
		}
	}	
	else
	{
		// 플레이어를 인식하지 못한 경우
		// 랜덤으로 이동한다. 

	}

	// 공격이 아니면(끝나면) 쿨타임 
	if (_state != MONSTERSTATE::ATT) _attCoolTime++;

	

}


// 플레이어 피격 범위가 인식범위 안에 들어왔을때
void Minotaur::attack()
{
	_image = IMG("mino_attack");
	_frameX = 0;
	_frameY = (int)_direction;

	_attTimeCount++;
	cout << "_attTimeCount : " << _attTimeCount << endl;

	if (_attTimeCount >= 120)
	{
		_frameX++;
		// 공격렉트 생성 
		setCollisionRange();
		
		// 이펙트 주기와 맞춰서 공격렉트 초기화
		if (_attTimeCount >= 210)
		{
			_collision.attWidth = _collision.attHeight = 0;
			_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
		}

		if (_frameX >= IMG("mino_attack")->getMaxFrameX() 
			&& _attTimeCount >= 240) // 공격모션 변경 후 일정시간이 지나면
		{
			_attTimeCount = 0;
			
			_state = MONSTERSTATE::IDLE; // 공격종료
			_attCoolTime = 0;
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

void Minotaur::setCollisionRange()
{
	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.defWidth = 185;
		_collision.defHeight = 168;

		_collision.attPosX = _movePosX;
		_collision.attPosY = _collision.defRc.top-35;
		_collision.attWidth = 300;
		_collision.attHeight = 80;
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.defWidth = 185;
		_collision.defHeight = 168;

		_collision.attPosX = _movePosX;
		_collision.attPosY = _collision.defRc.bottom + 35;
		_collision.attWidth = 300;
		_collision.attHeight = 80;

		break;
	case MONSTERDIRECTION::LEFT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;

		_collision.attPosX = _collision.defRc.left - 35;
		_collision.attPosY = _movePosY;
		_collision.attWidth = 80;
		_collision.attHeight = 300;
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.defWidth = 140;
		_collision.defHeight = 168;

		_collision.attPosX = _collision.defRc.right + 35;
		_collision.attPosY = _movePosY;
		_collision.attWidth = 80;
		_collision.attHeight = 300;
		break;
	}

	if(_state != MONSTERSTATE::ATT) 	_collision.attWidth = _collision.attHeight = 0;
	_collision.defRc = RectMakeCenter(_movePosX, _movePosY - 30, _collision.defWidth, _collision.defHeight);
	_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);

}


void Minotaur::drawEffect()
{
	_collision.attEffectImg = IMG("none");

	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.attEffectImg = IMG("eff_bossAttUp");
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.attEffectImg = IMG("eff_bossAttDown");
		break;
	case MONSTERDIRECTION::LEFT:
		_collision.attEffectImg = IMG("eff_bossAttLeft");
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.attEffectImg = IMG("eff_bossAttRight");
		break;
	}

	if (_state == MONSTERSTATE::ATT)
	{
		_collision.attEffectImg->render(getMemDC(),
			_collision.attRc.left - CAM->getScreenRect().left, 
			_collision.attRc.top - CAM->getScreenRect().top);
	}
			
}




// 수정전
#if 0 


// 초기화 정리 
Minotaur::Minotaur()
{
	_curHp = 300;
	_curAtt = 10;
	_dropExp = 50;
	_dropLufia = RND->getFromIntTo(80, 100);
	_dropItemIndex = 0; // 임시

	_state = MONSTERSTATE::IDLE;
	_direction = MONSTERDIRECTION::DOWN;
	_monster.speed = 20;
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;
	_monster.image = IMG("mino_idle");
	_collision.attEffectImg = IMG("none2");
	_collision.attEffFrameX = 0;
	_collision.attEffFrameY = 0;
	_collision.attPosX = _monster.movePosX;
	_collision.attPosY = _collision.defRc.bottom + 35;
	_collision.attWidth = 300;
	_collision.attHeight = 80;

	_attTimeCount = 0;

	// 보스몬스터의 인식범위는 맵의 대부분.
	// 초기 피격렉트 초기화
	_collision.defWidth = 185; 	_collision.defHeight = 168;
	_collision.defRc = RectMakeCenter(_monster.movePosX, _monster.movePosY - 30, _collision.defWidth, _collision.defHeight);
	_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);

	_monster.recognitionRc = RectMakeCenter
	(DATAMANAGER->getMapData().map->getWidth()*0.5, DATAMANAGER->getMapData().map->getHeight()*0.5, 1900, 1350);
	//(DATAMANAGER->getMapData().map->getWidth()*0.5, DATAMANAGER->getMapData().map->getHeight()*0.5, 1690, 1060);

	_attStart = false;
}


void Minotaur::move()
{
	if (_monster.playerCheck)
	{
		//cout << "인식중! 보스가 따라감" << endl;
		//cout << "플레이어 좌표 X : " << DATAMANAGER->getPlayer()->getPlayer().drawPosX << " , Y : " << DATAMANAGER->getPlayer()->getPlayer().drawPosY<< endl;
		monsterMovetoPlayer();



		// 다 도착하면 공격상태로 변경
		if (_attStart && _monster.attCoolTime >= 180.0f && _state != MONSTERSTATE::DEAD)
		{
			_state = MONSTERSTATE::ATT;
		}
	}
	else
	{
		// 플레이어를 인식하지 못한 경우
		// 랜덤으로 이동한다. 

	}

	// 공격이 아니면(끝나면) 쿨타임 
	if (_state != MONSTERSTATE::ATT) _monster.attCoolTime++;



}


// 플레이어 피격 범위가 인식범위 안에 들어왔을때
void Minotaur::attack()
{
	_monster.image = IMG("mino_attack");
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;

	_attTimeCount++;
	cout << "_attTimeCount : " << _attTimeCount << endl;

	if (_attTimeCount >= 120)
	{
		_monster.frameX++;
		// 공격렉트 생성 
		setCollisionRange();

		// 이펙트 주기와 맞춰서 공격렉트 초기화
		if (_attTimeCount >= 210)
		{
			_collision.attWidth = _collision.attHeight = 0;
			_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
		}

		if (_monster.frameX >= IMG("mino_attack")->getMaxFrameX()
			&& _attTimeCount >= 240) // 공격모션 변경 후 일정시간이 지나면
		{
			_attTimeCount = 0;

			_state = MONSTERSTATE::IDLE; // 공격종료
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
	case MONSTERDIRECTION::UP:
		_collision.defWidth = 185;
		_collision.defHeight = 168;

		_collision.attPosX = _monster.movePosX;
		_collision.attPosY = _collision.defRc.top - 35;
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
	case MONSTERDIRECTION::LEFT:
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

	if (_state != MONSTERSTATE::ATT) 	_collision.attWidth = _collision.attHeight = 0;
	_collision.attRc = RectMakeCenter(_collision.attPosX, _collision.attPosY, _collision.attWidth, _collision.attHeight);
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
			cout << DATAMANAGER->getPlayer()->getPlayer().drawPosY + 30 << endl;
		}






		if (_monster.movePosY >= DATAMANAGER->getPlayer()->getPlayer().drawPosY + 50) _attStart = true;

		break;
	case MONSTERDIRECTION::DOWN:
		if (_monster.movePosY < DATAMANAGER->getPlayer()->getPlayer().drawPosY + 30)
		{
			_monster.movePosY += _monster.speed;
		}
		if (_monster.movePosY <= DATAMANAGER->getPlayer()->getPlayer().drawPosY + 50) _attStart = true;

		break;
	case MONSTERDIRECTION::LEFT:
		if (_monster.movePosX > DATAMANAGER->getPlayer()->getPlayer().drawPosX + 30)
		{
			_monster.movePosX -= _monster.speed;
		}
		if (_monster.movePosX >= DATAMANAGER->getPlayer()->getPlayer().drawPosX + 60) _attStart = true;
		break;
	case MONSTERDIRECTION::RIGHT:
		if (_monster.movePosX < DATAMANAGER->getPlayer()->getPlayer().drawPosX + 30)
		{
			_monster.movePosX += _monster.speed;
		}
		if (_monster.movePosX <= DATAMANAGER->getPlayer()->getPlayer().drawPosX + 60) _attStart = true;

		break;

	}



}

void Minotaur::drawEffect()
{
	_collision.attEffectImg = IMG("none");

	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		_collision.attEffectImg = IMG("eff_bossAttUp");
		break;
	case MONSTERDIRECTION::DOWN:
		_collision.attEffectImg = IMG("eff_bossAttDown");
		break;
	case MONSTERDIRECTION::LEFT:
		_collision.attEffectImg = IMG("eff_bossAttLeft");
		break;
	case MONSTERDIRECTION::RIGHT:
		_collision.attEffectImg = IMG("eff_bossAttRight");
		break;
	}

	if (_state == MONSTERSTATE::ATT)
	{
		_collision.attEffectImg->render(getMemDC(),
			_collision.attRc.left - CAM->getScreenRect().left,
			_collision.attRc.top - CAM->getScreenRect().top);
	}

}

#endif
