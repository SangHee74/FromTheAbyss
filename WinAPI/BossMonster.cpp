#include "Stdafx.h"
#include "BossMonster.h"

// 초기화 정리 
Minotaur::Minotaur()
{
	_maxHp = 300;
	_curHp = 300;
	_curAtt = 10;
	_dropExp = 50;
	_dropLufia = RND->getFromIntTo(80,100);
	_dropItemIndex = 0; // 임시

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

	// 초기 렉트 초기화 : 인식렉트, 이동렉트(프레임렌더), 타격범위렉트, 피격범위렉트 
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
	// 피격렉트 재설정
	setCollisionDefRange();


	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		_movePosX = DATAMANAGER->getPlayer()->getPlayer().drawPosX + 40;
		_movePosY = DATAMANAGER->getPlayer()->getPlayer().drawPosY + 90;
	}
	
}


// 플레이어 피격 범위가 인식범위 안에 들어왔을때
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
		// 공격렉트 생성 
		setCollisionAttRange();
		
		// 이펙트 주기와 맞춰서 공격렉트 초기화
		if (_atkTimeCount >= 2.5f)
		{
			_collision.atkWidth = _collision.atkHeight = 0;
			_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
		}

		if (_frameX >= IMG("mino_attack")->getMaxFrameX() 
			&& _atkTimeCount >= 4.0f) // 공격모션 변경 후 일정시간이 지나면
		{
			_atkTimeCount = 0;
			_atkCoolTime = 0;
			_atkStart = false;
			_state = MONSTERSTATE::IDLE; // 공격종료
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
	_collision.atkEffectImg = IMG("none2");
	_collision.atkEffFrameX = 0;
	_collision.atkEffFrameY = 0;
	_collision.atkPosX = _monster.movePosX;
	_collision.atkPosY = _collision.defRc.bottom + 35;
	_collision.atkWidth = 300;
	_collision.atkHeight = 80;

	_atkTimeCount = 0;

	// 보스몬스터의 인식범위는 맵의 대부분.
	// 초기 피격렉트 초기화
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



		// 다 도착하면 공격상태로 변경
		if (_atkStart && _monster.atkCoolTime >= 180.0f && _state != MONSTERSTATE::DEAD)
		{
			_state = MONSTERSTATE::ATK;
		}
	}
	else
	{
		// 플레이어를 인식하지 못한 경우
		// 랜덤으로 이동한다. 

	}

	// 공격이 아니면(끝나면) 쿨타임 
	if (_state != MONSTERSTATE::ATK) _monster.atkCoolTime++;



}


// 플레이어 피격 범위가 인식범위 안에 들어왔을때
void Minotaur::atkack()
{
	_monster.image = IMG("mino_atkack");
	_monster.frameX = 0;
	_monster.frameY = (int)_direction;

	_atkTimeCount++;

	if (_atkTimeCount >= 120)
	{
		_monster.frameX++;
		// 공격렉트 생성 
		setCollisionRange();

		// 이펙트 주기와 맞춰서 공격렉트 초기화
		if (_atkTimeCount >= 210)
		{
			_collision.atkWidth = _collision.atkHeight = 0;
			_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
		}

		if (_monster.frameX >= IMG("mino_atkack")->getMaxFrameX()
			&& _atkTimeCount >= 240) // 공격모션 변경 후 일정시간이 지나면
		{
			_atkTimeCount = 0;

			_state = MONSTERSTATE::IDLE; // 공격종료
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
