#pragma once
#include "Stage.h"
class Stage11 : public Stage
{
private:
public:
	Stage11() {}
	~Stage11() {}
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void portalOn();

};

