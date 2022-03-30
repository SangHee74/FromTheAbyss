#include "Stdafx.h"
#include "JsonDataScene.h"

HRESULT JsonDataScene::init(void)
{
	_questSample = new QuestSample;
	_questSample->init();
	return S_OK;
}

void JsonDataScene::release(void)
{
}

void JsonDataScene::update(void)
{
	// Do Noting
}

void JsonDataScene::render(void)
{
	questPopUp();
}

void JsonDataScene::questPopUp()
{
	char str[256];
	queue<Quest*>* temp = _questSample->getQuest();
	Quest* node = temp->front();
	

	// 빌드 전까지 메모리주소가 없기 때문에 불완전하다고 나온다.
	// C++이 타입에 엄격하기 때문.
	// 클래스 전방선언 -> 헤더파일인클루드 할 것

	sprintf(str, "%s", node->getName().c_str());
	TextOut(getMemDC(), 200, 150, str, strlen(str));

	sprintf(str, "개요 : %s", node->getDescription().c_str());
	TextOut(getMemDC(), 200, 200, str, strlen(str));

	sprintf(str, "몬스터 이름 : %s", node->getMonsterName().c_str());
	TextOut(getMemDC(), 200, 250, str, strlen(str));

	sprintf(str, "처치해야 할 몬스터 : %d", node->getMonster());
	TextOut(getMemDC(), 200, 300, str, strlen(str));

	sprintf(str, "퀘스트 체크 : %s", node->getQuestCheck().c_str());
	TextOut(getMemDC(), 200, 350, str, strlen(str));

	sprintf(str, "경험치 보상 : %d exp", node->getExp());
	TextOut(getMemDC(), 200, 400, str, strlen(str));

	sprintf(str, "퀘스트 보상 골드 : %d gold", node->getGold());
	TextOut(getMemDC(), 200, 450, str, strlen(str));

	sprintf(str, "퀘스트 보상 아이템 : %s", node->getItem().c_str());
	TextOut(getMemDC(), 200, 500, str, strlen(str));


}

void JsonDataScene::currentQuest()
{
}
