#pragma once
#include "SingletonBase.h"

class ObjectManager : public SingletonBase<ObjectManager>
{
private:

public:
	ObjectManager() {}
	~ObjectManager() {}

	HRESULT init(void);
	void release(void);

	// 충돌처리, 렌더순서 정렬
};

