#pragma once
#include "Base/SingletonBase.h"

class GameNode;
class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*> mSceneList;
private:
	static GameNode* _currentScene;
	//목록
	mSceneList _mSceneList;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	//씬추가하기
	GameNode* addScene(string sceneName, GameNode* scene);
	HRESULT changeScene(string sceneName);
public:
	SceneManager();
	~SceneManager();
};

