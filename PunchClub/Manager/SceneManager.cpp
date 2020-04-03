#include "stdafx.h"
#include "SceneManager.h"
#include "Base/GameNode.h"

//현재씬을 널값으로 초기화 하자.
GameNode* SceneManager::_currentScene = nullptr;
HRESULT SceneManager::init() { return S_OK; }
void SceneManager::release()
{
	auto iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		//삭제
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene)iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	_mSceneList.clear();
}
void SceneManager::update()
{
	if (_currentScene)
	{
		_currentScene->update();
	}
}
void SceneManager::render()
{
	if (_currentScene)_currentScene->render();
}
GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	if (!scene)return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}
HRESULT SceneManager::changeScene(string sceneName)
{
	auto find = _mSceneList.find(sceneName);

	//못찾으면 E_FAIL
	if (find == _mSceneList.end())return E_FAIL;

	//바꾸려는씬이 현재씬이랑 같아도 E_FAIL
	if (find->second == _currentScene)return E_FAIL;

	//여기까지 왔다면 문제가 없다 즉 씬을 초기화하고 변경하자.
	if (SUCCEEDED(find->second->init()))
	{
		//혹시 기존에 씬이 있다면 릴리즈
		if (_currentScene)_currentScene->release();

		_currentScene = find->second;
		return S_OK;
	}
	return E_FAIL;
}
SceneManager::SceneManager()
{
}
SceneManager::~SceneManager()
{
}
