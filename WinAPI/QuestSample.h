#pragma once
#include "Quest.h"

class Quest;
/*
ť(queue)
ť�� ����Ʈ�� �������� ���ð� �ٸ��� ���� ó���� �� �����Ͱ� ó���� ������ FIFO �ڷ� ����
������ �Ͼ�� ���� ��(rear), ������ �Ͼ�� ���� ��(front)��� �Ѵ�.

����Ʈ ť, CPU �����ٸ�, ������ ����, *BFS(�ʺ�켱Ž��) ���� �� �� ����� �����Ѵ�(���� �Ⱦ���)

front()
back()
push()
size()
empty()
*/
class QuestSample
{
private:
	queue <Quest*> _quest;


public:
	QuestSample() {}
	~QuestSample() {}

	void init(void);
	void questSetup(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() { return &this->_quest; }

};

