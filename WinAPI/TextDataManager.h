#pragma once
#include"SingletonBase.h"
//FILE* file;
//#include <fstream>
//#include <ofstr>
//Text(보안에 굉장히 취약), XML, INI, JSON


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

