#pragma once
#include "Scene.h"
class WorkScene: public Scene
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	WorkScene();
	~WorkScene();
};
