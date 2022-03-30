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
	

	// ���� ������ �޸��ּҰ� ���� ������ �ҿ����ϴٰ� ���´�.
	// C++�� Ÿ�Կ� �����ϱ� ����.
	// Ŭ���� ���漱�� -> ���������Ŭ��� �� ��

	sprintf(str, "%s", node->getName().c_str());
	TextOut(getMemDC(), 200, 150, str, strlen(str));

	sprintf(str, "���� : %s", node->getDescription().c_str());
	TextOut(getMemDC(), 200, 200, str, strlen(str));

	sprintf(str, "���� �̸� : %s", node->getMonsterName().c_str());
	TextOut(getMemDC(), 200, 250, str, strlen(str));

	sprintf(str, "óġ�ؾ� �� ���� : %d", node->getMonster());
	TextOut(getMemDC(), 200, 300, str, strlen(str));

	sprintf(str, "����Ʈ üũ : %s", node->getQuestCheck().c_str());
	TextOut(getMemDC(), 200, 350, str, strlen(str));

	sprintf(str, "����ġ ���� : %d exp", node->getExp());
	TextOut(getMemDC(), 200, 400, str, strlen(str));

	sprintf(str, "����Ʈ ���� ��� : %d gold", node->getGold());
	TextOut(getMemDC(), 200, 450, str, strlen(str));

	sprintf(str, "����Ʈ ���� ������ : %s", node->getItem().c_str());
	TextOut(getMemDC(), 200, 500, str, strlen(str));


}

void JsonDataScene::currentQuest()
{
}
