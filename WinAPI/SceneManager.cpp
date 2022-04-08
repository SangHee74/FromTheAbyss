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
	_fadeOut.blackImg = IMAGEMANAGER->findImage("black");
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

	// 포인터는 메모리에 직접 접근이기 때문에 항상 예외처리로 신경 써줘야 한다.
	// 이를 위한 라인 수에 연연하지 말것.
	// for each 사용 시 .( 권장  X)  
	/*
	for each(auto scene in _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
	*/
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

// 씬 변경 
// 페이드 아웃 추가 
HRESULT SceneManager::changeScene(string sceneName)
{
	// 변경하려는 씬을 찾는다.
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	// 찾는데 성공하고, 초기화가 됬다면 
	if (SUCCEEDED(find->second->init()))
	{
		// 페이드 아웃


		// 페이드 아웃 후 씬 변경
		// 씬을 바꿔도 변수가 계속 남아있게 설계를 고민하자 
		// 익스턴 스태틱 등등 
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

