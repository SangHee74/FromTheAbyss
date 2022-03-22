#include "Stdafx.h"
#include "ProgressBar.h"


HRESULT ProgressBar::init(float hp, float sp)
{

	_hpWidth = 184;
	_spWidth = 184;

	// 여기서 이미지 관리
	_hpBar = IMAGEMANAGER->addImage("hp", "Resources/Images/Object/hp.bmp", _hpWidth , 4 * MAGNI);
	_spBar = IMAGEMANAGER->addImage("sp", "Resources/Images/Object/sp.bmp", _spWidth , 4 * MAGNI);

	_hpBarCover =IMG("HPBar");
	_spBarCover = IMG("SPBar");

	_hpRc = RectMake(94,52, _hpWidth, _hpBar->getHeight());
	_spRc = RectMake(390,52, _spWidth, _spBar->getHeight());


	return S_OK;
}



void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{
//	_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
	_hpRc = RectMake(_hpBarCover->getX() + 10, _hpBarCover->getY() + 30, _hpWidth, _hpBar->getHeight());
	_spRc = RectMake(_spBarCover->getX() + 10, _spBarCover->getY() + 30, _spWidth, _spBar->getHeight());

}

void ProgressBar::render(void)
{
	/*
	_progressBarDown->render(getMemDC(),
		_rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2,
		0, 0,
		_progressBarDown->getWidth(),
		_progressBarDown->getHeight()    );

	// Up : Down에 종속적임. 
	_progressBarUp->render(getMemDC(),
		_rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2,
		0, 0,
		_width,
		_progressBarDown->getHeight()    );
	*/



	_hpBarCover->render(getMemDC(), _hpBarCover->getX(), _hpBarCover->getY());
	_spBarCover->render(getMemDC(), _spBarCover->getX(), _spBarCover->getY());
	_hpBar->render(getMemDC(), _hpRc.left,_hpRc.top,0,0, _hpWidth, _hpBar->getHeight());
	_spBar->render(getMemDC(), _spRc.left, _spRc.top, 0, 0, _spWidth, _spBar->getHeight());

	rcMake(getMemDC(), _hpRc);
	rcMake(getMemDC(), _spRc);
}

void ProgressBar::setHpGauge(float currentScore, float maxScore)
{
	_hpWidth = (currentScore / maxScore)* _hpBar->getWidth();
}

void ProgressBar::setSpGauge(float currentScore, float maxScore)
{
	_spWidth = (currentScore / maxScore)* _spBar->getWidth();

}

