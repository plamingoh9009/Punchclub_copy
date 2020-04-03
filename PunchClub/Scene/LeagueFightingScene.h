#pragma once
#include "Scene.h"
class LeagueFightingScene: public Scene
{
private:
	Image * _bg[5];
	int _bg_idx = 0;
	Image * _fight_text;
	Image * _player[4];
	int _player_idx = 0;
	POINT _player_center;
	Image * _enemy[3];

	double _timer = 0;
protected:
	HRESULT init_bgs();
	void delete_bgs();
	HRESULT init_fight_text();
	HRESULT init_player();
	void draw_player();
	void delete_player();
	void update_player();
	HRESULT init_enemy();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	LeagueFightingScene();
	~LeagueFightingScene();
};

