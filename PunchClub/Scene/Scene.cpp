#include "stdafx.h"
#include "Scene.h"

vSceneList Scene::_sceneList;
void Scene::update_scene()
{
	// 노드에서 업데이트 받아온다.
	update_checkDebugMode();
	update_checkClicked();
}
void Scene::change_scene()
{
	SCENE_TYPE type;
	if (_scene_forChange == SCENE_BACK)
	{
		type = back_currentScene_toList();
		change_currentScene(type);
	}
	else if (_scene_forChange != SCENE_EMPTY)
	{
		type = _scene_forChange;
		switch (type)
		{
		case SCENE_TITLE:
			delete_sceneList();
			break;
		}
		change_currentScene(type);
	}
}
void Scene::add_currentScene_toList(SCENE_TYPE sceneType)
{
	_scene_forChange = SCENE_EMPTY;
	_sceneList.push_back(sceneType);
}
SCENE_TYPE Scene::back_currentScene_toList()
{
	SCENE_TYPE type;
	_sceneList.pop_back();
	type = _sceneList.back();
	_sceneList.pop_back();
	return type;
}
void Scene::delete_sceneList()
{
	auto iter = _sceneList.begin();
	for (; iter != _sceneList.end();)
	{
		iter = _sceneList.erase(iter);
	}
	swap(_sceneList, vSceneList());
}
HRESULT Scene::init()
{
	return S_OK;
}
void Scene::release()
{
}
void Scene::update()
{
}
void Scene::render()
{
}
Scene::Scene()
{
}
Scene::~Scene()
{
}
