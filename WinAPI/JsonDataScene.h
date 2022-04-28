#pragma once
#include "GameNode.h"
#include "QuestSample.h"

class JsonDataScene : public GameNode
{
private:
	QuestSample* _questSample;

	MainQuest* _mainQuestTest;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	JsonDataScene() {}
	~JsonDataScene() {}

	void questPopUp();
	void currentQuest();
};

