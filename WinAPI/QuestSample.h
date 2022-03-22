#pragma once
#include "Quest.h"

class Quest;
/*
큐(queue)
큐는 리스트의 일종으로 스택과 다르게 가장 처음에 들어간 데이터가 처음에 나오는 FIFO 자료 구조
삽입이 일어나는 쪽을 뒤(rear), 삭제가 일어나는 쪽을 앞(front)라고 한다.

프린트 큐, CPU 스케줄링, 데이터 버퍼, *BFS(너비우선탐색) 등을 할 때 고려해 봐야한다(쓸지 안쓸지)

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

