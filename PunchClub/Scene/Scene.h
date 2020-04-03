#pragma once
#include "Base/GameNode.h"
#include "UI/InGameUI.h"
#include "Object/Player.h"
#include "Object/Facility.h"
typedef vector<SCENE_TYPE> vSceneList;
class Scene : public GameNode
{
protected:
	static vSceneList _sceneList;
protected:
	void update_scene();
	void change_scene();
	void add_currentScene_toList(SCENE_TYPE sceneType);
	SCENE_TYPE back_currentScene_toList();
	void delete_sceneList();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	Scene();
	~Scene();
};

