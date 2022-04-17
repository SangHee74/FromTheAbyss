#include "Stdafx.h"
#include "MainGame.h"
#include "ImageClass.h"
#include "SoundClass.h"

#pragma region noUseScene
#include "SoundScene.h"
#include "JsonDataScene.h"
#pragma endregion

#pragma region addScene
#include "Title.h"
#include "Save.h"
#include "MainHall.h"
#include "Abyss.h"
#include "Stage.h"
#include "Pub.h"
#include "Store.h"
#include "Square.h"
#include "Tutorial.h"
#include "Castle.h"
#include "Stage11.h"
#include "Stage14.h"

// 맵툴 
#include "MapTool.h"
#pragma endregion




HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	ImageClass imageClass = ImageClass();
	imageClass.init();
	
	SoundClass soundClass = SoundClass();
	soundClass.init();

	//SCENEMANAGER->addScene("사운드", new SoundScene);
	//SCENEMANAGER->addScene("제이슨", new JsonDataScene);
	SCENEMANAGER->addScene("title", new Title);
	SCENEMANAGER->addScene("save", new Save);
	SCENEMANAGER->addScene("main", new MainHall);
	SCENEMANAGER->addScene("abyss", new Abyss);
	SCENEMANAGER->addScene("pub", new Pub);
	SCENEMANAGER->addScene("store", new Store);
	SCENEMANAGER->addScene("square", new Square);
	SCENEMANAGER->addScene("tutorial", new Tutorial);
	SCENEMANAGER->addScene("castle", new Castle);

	SCENEMANAGER->addScene("stage11", new Stage11);
	SCENEMANAGER->addScene("stage14", new Stage14);

	SCENEMANAGER->addScene("맵툴", new MapTool);

	//SCENEMANAGER->changeScene("stage14");
	//SCENEMANAGER->changeScene("stage11");
	SCENEMANAGER->changeScene("save");



	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	
	
}

void MainGame::update(void)
{
	GameNode::update();
	
	SCENEMANAGER->update();
	
}



void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	   	 
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());


	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}
