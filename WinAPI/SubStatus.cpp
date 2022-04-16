#include "Stdafx.h"
#include "SubStatus.h"

HRESULT SubStatus::init(void)
{
	return S_OK;
}

void SubStatus::release(void)
{
}

void SubStatus::update(void)
{
}

void SubStatus::render(void)
{
	IMAGEMANAGER->findImage("p_face")->render(getMemDC(), CENTER_X + 35, 75);

	// name
	FONTMANAGER->drawText(getMemDC(), RectMake(CENTER_X + 160, 85, 80, 50), "돋움", 40, FW_EXTRABOLD, "DAHLIA", RGB(0, 0, 0));

	// Left 
	// lv, hp, sp, exp, next, lufia 
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().lv, CENTER_X + 272, 144);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().curHp, CENTER_X + 155, 196);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().curSp, CENTER_X + 155, 230);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().maxHp, CENTER_X + 280, 196);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().maxSp, CENTER_X + 280, 230);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().curExp, CENTER_X + 280, 360);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().maxExp, CENTER_X + 280, 394);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().lufia, CENTER_X + 254, 426);


	// Right
	// point, atk, def,int,men,agi,luk
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iStatusPoint, RSCENTER_X + 250, 108);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iAtk, RSCENTER_X + 120, 150);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iDef, RSCENTER_X + 120, 193);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iInt, RSCENTER_X + 120, 236);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iMen, RSCENTER_X + 120, 279);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iAgi, RSCENTER_X + 120, 322);
	showNumberImgAlignLeft(DATAMANAGER->getPlayer()->getPlayerStatus().iLuk, RSCENTER_X + 120, 365);

}

void SubStatus::showNumberImgAlignLeft(int number, int destX, int destY)
{

	// 기본 화이트
	Image* numberImg = IMG("Num_W2");
	int tempX = 22;

	// 최대 9999
	if (number > 999)		 numberImg->frameRender(getMemDC(), destX - tempX * 3, destY, number / 1000 % 10, 0);
	if (number > 99)		 numberImg->frameRender(getMemDC(), destX - tempX * 2, destY, number / 100 % 10, 0);
	if (number > 9)			 numberImg->frameRender(getMemDC(), destX - tempX, destY, number / 10 % 10, 0);
							 numberImg->frameRender(getMemDC(), destX, destY, number % 10, 0);
	if (number <= 0)		 numberImg->frameRender(getMemDC(), destX, destY, 0, 0);

}
