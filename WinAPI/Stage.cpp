#include "Stdafx.h"
#include "Stage.h"
#include "Abyss.h"

HRESULT Stage::init(void)
{
	// 캐릭터 이닛
	DATAMANAGER->getPlayer()->init(); // 로드한 데이터 이닛.

	_em = new EnemyManager();

	//_currentAbyss = _player->getP
	_em->init(_currentAbyss, _currentStage);

	_UIBar = new ProgressBar();
	_UIBar->init(_player->getPlayerStatus().maxHp, _player->getPlayerStatus().maxSp);
	
	_subScreen = new SubMenu();
	_subScreen->init();

	// 맵 정보 세팅
	// 플레이어가 가진 선택 어비스, 스테이지 정보를 기준으로. 
	// 렌더맵, 픽셀맵, 오브젝트, 탑렌더 
	_player->setPixelMap("map_stage1_pixel");

	CAM->init();
	CAM->setLimitsX(LSCENTER_X, IMG("map_stage1")->getWidth());
	CAM->setLimitsY(CENTER_Y, IMG("map_stage1")->getHeight());

	_alpha;

	return S_OK;
}

void Stage::release(void)
{
	_UIBar->release();
	SAFE_DELETE(_UIBar);

	_subScreen->release();
	SAFE_DELETE(_subScreen);


	_em->release();
	SAFE_DELETE(_em);

	//STATE::destroy();

}

void Stage::update(void)
{
	POINT cameraPos;
	cameraPos.x = _player->getPlayer().movePosX;
	cameraPos.y = _player->getPlayer().movePosY;
	CAM->setCameraPos(cameraPos);
	CAM->update();
	_player->getPlayerCAM().rc = CAM->getScreenRect();
	_player->update();

	_UIBar->setHpGauge(_player->getPlayerStatus().curHp, _player->getPlayerStatus().maxHp);
	_UIBar->setSpGauge(_player->getPlayerStatus().curSp, _player->getPlayerStatus().maxSp);
	_UIBar->update();
	IMG("Num_UI")->setFrameX(11);
	IMG("Num_UI")->setFrameY(1);




	if (KEYOKD('5'))
	{
		_player->getPlayerStatus().curHp -= 10;
		_player->setState(PLAYERSTATE::HIT);
	}

	if (KEYOKD('6'))
	{
		_player->getPlayerStatus().curHp += 10;
	}

	if (KEYOKD('7'))
	{
		cout << "끼임탈출!" << endl;
		_player->getPlayer().movePosX = 50;
		_player->getPlayer().movePosY = 300;
	}

	_subScreen->update();
	
	
	// 죽으면 메인홀로 이동
	if ( _player->getState() == PLAYERSTATE::DEAD)
	{
		SCENEMANAGER->changeScene("main");
	}

	_em->update();

	int tempDistance;
	//getDistance(_player->getPlayer().movePosX, _player->getPlayer().movePosY,
	//	_em->getMonsters())


}

void Stage::render(void)
{
	int cameraLeft = CAM->getScreenRect().left;
	int cameraTop = CAM->getScreenRect().top;

	IMGR("map_stage1", getMemDC(), 0, 0,
		cameraLeft,
		cameraTop,
		CENTER_X, WINSIZE_Y);

	_player->render();

	//_em->render();

	IMGR("map_stage1_top", getMemDC(), 0, 0,
		cameraLeft,
		cameraTop,
		CENTER_X, WINSIZE_Y);
	
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		IMGR("map_stage1_pixel", getMemDC(), 0, 0,
			cameraLeft,
			cameraTop,
			CENTER_X, WINSIZE_Y);
	}
	_UIBar->render();
	_UIBar->renderHpSpNumImg(_player->getPlayerStatus().curHp, _player->getPlayerStatus().curSp,
		_player->getPlayerStatus().maxHp, _player->getPlayerStatus().maxSp);
	//IMGR("UI_pathInfo", getMemDC(), LSCENTER_X-21, 10);

	_subScreen->render();



}
