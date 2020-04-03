#include "stdafx.h"
#include "LeagueWaitingScene.h"
#include "Object/Player.h"
//==========================================
//##			Prefight Window			  ##
//==========================================
void LeagueWaitingScene::init_prefight_window()
{
	string path;
	POINT center;
	path = _imgPath + "prefight_vs.bmp";
	_pfVs = new Image;
	_pfVs->init(path.c_str(), (int)(46 * GAME_MULTIPLE), (int)(34 * GAME_MULTIPLE));
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(WIN_HALF_H - _pfVs->get_height());
	_pfVs_rc = RectMakeCenter(center.x, center.y, _pfVs->get_width(), _pfVs->get_height());
	_vs_center = center;
	// Window Image
	path = _imgPath + "prefight_window.bmp";
	_pfWindow = new Image;
	_pfWindow->init(path.c_str(), (int)(102 * GAME_MULTIPLE), (int)(108 * GAME_MULTIPLE));
}
void LeagueWaitingScene::draw_prefight_window()
{
	_pfVs->render(get_memDC(), _pfVs_rc.left, _pfVs_rc.top);
	_pfWindow->render(get_memDC(), _player_window_rc.left, _player_window_rc.top);
	_pfWindow->render(get_memDC(), _enemy_window_rc.left, _enemy_window_rc.top);
}
void LeagueWaitingScene::delete_prefight_window()
{
	Release(_pfVs);
	Release(_pfWindow);
}
HRESULT LeagueWaitingScene::init_fightStat()
{
	POINT center;
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(WIN_HALF_H - _pfVs->get_height());
	// Player Side
	center.x = (LONG)(_vs_center.x - _pfWindow->get_width());
	_player_window_rc = RectMakeCenter(center.x, center.y,
		_pfWindow->get_width(), _pfWindow->get_height());
	_player_window_center = center;
	center.x = (LONG)(center.x - _pfWindow->get_width() * 1.375);
	_playerStat = new PrefightStat;
	_playerStat->init();
	_playerStat->set_window(center, "Player");
	_playerStat->set_stat(PLAYER->get_str(), PLAYER->get_stm(), PLAYER->get_agl());
	// Enemy Side
	center.x = (LONG)(_vs_center.x + _pfWindow->get_width() - 5);
	_enemy_window_rc = RectMakeCenter(center.x, center.y,
		_pfWindow->get_width(), _pfWindow->get_height());
	_enemy_window_center = center;
	center.x = (LONG)(center.x + _pfWindow->get_width() * 1.375 + 5);
	_enemyStat = new PrefightStat;
	_enemyStat->init();
	_enemyStat->set_window(center, "Enemy", false);
	_enemyStat->set_stat(
		(int)_enemyStat->get_enemyStat().str, 
		(int)_enemyStat->get_enemyStat().stm, 
		(int)_enemyStat->get_enemyStat().agl);
	return S_OK;
}
void LeagueWaitingScene::draw_fightStat()
{
	Draw(_playerStat);
	Draw(_enemyStat);
}
void LeagueWaitingScene::delete_fightStat()
{
	Release(_playerStat);
	Release(_enemyStat);
}
void LeagueWaitingScene::update_fightStat()
{
}
//==========================================
//##			Charactor Image			  ##
//==========================================
void LeagueWaitingScene::init_picture()
{
	set_imgPath("League/");
	string path = _imgPath + "player_fight_idle.bmp";
	_player_img = new Image;
	_player_img->init(path.c_str(), (int)(126 * GAME_MULTIPLE), (int)(75 * GAME_MULTIPLE), 3, 1);
	_player_rc = RectMakeCenter(
		_player_window_center.x, _player_window_center.y,
		_player_img->get_frameWidth(), _player_img->get_frameHeight());
	_player_img->set_frameSection(1, 0, 2, 0.25f);
	path = _imgPath + "enemyA_fight_idle.bmp";
	_enemy_img = new Image;
	_enemy_img->init(path.c_str(), (int)(126 * GAME_MULTIPLE), (int)(75 * GAME_MULTIPLE), 3, 1);
	_enemy_rc = RectMakeCenter(
		_enemy_window_center.x, _enemy_window_center.y,
		_enemy_img->get_frameWidth(), _enemy_img->get_frameHeight());
	_enemy_img->set_frameSection(1, 2, 0, 0.3f);
}
void LeagueWaitingScene::draw_picture()
{
	_player_img->frameRender(get_memDC(), _player_rc.left, _player_rc.top);
	_enemy_img->frameRender(get_memDC(), _enemy_rc.left, _enemy_rc.top);
}
void LeagueWaitingScene::update_picture()
{
	_player_img->frameUpdate(false);
	_enemy_img->frameUpdate(false, true);
}
void LeagueWaitingScene::delete_picture()
{
	Release(_player_img);
	Release(_enemy_img);
}
//==========================================
//##			Prefight Skill			  ##
//==========================================
void LeagueWaitingScene::init_prefight_skill()
{
	// Player Side
	POINT center;
	_player_skill = new PrefightSkillSet;
	_player_skill->init();
	center.x = (LONG)(_player_window_center.x - _player_skill->get_width() * 0.475);
	center.y = (LONG)(_player_window_center.y + _player_skill->get_height() * 2.75);
	_player_skill->set_center(center);
	// Enemy Side
	_enemy_skill = new PrefightSkillSet;
	_enemy_skill->init();
	center.x = (LONG)(_enemy_window_center.x + _enemy_skill->get_width() * 0.475);
	center.y = (LONG)(_enemy_window_center.y + _enemy_skill->get_height() * 2.75);
	_enemy_skill->set_center(center);
}
void LeagueWaitingScene::draw_prefight_skill()
{
	_player_skill->render();
	_enemy_skill->render();
}
void LeagueWaitingScene::delete_prefight_skill()
{
	_player_skill->release();
	_player_skill = nullptr;
	_enemy_skill->release();
	_enemy_skill = nullptr;
}

HRESULT LeagueWaitingScene::init()
{
	add_currentScene_toList(SCENE_LEAGUE_WAIT);
	set_imgPath("UI/Fight/");
	string path = _imgPath + "Window_back.bmp";
	_bg = new Image;
	_bg->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(383 * GAME_MULTIPLE));
	INGAME_UI->init(UI_LEAGUE);
	init_prefight_window();
	init_fightStat();
	// Window Picture
	init_picture();
	// Skill set
	init_prefight_skill();
	// Button
	POINT center;
	center.x = (LONG)(_vs_center.x);
	center.y = (LONG)(WINSIZEY - _pfVs->get_height() * 0.6);
	_fight_button = new Button(BUTTON::BTN_RED_LONG);
	_fight_button->init();
	_fight_button->set_center(center);
	_fight_button->set_text_toButton("ÆÄÀÌÆ®");
	return S_OK;
}
void LeagueWaitingScene::release()
{
	Release(_bg);
	delete_prefight_window();
	delete_fightStat();
	delete_picture();
	delete_prefight_skill();
	Release(_fight_button);
}
void LeagueWaitingScene::update()
{
	update_scene();
	update_picture();
	if (_fight_button->is_clickButton())
	{
		_scene_forChange = SCENE_LEAGUE_FIGHT;
	}
	else
	{
		_fight_button->update();
	}
	INGAME_UI->update();
	change_scene();
}
void LeagueWaitingScene::render()
{
	_bg->render(get_memDC(), 0, 0);
	draw_prefight_window();
	draw_fightStat();
	draw_picture();
	draw_prefight_skill();
	_fight_button->render();
	INGAME_UI->render();
}
LeagueWaitingScene::LeagueWaitingScene()
{
}
LeagueWaitingScene::~LeagueWaitingScene()
{
}
