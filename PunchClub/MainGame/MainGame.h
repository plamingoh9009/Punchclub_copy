#pragma once
#include "Base/GameNode.h"
// 여기에 게임씬 추가
#include "Scene/TitleScene.h"
#include "Scene/HomeScene.h"
#include "Scene/HudMapScene.h"
#include "Scene/GymScene.h"
#include "Scene/ShopScene.h"
#include "Scene/SkillTreeScene.h"
#include "Scene/LeagueWaitingScene.h"
#include "Scene/LeagueFightingScene.h"
class MainGame: public GameNode
{
protected:
	void add_scenes_toManager();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
public:
	MainGame();
	~MainGame();
};

