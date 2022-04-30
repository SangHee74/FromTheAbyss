#pragma once
#include"SingletonBase.h"


#define SAVE_BUFFER 30000
#define LOAD_BUFFER 30000

class TextDataManager : public SingletonBase<TextDataManager>
{
private:

public:
	HRESULT init(void);
	void release(void);

	void save(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	vector<string> load(const char* fileName);
	vector<string> charArrySeparation(char charArray[]);

	TextDataManager() {}
	~TextDataManager() {}
};

