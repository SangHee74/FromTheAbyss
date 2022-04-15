#include "Stdafx.h"
#include "Monster.h"

Monster::Monster(): _maxHp(0), _curHp(0), _curAtt(0),
					_dropExp(0), _dropLufia(0), _dropItemIndex(0),
					_moveRc(RectMake(0,0,0,0)), 
					_recognitionRc(RectMake(0, 0, 0, 0)),
					_movePosX(0), _movePosY(0),
					_frameX(0), _frameY(0), _atkRange(0),
					_speed(0.0f), _distance(0.0f), _angle(0.0f),
					_rndTimeCount(0.0f), _worldTimeCount(0.0f), _atkCoolTime(0.0f), _atkTimeCount(0.0f),
					_playerCheck(false), _atkStart(false), _image(nullptr)
{
}

HRESULT Monster::init(void)
{
	return S_OK;
}

HRESULT Monster::init(POINT position)
{
	// �ӽú��� 
	timeCount = 0.0f;

	// �̵� �� ������Ʈ ���� 
	_movePosX = position.x;
	_movePosY = position.y;
	_frameX = 0;
	_frameY = 0;
	_speed = 5;
	_distance = 0;
	_angle = 0.0f;

	// ������ ������Ʈ, ���ݻ��� üũ �� 
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_worldTimeCount = GetTickCount();
	_atkCoolTime = 0.0f;
	_atkTimeCount = 0.0f;

	// ������ �νĹ����� �÷��̾ �ִ��� üũ 
	_playerCheck = false;


	return S_OK;
}

HRESULT Monster::init(const char* imageName, POINT position)
{
	// �ӽú��� 
	timeCount = 0.0f;

	// �̹��� ����
	_image= IMAGEMANAGER->findImage(imageName);

	// �̵� �� ������Ʈ ���� 
	_movePosX = position.x;
	_movePosY = position.y;
	_frameX = 0;
	_frameY = 0;
	_speed = 5;
	_distance = 0;
	_angle = 0.0f;

	// ������ ������Ʈ, ���ݻ��� üũ �� 
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_worldTimeCount = GetTickCount();
	_atkCoolTime = 0.0f;
	_atkTimeCount = 0.0f;

	// ������ �νĹ����� �÷��̾ �ִ��� üũ 
	_playerCheck = false;


	return S_OK;
}

void Monster::release(void)
{
}

void Monster::update(void)
{
	// �̵�
	move();

	// ������ȯ + ��Ʈ �ʱ�ȭ
	setDirection();
	
	// �÷��̾� �߽߰� ���󰡱�
	if (_playerCheck) monsterMovetoPlayer();
	
	// �ȼ��浹
	pixelCollision();



	// ����
	if ( _atkStart && _atkCoolTime >= 120.0f )
	{
		_state = MONSTERSTATE::ATK;
		atkack();
	}
	if (_state == MONSTERSTATE::ATK) _atkTimeCount++;
	if (_state != MONSTERSTATE::ATK) _atkCoolTime++;
	//cout << "_atkTimeCount : " << _atkTimeCount << endl;
	//cout << "_atkCoolTime : " << _atkCoolTime << endl;
	

	// �ǰ�
	if (_state == MONSTERSTATE::DEF)
	{
		//cout << "���� �ǰ� �� Ÿ��ī��Ʈ : " << timeCount << endl;
		timeCount += TIMEMANAGER->getElapsedTime();

		if (timeCount >= 1.0f)
		{
			timeCount = 0;
			_state = MONSTERSTATE::IDLE;
		}
	}

	// ���, �̵� �� ���⿡ ���� ������Y ����
	if (_state == MONSTERSTATE::IDLE || _state == MONSTERSTATE::MOVE)
	{
		_frameY = static_cast<int>(_direction);
	}

	// ���� ��� �浹 ���� �ʱ�ȭ
	if (_state == MONSTERSTATE::DEAD)
	{
		_collision.defWidth = _collision.defHeight = 0;
		_collision.defRc = RectMakeCenter(_movePosX, _movePosY, _collision.atkWidth, _collision.atkHeight);

		_collision.atkWidth = _collision.atkHeight = 0;
		_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
	}


}

void Monster::render(void)
{
	draw();
	animation();
	drawEffect();
}


void Monster::draw(void)
{

	//if (KEYMANAGER->isToggleKey(VK_F3))
	{
		//�νķ�Ʈ
	//	Rectangle(getMemDC(),
	//	_recognitionRc.left - CAM->getScreenRect().left,
	//	_recognitionRc.top - CAM->getScreenRect().top,
	//	_recognitionRc.right - CAM->getScreenRect().left,
	//	_recognitionRc.bottom - CAM->getScreenRect().top
	//	);

		// �̵���Ʈ
		//Rectangle(getMemDC(),
		//	_moveRc.left - CAM->getScreenRect().left,
		//	_moveRc.top - CAM->getScreenRect().top,
		//	_image->getFrameWidth() + _moveRc.left - CAM->getScreenRect().left,
		//	_image->getFrameHeight() + _moveRc.top - CAM->getScreenRect().top
		//);

		// �ǰݷ�Ʈ
		Rectangle(getMemDC(),
			_collision.defRc.left - CAM->getScreenRect().left,
			_collision.defRc.top - CAM->getScreenRect().top,
			_collision.defRc.right - CAM->getScreenRect().left,
			_collision.defRc.bottom - CAM->getScreenRect().top
		);

		// Ÿ�ݷ�Ʈ
		Rectangle(getMemDC(),
			_collision.atkRc.left - CAM->getScreenRect().left,
			_collision.atkRc.top - CAM->getScreenRect().top,
			_collision.atkRc.right - CAM->getScreenRect().left,
			_collision.atkRc.bottom - CAM->getScreenRect().top
		);

		// �ӽ� �÷��̾� ��ο췺Ʈ
		//Rectangle(getMemDC(),
		//	DATAMANAGER->getPlayer()->getPlayer().drawRc.left - CAM->getScreenRect().left,
		//	DATAMANAGER->getPlayer()->getPlayer().drawRc.top - CAM->getScreenRect().top,
		//	DATAMANAGER->getPlayer()->getPlayer().drawRc.right - CAM->getScreenRect().left,
		//	DATAMANAGER->getPlayer()->getPlayer().drawRc.bottom - CAM->getScreenRect().top
		//);

		RECT tempPos, tempPos2, tempPos3, tempPos4, tempPos5;
		tempPos = RectMakeCenter(_movePosX, _movePosY, 4, 4);
		Rectangle(getMemDC(), tempPos.left - CAM->getScreenRect().left, tempPos.top - CAM->getScreenRect().top,
			tempPos.left - CAM->getScreenRect().left + 4, tempPos.top - CAM->getScreenRect().top + 4);

		// �ȼ��浹 �Ʒ� - �� �¿�� �Ѹ��� 
		tempPos2 = RectMakeCenter(_movePosX, _pixel.probeUp, 4, 4);
		Rectangle(getMemDC(), tempPos2.left - CAM->getScreenRect().left, tempPos2.top - CAM->getScreenRect().top,
			tempPos2.left - CAM->getScreenRect().left + 4, tempPos2.top - CAM->getScreenRect().top + 4);

		tempPos3 = RectMakeCenter(_movePosX, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos3.left - CAM->getScreenRect().left, tempPos3.top - CAM->getScreenRect().top,
			tempPos3.left - CAM->getScreenRect().left + 4, tempPos3.top - CAM->getScreenRect().top + 4);
		// �ȼ��浹 ��
		tempPos4 = RectMakeCenter(_pixel.probeLeft, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos4.left - CAM->getScreenRect().left, tempPos4.top - CAM->getScreenRect().top,
			tempPos4.left - CAM->getScreenRect().left + 4, tempPos4.top - CAM->getScreenRect().top + 4);
		// �ȼ��浹 ��
		tempPos5 = RectMakeCenter(_pixel.probeRight, _pixel.probeDown, 4, 4);
		Rectangle(getMemDC(), tempPos5.left - CAM->getScreenRect().left, tempPos5.top - CAM->getScreenRect().top,
			tempPos5.left - CAM->getScreenRect().left + 4, tempPos5.top - CAM->getScreenRect().top + 4);
	}


	_image->frameRender(getMemDC(),
		_moveRc.left - CAM->getScreenRect().left,
		_moveRc.top  - CAM->getScreenRect().top,
		_frameX, _frameY);
	
	//rcMake(getMemDC(), _moveRc);
}

void Monster::animation(void) 
{
	switch (_state)
	{
	case MONSTERSTATE::ATK:


		break;


	default:
		if (_rndTimeCount + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_frameX++;
			if (_image->getMaxFrameX() < _frameX)
			{
				_frameX = 0;
			}
		}
		break;
	}
	

}

void Monster::setDirection(void)
{
	if (_playerCheck && _state != MONSTERSTATE::ATK)
	{
		// �÷��̾� ������ ���� ���� ��ȯ
		// X �������� �����¿� 
		if (_angle >= 45 * DTR && _angle < 135 * DTR)
		{
			_direction = MONSTERDIRECTION::UP;
		}
		if (_angle >= 135 * DTR	&& _angle < 225 * DTR)
		{
			_direction = MONSTERDIRECTION::LEFT;
		}
		if (_angle >= 225 * DTR	&& _angle < 315 * DTR)
		{
			_direction = MONSTERDIRECTION::DOWN;
		}
		if (_angle >= 315 * DTR || (_angle >= 0 * DTR && _angle < 45 * DTR))
		{
			_direction = MONSTERDIRECTION::RIGHT;
		}
	}
 
	_moveRc = RectMakeCenter(_movePosX, _movePosY, _image->getFrameWidth(), _image->getFrameHeight());

}

void Monster::monsterMovetoPlayer(void)
{
	_state = MONSTERSTATE::MOVE;

	if (_state == MONSTERSTATE::MOVE);
	{
		switch (_direction)
		{
		case MONSTERDIRECTION::UP:
			if (_distance > _atkRange)
			{
				_movePosY -= _speed;
			}
			else if (_distance > _recognitionRc.bottom - _recognitionRc.top)
			{
				_distance = 0;
			}
			else
			{
				if (_atkCoolTime >= 120.0f) _atkStart = true;
				if (_atkCoolTime < 120.0f) _atkStart = false;
			}
			break;

		case MONSTERDIRECTION::DOWN:
			if (_distance > _atkRange)
			{
				_movePosY += _speed;
			}
			else if (_distance > _recognitionRc.bottom - _recognitionRc.top)
			{
				_distance = 0;
			}
			else
			{
				if (_atkCoolTime >= 120.0f) _atkStart = true;
				if (_atkCoolTime < 120.0f) _atkStart = false;
			}
			break;

		case MONSTERDIRECTION::LEFT:
			if (_distance > _atkRange)
			{
				_movePosX -= _speed;
			}
			else if (_distance > _recognitionRc.right - _recognitionRc.left)
			{
				_distance = 0;
			}
			else
			{
				if (_atkCoolTime >= 120.0f) _atkStart = true;
				if (_atkCoolTime < 120.0f) _atkStart = false;
			}
			break;

		case MONSTERDIRECTION::RIGHT:
			if (_distance > _atkRange)
			{
				_movePosX += _speed;
			}
			else if (_distance > _recognitionRc.right - _recognitionRc.left)
			{
				_distance = 0;
			}
			else
			{
				if (_atkCoolTime >= 120.0f) _atkStart = true;
				if (_atkCoolTime < 120.0f) _atkStart = false;
			}
			break;

		}

	}

}

void Monster::pixelCollision()
{
	//Ž��
	_pixel.probeUp	  =  _movePosY - _pixel.space.TB;
	_pixel.probeDown  =  _movePosY + _pixel.space.TB;
	_pixel.probeLeft  =  _movePosX - _pixel.space.LR;
	_pixel.probeRight =  _movePosX + _pixel.space.LR;


	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		if (pixelColorCheck(_movePosX, _pixel.probeUp)) _movePosY += _speed;
		break;
	case MONSTERDIRECTION::DOWN:
		if (pixelColorCheck(_movePosX, _pixel.probeUp)) _movePosY -= _speed;
		break;
	case MONSTERDIRECTION::LEFT:
		if (pixelColorCheck(_pixel.probeLeft, _pixel.probeDown)) _movePosX += _speed;
		break;
	case MONSTERDIRECTION::RIGHT:
		if (pixelColorCheck(_pixel.probeRight, _pixel.probeDown)) _movePosX -= _speed;
		break;
	}

}

bool Monster::pixelColorCheck(int getPixelX, int getPixelY)
{
	DATAMANAGER->getMapData().pixelMap->getMemDC();

	COLORREF color = GetPixel(DATAMANAGER->getMapData().pixelMap->getMemDC(), getPixelX, getPixelY);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);


	if (!(r == 255 && g == 0 && b == 255))
	{
		// ����Ÿ�� �ƴϸ�, �ȼ� �浹��.
		return true;
	}
	else return false;

}


// �������̵� �Լ�
void Monster::move(void){
}

void Monster::atkack(void){
}

void Monster::drawEffect(void){
}




// ���� ���� �� 
#if 0

HRESULT Monster::init(void)
{
	return S_OK;
}

HRESULT Monster::init(POINT position)
{
	timeCount = 0.0f;

	_monster.worldTimeCount = GetTickCount();
	_monster.rndTimeCount = RND->getFromFloatTo(50, 150);

	_monster.movePosX = position.x;
	_monster.movePosY = position.y;
	_monster.frameX = 0;
	_monster.frameY = 0;
	_monster.speed = 2;
	_monster.distance = 0;
	_monster.angle = 0.0f;
	_monster.playerCheck = false;
	_monster.atkCoolTime = 0.0f;

	_monster.moveRc = RectMakeCenter(position.x, position.y,
		_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
	//_monster.recognitionRc = RectMakeCenter(position.x, position.y,
	//	_monster.image->getFrameHeight()*3, _monster.image->getFrameHeight()*3);
	_collision.defRc = CollisionAreaResizing(_monster.moveRc, 40, 40);

	//RectMakeCenter(position.x, position.y,
	//_monster.image->getFrameWidth()-40, _monster.image->getFrameHeight()-40);
	return S_OK;
}

HRESULT Monster::init(const char* imageName, POINT position)
{
	_monster.worldTimeCount = GetTickCount();
	_monster.rndTimeCount = RND->getFromFloatTo(50, 150);

	_monster.image = IMAGEMANAGER->findImage(imageName);

	_monster.movePosX = position.x;
	_monster.movePosY = position.y;
	_monster.frameX = 0;
	_monster.frameY = 0;
	_monster.speed = 2;
	_monster.distance = 0;
	_monster.angle = 0.0f;
	_monster.playerCheck = false;
	_monster.atkCoolTime = 0.0f;

	_monster.moveRc = RectMakeCenter(position.x, position.y,
		_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
	//_monster.recognitionRc = RectMakeCenter(position.x, position.y,
	//	_monster.image->getFrameHeight() * 3, _monster.image->getFrameHeight() * 3);
	_collision.defRc = CollisionAreaResizing(_monster.moveRc, 40, 40);


	return S_OK;
}

void Monster::release(void)
{
}

void Monster::update(void)
{
	move();
	setDirection();
	pixelCollision();
	if (_state == MONSTERSTATE::ATK) atkack();  // ���ۼ�

	if (_state == MONSTERSTATE::DEF)
	{
		timeCount += TIMEMANAGER->getElapsedTime();

		if (timeCount >= 1.0f)
		{
			timeCount = 0;
			_state = MONSTERSTATE::IDLE;
		}
	}

	if (_state == MONSTERSTATE::IDLE || _state == MONSTERSTATE::MOVE)
	{
		_monster.frameY = static_cast<int>(_direction);
	}

	if (_state == MONSTERSTATE::DEAD)
	{
		_collision.atkWidth = _collision.atkHeight = 0;
		_collision.atkRc = RectMakeCenter(_collision.atkPosX, _collision.atkPosY, _collision.atkWidth, _collision.atkHeight);
	}


}

void Monster::render(void)
{
	draw();
	animation();
	drawEffect();
}

void Monster::move(void)
{
	// �������̵�
}

void Monster::atkack(void)
{
	// �������̵�
}

void Monster::draw(void)
{
	//�νķ�Ʈ
	//Rectangle(getMemDC(),
	//	_monster.recognitionRc.left - CAM->getScreenRect().left,
	//	_monster.recognitionRc.top - CAM->getScreenRect().top,
	//	_monster.recognitionRc.right - CAM->getScreenRect().left,
	//	_monster.recognitionRc.bottom - CAM->getScreenRect().top
	//);

	// �ǰݷ�Ʈ
	Rectangle(getMemDC(),
		_collision.defRc.left - CAM->getScreenRect().left,
		_collision.defRc.top - CAM->getScreenRect().top,
		_collision.defRc.right - CAM->getScreenRect().left,
		_collision.defRc.bottom - CAM->getScreenRect().top
	);

	// Ÿ�ݷ�Ʈ
	Rectangle(getMemDC(),
		_collision.atkRc.left - CAM->getScreenRect().left,
		_collision.atkRc.top - CAM->getScreenRect().top,
		_collision.atkRc.right - CAM->getScreenRect().left,
		_collision.atkRc.bottom - CAM->getScreenRect().top
	);

	// �̵���Ʈ
//Rectangle(getMemDC(),
//	_monster.moveRc.left - CAM->getScreenRect().left,
//	_monster.moveRc.top - CAM->getScreenRect().top,
//	_monster.image->getFrameWidth() + _monster.moveRc.left - CAM->getScreenRect().left,
//	_monster.image->getFrameHeight() + _monster.moveRc.top - CAM->getScreenRect().top
//);




	_monster.image->frameRender(getMemDC(),
		_monster.moveRc.left - CAM->getScreenRect().left,
		_monster.moveRc.top - CAM->getScreenRect().top,
		_monster.frameX, _monster.frameY);

	//rcMake(getMemDC(), _moveRc);
}

void Monster::animation(void)
{
	if (_monster.rndTimeCount + _monster.worldTimeCount <= GetTickCount())
	{
		_monster.worldTimeCount = GetTickCount();
		_monster.frameX++;
		if (_monster.image->getMaxFrameX() < _monster.frameX)
		{
			_monster.frameX = 0;
		}
	}

}

void Monster::setDirection(void)
{

	if (_monster.playerCheck && _state != MONSTERSTATE::ATK)
	{
		// �÷��̾� ������ ���� ���� ��ȯ
		if (_monster.angle >= 45 * DTR && _monster.angle < 135 * DTR)
		{
			_direction = MONSTERDIRECTION::UP;
		}
		if (_monster.angle >= 135 * DTR	&& _monster.angle < 225 * DTR)
		{
			_direction = MONSTERDIRECTION::LEFT;
		}
		if (_monster.angle >= 225 * DTR	&& _monster.angle < 315 * DTR)
		{
			_direction = MONSTERDIRECTION::DOWN;
		}
		if (_monster.angle >= 315 * DTR || (_monster.angle >= 0 * DTR && _monster.angle < 45 * DTR))
		{
			_direction = MONSTERDIRECTION::RIGHT;
		}
	}

	if (_monster.image != nullptr)
	{
		_monster.moveRc = RectMakeCenter(_monster.movePosX, _monster.movePosX,
			_monster.image->getFrameWidth(), _monster.image->getFrameHeight());
	}
}

void Monster::setCollisionRange()
{
	// �������̵�
	// ���⺰ Ÿ��, �ǰ� ���� ������
}

void Monster::drawEffect(void)
{
	// �������̵�
}



void Monster::pixelCollision()
{
	//Ž��
	_pixel.probeUp = (_monster.movePosY + _monster.image->getFrameHeight() / 2) - 16;
	_pixel.probeDown = (_monster.movePosY + _monster.image->getFrameHeight() / 2) - 8;
	_pixel.probeLeft = _monster.movePosX - 20;
	_pixel.probeRight = _monster.movePosX + 20;

	switch (_direction)
	{
	case MONSTERDIRECTION::UP:
		if (pixelColorCheck(_monster.movePosX, _pixel.probeUp)) _monster.movePosY += _monster.speed;
		break;
	case MONSTERDIRECTION::DOWN:
		if (pixelColorCheck(_monster.movePosX, _pixel.probeUp)) _monster.movePosY -= _monster.speed;
		break;
	case MONSTERDIRECTION::LEFT:
		if (pixelColorCheck(_pixel.probeLeft, _pixel.probeDown)) _monster.movePosX += _monster.speed;
		break;
	case MONSTERDIRECTION::RIGHT:
		if (pixelColorCheck(_pixel.probeRight, _pixel.probeDown)) _monster.movePosX -= _monster.speed;
		break;
	}
}

bool Monster::pixelColorCheck(int getPixelX, int getPixelY)
{
	DATAMANAGER->getMapData().pixelMap->getMemDC();

	COLORREF color = GetPixel(DATAMANAGER->getMapData().pixelMap->getMemDC(), getPixelX, getPixelY);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);


	if (!(r == 255 && g == 0 && b == 255))
	{
		// ����Ÿ�� �ƴϸ�, �ȼ� �浹��.
		return true;
	}
	else return false;

}





//if (KEYMANAGER->isToggleKey(VK_F3))
{
	//�νķ�Ʈ
//	Rectangle(getMemDC(),
//	_recognitionRc.left - CAM->getScreenRect().left,
//	_recognitionRc.top - CAM->getScreenRect().top,
//	_recognitionRc.right - CAM->getScreenRect().left,
//	_recognitionRc.bottom - CAM->getScreenRect().top
//	);

	// �̵���Ʈ
	Rectangle(getMemDC(),
		_moveRc.left, _moveRc.top,
		_image->getFrameWidth() + _moveRc.left, _image->getFrameHeight() + _moveRc.top);

	// �ǰݷ�Ʈ
	Rectangle(getMemDC(),
		_collision.defRc.left, _collision.defRc.top,
		_collision.defRc.right, _collision.defRc.bottom);

	// Ÿ�ݷ�Ʈ
	Rectangle(getMemDC(),
		_collision.atkRc.left, _collision.atkRc.top,
		_collision.atkRc.right, _collision.atkRc.bottom);

	// �ӽ� �÷��̾� ��ο췺Ʈ
	Rectangle(getMemDC(),
		DATAMANAGER->getPlayer()->getPlayer().drawRc.left,
		DATAMANAGER->getPlayer()->getPlayer().drawRc.top,
		DATAMANAGER->getPlayer()->getPlayer().drawRc.right,
		DATAMANAGER->getPlayer()->getPlayer().drawRc.bottom);

	RECT tempPos, tempPos2, tempPos3, tempPos4, tempPos5;
	tempPos = RectMakeCenter(_movePosX, _movePosY, 4, 4);
	Rectangle(getMemDC(), tempPos.left, tempPos.top,
		tempPos.left + 4, tempPos.top + 4);

	// �ȼ��浹 �Ʒ� - �� �¿�� �Ѹ��� 
	tempPos2 = RectMakeCenter(_movePosX, _pixel.probeUp, 4, 4);
	Rectangle(getMemDC(), tempPos2.left, tempPos2.top,
		tempPos2.left + 4, tempPos2.top + 4);

	tempPos3 = RectMakeCenter(_movePosX, _pixel.probeDown, 4, 4);
	Rectangle(getMemDC(), tempPos3.left, tempPos3.top,
		tempPos3.left + 4, tempPos3.top + 4);
	// �ȼ��浹 ��
	tempPos4 = RectMakeCenter(_pixel.probeLeft, _pixel.probeDown, 4, 4);
	Rectangle(getMemDC(), tempPos4.left, tempPos4.top,
		tempPos4.left + 4, tempPos4.top + 4);
	// �ȼ��浹 ��
	tempPos5 = RectMakeCenter(_pixel.probeRight, _pixel.probeDown, 4, 4);
	Rectangle(getMemDC(), tempPos5.left, tempPos5.top,
		tempPos5.left + 4, tempPos5.top + 4);
}
#endif