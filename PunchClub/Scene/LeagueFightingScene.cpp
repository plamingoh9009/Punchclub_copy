#include "stdafx.h"
#include "LeagueFightingScene.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
HRESULT LeagueFightingScene::init_bgs()
{
	string path;
	_bg[0] = new Image;
	path = _imgPath + "league_bg.bmp";
	_bg[0]->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(384 * GAME_MULTIPLE));
	_bg[1] = new Image;
	path = _imgPath + "prisonyard_bg.bmp";
	_bg[1]->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(384 * GAME_MULTIPLE));
	_bg[2] = new Image;
	path = _imgPath + "ring_ussr_bg.bmp";
	_bg[2]->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(384 * GAME_MULTIPLE));
	_bg[3] = new Image;
	path = _imgPath + "roof_bg.bmp";
	_bg[3]->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(384 * GAME_MULTIPLE));
	_bg[4] = new Image;
	path = _imgPath + "sidewalk_bg.bmp";
	_bg[4]->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(384 * GAME_MULTIPLE));

	_bg_idx = RAND->get_int(5);
	return S_OK;
}
void LeagueFightingScene::delete_bgs()
{
	for (int i = 0; i < 5; i++)
	{
		Release(_bg[i]);
	}
}

HRESULT LeagueFightingScene::init_fight_text()
{
	string path;
	_fight_text = new Image;
	path = _imgPath + "fight_pixel_text.bmp";
	return S_OK;
}
HRESULT LeagueFightingScene::init_player()
{
	string path;
	_player[0] = new Image;
	path = _imgPath + "player_fight_idle.bmp";
	_player[0]->init(path.c_str(), (int)(126 * GAME_MULTIPLE), (int)(75 * GAME_MULTIPLE), 3, 1);
	_player[0]->set_frameSection(1, 0, 2, 0.3f);
	_player[1] = new Image;
	path = _imgPath + "player_block.bmp";
	_player[1]->init(path.c_str(), (int)(82 * GAME_MULTIPLE), (int)(73 * GAME_MULTIPLE), 2, 1);
	_player[1]->set_frameSection(1, 0, 1, 0.3f);
	_player[2] = new Image;
	path = _imgPath + "player_punch.bmp";
	_player[2]->init(path.c_str(), (int)(275 * GAME_MULTIPLE), (int)(75 * GAME_MULTIPLE), 5, 1);
	_player[2]->set_frameSection(1, 0, 4, 0.3f);
	_player[3] = new Image;
	path = _imgPath + "player_uppercut.bmp";
	_player[3]->init(path.c_str(), (int)(150 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 3, 1);
	_player[3]->set_frameSection(1, 0, 2, 0.3f);
	return S_OK;
}
void LeagueFightingScene::draw_player()
{
	_player[_player_idx]->frameRender(get_memDC());
}
void LeagueFightingScene::delete_player()
{
	for (int i = 0; i < 4; i++)
	{
		Release(_player[_player_idx]);
	}
}
void LeagueFightingScene::update_player()
{
	_player[_player_idx]->frameUpdate(false);
}
HRESULT LeagueFightingScene::init_enemy()
{
	string path;
	_enemy[0] = new Image;
	path = _imgPath + "enemyA_fight_idle.bmp";
	_enemy[0]->init(path.c_str(), (int)(126 * GAME_MULTIPLE), (int)(75 * GAME_MULTIPLE), 3, 1);
	_enemy[0]->set_frameSection(1, 0, 2, 0.3f);
	_enemy[1] = new Image;
	path = _imgPath + "enemyA_block.bmp";
	_enemy[1]->init(path.c_str(), (int)(82 * GAME_MULTIPLE), (int)(73 * GAME_MULTIPLE), 2, 1);
	_enemy[1]->set_frameSection(1, 0, 1, 0.3f);
	return S_OK;
}

void LeagueFightingScene::draw_enemy()
{
	_enemy[_enemy_idx]->frameRender(get_memDC());
}

void LeagueFightingScene::delete_enemy()
{
	Release(_enemy[0]);
	Release(_enemy[1]);
}

void LeagueFightingScene::update_enemy()
{
	_enemy[_enemy_idx]->frameUpdate(false);
}

void LeagueFightingScene::init_positions()
{
	POINT center;

	switch (_bg_idx)
	{
	case 0:
		center.x = (LONG)(WIN_HALF_W);
		center.y = (LONG)(WIN_HALF_H - 20);
		break;
	default:
		center.x = (LONG)(WIN_HALF_W);
		center.y = (LONG)(WIN_HALF_H + 100);
		break;
	}
	_player_center = PointMake(center.x - 45, center.y);
	_player[_player_idx]->set_center(_player_center);
	_enemy_center = PointMake(center.x + 45, center.y);
	_enemy[_enemy_idx]->set_center(_enemy_center);
}

void LeagueFightingScene::setup_positions(int playerIdx, int enemyIdx)
{
	_player[playerIdx]->set_center(_player_center);
	_enemy[enemyIdx]->set_center(_enemy_center);
}
void LeagueFightingScene::setup_fight_actions()
{
	// 플레이어, 에너지 둘 중에 더 긴 프레임이 끝난 경우
	int playerMaxFrame = _player[_player_idx]->get_maxFrameX();
	int enemyMaxFrame = _enemy[_enemy_idx]->get_maxFrameX();
	if (playerMaxFrame >= enemyMaxFrame)
	{
		if (_player[_player_idx]->is_end_firstSection())
		{
			settle_result();
			_player_idx = RAND->get_int(4);
			_enemy_idx = RAND->get_int(2);
			setup_positions(_player_idx, _enemy_idx);
			_doneAction = true;
		}
		else if (_player[_player_idx]->get_frameX() == 0)
		{
			_doneAction = false;
		}
	}
	else
	{
		if (_enemy[_enemy_idx]->is_end_firstSection())
		{
			settle_result();
			_player_idx = RAND->get_int(4);
			_enemy_idx = RAND->get_int(2);
			setup_positions(_player_idx, _enemy_idx);
			_doneAction = true;
		}
		else if (_enemy[_enemy_idx]->get_frameX() == 0)
		{
			_doneAction = false;
		}
	}
}

void LeagueFightingScene::settle_result()
{
	//if()
}

HRESULT LeagueFightingScene::init()
{
	add_currentScene_toList(SCENE_LEAGUE_FIGHT);
	set_imgPath("League/");
	init_bgs();
	init_fight_text();
	init_player();
	init_enemy();
	init_positions();
	INGAME_UI->init(UI_LEAGUE);
	return S_OK;
}
void LeagueFightingScene::release()
{
	delete_bgs();
	delete_player();
	delete_enemy();
}
void LeagueFightingScene::update()
{
	update_scene();
	update_player();
	update_enemy();
	setup_fight_actions();
	INGAME_UI->update();
	change_scene();
}
void LeagueFightingScene::render()
{
	Draw(_bg[_bg_idx], get_memDC());
	draw_player();
	draw_enemy();
	INGAME_UI->render();
}
LeagueFightingScene::LeagueFightingScene()
{
}
LeagueFightingScene::~LeagueFightingScene()
{
}