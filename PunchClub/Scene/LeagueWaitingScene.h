#pragma once
#include "Scene.h"
#include "UI/InGameUI.h"
#include "UI/PrefightStat.h"
#include "UI/PrefightSkillSet.h"
class LeagueWaitingScene: public Scene
{
private:
	Image * _bg;
	// Prefight Window
	PrefightStat * _playerStat;
	PrefightStat * _enemyStat;
	Image * _pfWindow;
	Image * _pfVs;
	RECT _player_window_rc;
	RECT _enemy_window_rc;
	RECT _pfVs_rc;
	POINT _vs_center;
	POINT _player_window_center;
	POINT _enemy_window_center;
	// Prefight Picture
	Image * _player_img;
	Image * _enemy_img;
	RECT _player_rc;
	RECT _enemy_rc;
	// Prefight Skill set
	PrefightSkillSet * _player_skill;
	PrefightSkillSet * _enemy_skill;
	// Button
	Button * _fight_button;
protected:
	void init_prefight_window();
	void draw_prefight_window();
	void delete_prefight_window();
	HRESULT init_fightStat();
	void draw_fightStat();
	void delete_fightStat();
	void update_fightStat();
	void init_picture();
	void draw_picture();
	void update_picture();
	void delete_picture();
	void init_prefight_skill();
	void draw_prefight_skill();
	void delete_prefight_skill();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	LeagueWaitingScene();
	~LeagueWaitingScene();
};

