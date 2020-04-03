#include "stdafx.h"
#include "SkillTreeScene.h"


HRESULT SkillTreeScene::init()
{
	add_currentScene_toList(SCENE_SKILLTREE);
	INGAME_UI->init();
	INGAME_UI->set_fRedButton(true);
	return S_OK;
}
void SkillTreeScene::release()
{
}
void SkillTreeScene::update()
{
	update_scene();
	INGAME_UI->update();
	change_scene();
}
void SkillTreeScene::render()
{
	INGAME_UI->render();
}
SkillTreeScene::SkillTreeScene()
{
}
SkillTreeScene::~SkillTreeScene()
{
}
