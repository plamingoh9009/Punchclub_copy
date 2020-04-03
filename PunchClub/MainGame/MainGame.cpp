#include "stdafx.h"
#include "MainGame.h"

void MainGame::add_scenes_toManager()
{
	SCENEMANAGER->addScene("Title", new TitleScene());
	SCENEMANAGER->addScene("Home", new HomeScene());
	SCENEMANAGER->addScene("HudMap", new HudMapScene());
	SCENEMANAGER->addScene("Gym", new GymScene());
	SCENEMANAGER->addScene("Shop", new ShopScene());
	SCENEMANAGER->addScene("SkillTree", new SkillTreeScene());
	SCENEMANAGER->addScene("LeagueWait", new LeagueWaitingScene());
	SCENEMANAGER->addScene("LeagueFight", new LeagueFightingScene());
}

HRESULT MainGame::init()
{
	GameNode::init(true);
	add_scenes_toManager();
	SCENEMANAGER->changeScene("Home");
	return S_OK;
}
void MainGame::release()
{
	SCENEMANAGER->release();
	GameNode::release();
}
void MainGame::update()
{
	GameNode::update();
	SCENEMANAGER->update();
}
void MainGame::render()
{
	//��� ��Ʈ��
	PatBlt(get_memDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=====================================================
	SCENEMANAGER->render();
	if (_fDebug) { TIMEMANAGER->render(get_memDC()); }
	//=====================================================
	//������� ������ HDC�� �׸���.(��������!!)
	this->get_backBuffer()->render(get_hdc(), 0, 0);
}
MainGame::MainGame()
{
}
MainGame::~MainGame()
{
}