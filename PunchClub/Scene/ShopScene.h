#pragma once
#include "Scene.h"
#include "UI/InGameUI.h"
#include "Object/Npc.h"
class ShopScene: public Scene
{
private:
	Image * _bg;
	Npc * _shop;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	ShopScene();
	~ShopScene();
};

