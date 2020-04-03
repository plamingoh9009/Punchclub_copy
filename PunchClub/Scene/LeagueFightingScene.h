#pragma once
#include "Scene.h"
class LeagueFightingScene: public Scene
{
private:
	Image * _bg[5];
	int _bg_idx = 0;
	Image * _fight_text;
	Image * _player[4];
	POINT _player_center;
	int _player_idx = 0;
	Image * _enemy[2];
	POINT _enemy_center;
	int _enemy_idx = 0;
	double _timer = 0;
	bool _doneAction = false;
protected:
	void setup_positions(int playerIdx, int enemyIdx);
	void setup_fight_actions();
	void settle_result();
protected:
	HRESULT init_bgs();
	void delete_bgs();
	HRESULT init_fight_text();
	// Player
	HRESULT init_player();
	void draw_player();
	void delete_player();
	void update_player();
	// Enemy
	HRESULT init_enemy();
	void draw_enemy();
	void delete_enemy();
	void update_enemy();
	// Position
	void init_positions();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	LeagueFightingScene();
	~LeagueFightingScene();
};

