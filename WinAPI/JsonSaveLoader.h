#pragma once
#pragma "SingletonBase.h"

class JsonSaveLoader : public SingletonBase <JsonSaveLoader>
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWithFileStream(char* fileName);


public:
	
	HRESULT init(void);
	void release(void);

	JsonSaveLoader() {}
	~JsonSaveLoader() {}
	
	void saveJsonFile(char* fileName, Json::Value root);

	Json::Value loadJsonFile(char* fileName);

};
