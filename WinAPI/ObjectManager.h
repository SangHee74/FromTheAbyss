#pragma once
#include "SingletonBase.h"


class ObjectManager : public SingletonBase<ObjectManager>
{
private:



	// ������Ʈ 
	// 1. �� ���� ������Ʈ(����, �� ��) / ���� / �÷��̾�



public:
	ObjectManager() {}
	~ObjectManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


};

