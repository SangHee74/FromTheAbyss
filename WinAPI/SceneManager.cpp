#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;   
 
DWORD CALLBACK loadingThread(LPVOID prc)
{
	// ��ü�� ���� �Լ� ����
	SceneManager::_readyScene->init();

	// ���� ���� ��ü�� ������ ����
	SceneManager::_currentScene = SceneManager::_readyScene;

	// �ε� �� ����
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;
	// �ε�Ŭ������ ����� �ε����� ���� �ʿ�
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

	
	// �ε� �� -> ��ü ������� �� ->����� , ���� �ʴ�(for ���)
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

	// �����ʹ� �޸𸮿� ���� �����̱� ������ �׻� ����ó���� �Ű� ����� �Ѵ�.
	// �̸� ���� ���� ���� �������� ����.
	// for each ��� �� .( ����  X)  
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
	// ������� �����ϸ� ���� �� ���� 
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	// ������� �����ϸ� ���� �� ���� 
	if (_currentScene) _currentScene->render();

}

// �� �߰�
GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	// ���� ������ ����
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

// �� ���� 
// ���̵� �ƿ� �߰� 
HRESULT SceneManager::changeScene(string sceneName)
{
	// �����Ϸ��� ���� ã�´�.
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	// ã�µ� �����ϰ�, �ʱ�ȭ�� ��ٸ� 
	if (SUCCEEDED(find->second->init()))
	{
		// ���̵� �ƿ�


		// ���̵� �ƿ� �� �� ����
		// ���� �ٲ㵵 ������ ��� �����ְ� ���踦 ������� 
		// �ͽ��� ����ƽ ��� 
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

