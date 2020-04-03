#pragma once
#include "Gauge.h"
#include "Object/Enemy.h"
class FightGauge: public UI
{
	// 라운드 이미지
	Image * _round_back;
	Image * _round_fore;
	POINT _round_center;
	RECT _round_back_rc;
	RECT _round_fore_rc;
	string _round_title;
	string _round_desc;
	string _round_num;
	// 싸울때 쓰는 게이지
	Gauge * _playerHp;
	Gauge * _playerNrg;
	Gauge * _enemyHp;
	Gauge * _enemyNrg;
protected:
	void init_player_bars();
	void init_enemy_bars();

	void init_round();
	void draw_round();
	void update_round();
	void delete_round();

	void sync_player_bars();
	void sync_enemy_bars();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	FightGauge();
	~FightGauge();
};

