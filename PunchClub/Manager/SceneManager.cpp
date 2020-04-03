#include "stdafx.h"
#include "SceneManager.h"
#include "Base/GameNode.h"

//������� �ΰ����� �ʱ�ȭ ����.
GameNode* SceneManager::_currentScene = nullptr;
HRESULT SceneManager::init() { return S_OK; }
void SceneManager::release()
{
	auto iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		//����
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

	//��ã���� E_FAIL
	if (find == _mSceneList.end())return E_FAIL;

	//�ٲٷ��¾��� ������̶� ���Ƶ� E_FAIL
	if (find->second == _currentScene)return E_FAIL;

	//������� �Դٸ� ������ ���� �� ���� �ʱ�ȭ�ϰ� ��������.
	if (SUCCEEDED(find->second->init()))
	{
		//Ȥ�� ������ ���� �ִٸ� ������
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
