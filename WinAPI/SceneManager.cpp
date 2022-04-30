#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;   
 
DWORD CALLBACK loadingThread(LPVOID prc)
{
	// 교체될 씬의 함수 실행
	SceneManager::_readyScene->init();

	// 현재 씬을 교체될 씬으로 변경
	SceneManager::_currentScene = SceneManager::_readyScene;

	// 로딩 씬 해제
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;
	// 로딩클래스를 만들어 로딩씬과 연결 필요
	return 0;
}

HRESULT SceneManager::init(void)
{
	_currentScene = nullptr;
	_loadingScene = nullptr;
	_readyScene = nullptr;
	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();
	
	// 로딩 씬 -> 교체 대기중인 씬 ->현재씬 , 많지 않다(for 사용)
	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != nullptr)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mSceneList.clear();

}

void SceneManager::update(void)
{
	// 현재씬이 존재하면 현재 씬 갱신 
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	// 현재씬이 존재하면 현재 씬 렌더 
	if (_currentScene) _currentScene->render();

}

// 씬 추가
GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	// 씬이 없으면 리턴
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

GameNode * SceneManager::addLoadingScene(string loadingSceneName, GameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

// 플레이어만 인자타입(매개변수로 남기고 나머지는 싹 지운 후 체인지 씬)
HRESULT SceneManager::changeScene(string sceneName)
{
	// 변경하려는 씬을 찾는다.
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	// 찾는데 성공하고, 초기화가 됬다면 
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

