#pragma once
#include "SingletonBase.h"

// 게임노드가 필요하지만, 캡슐화(정보은닉:메인프로시저 등의 기능)을 위해 전방선언사용
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
	// friend : 단방향 선언, 복잡한 상속관계에서도 간편하게 사용 가능.(상속무시)
	// LPVOID : void* 형 (어떤 타입으로도 변환 가능)
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	// ㄴ 리팩토링 시 CALLBACK을 빼고 만든다 : 왜?
	// ㄴ 
};

