#pragma once
#include "SingletonBase.h"

class GameNode; 

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	// static name* : 
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;
public:

public:
	SceneManager() {}
	~SceneManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// 씬 추가
	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	// 씬 교체
	HRESULT changeScene(string sceneName);

	// 로딩 스레드 함수
	friend DWORD CALLBACK loadingThread(LPVOID prc);

 
};

