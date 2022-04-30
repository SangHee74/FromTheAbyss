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
#include "GameOver.h"
#include "MainHall.h"
#include "Abyss.h"
#include "Pub.h"
#include "Store.h"
#include "Square.h"
#include "Tutorial.h"
#include "Castle.h"
#include "Stage11.h"
#include "Stage14.h"
#include "StageBossIntro.h"



// ���� 
#include "MapTool.h"
#pragma endregion




HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	ImageClass imageClass = ImageClass();
	imageClass.init();
	
	SoundClass soundClass = SoundClass();
	soundClass.init();

	//SCENEMANAGER->addScene("����", new SoundScene);
	//SCENEMANAGER->addScene("���̽�", new JsonDataScene);
	SCENEMANAGER->addScene("title", new Title);
	SCENEMANAGER->addScene("save", new Save);
	SCENEMANAGER->addScene("gameOver", new GameOver);
	SCENEMANAGER->addScene("main", new MainHall);
	SCENEMANAGER->addScene("abyss", new Abyss);
	SCENEMANAGER->addScene("pub", new Pub);
	SCENEMANAGER->addScene("store", new Store);
	SCENEMANAGER->addScene("square", new Square);
	SCENEMANAGER->addScene("tutorial", new Tutorial);
	SCENEMANAGER->addScene("castle", new Castle);

	SCENEMANAGER->addScene("stage11", new Stage11);
	SCENEMANAGER->addScene("stage14", new Stage14);
	SCENEMANAGER->addScene("bossIntro", new StageBossIntro);

	SCENEMANAGER->addScene("����", new MapTool);

	SCENEMANAGER->changeScene("title");
	//SCENEMANAGER->changeScene("stage11");
	//SCENEMANAGER->changeScene("stage14");
	//SCENEMANAGER->changeScene("main");



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
	SOUNDMANAGER->update();
	
}



void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	   	 
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());


	this->getBackBuffer()->render(getHDC());
}
