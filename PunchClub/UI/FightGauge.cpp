#include "stdafx.h"
#include "FightGauge.h"
#include "Object/Player.h"
void FightGauge::init_player_bars()
{
	string path;
	POINT center;
	// ========================================
	// ***		Player Hp bar				***
	// ========================================
	_playerHp = new Gauge(GAUGE::GG_PLAYER_HP);
	_playerHp->init();
	// Set position
	center.x = (LONG)(0 + _playerHp->get_width() * 0.6);
	center.y = (LONG)(_round_center.y - 10);
	_playerHp->set_center(center);

	PLAYER->init_playerHp();
	
	// ========================================
	// ***		Player energy bar			***
	// ========================================
	_playerNrg = new Gauge(GAUGE::GG_ENERGY);
	_playerNrg->init();
	center.x = (LONG)(_playerHp->get_center().x - 112);
	center.y = (LONG)(_playerHp->get_center().y + 35);
	_playerNrg->set_center(center);
}
void FightGauge::init_enemy_bars()
{
	string path;
	POINT center;
	// ========================================
	// ***		Enemy Hp bar				***
	// ========================================
	_enemyHp = new Gauge(GAUGE::GG_ENEMY_HP);
	_enemyHp->init();
	center.x = (LONG)(WINSIZEX - _enemyHp->get_width() * 0.6);
	center.y = (LONG)(_round_center.y - 10);
	_enemyHp->set_center(center);

	if (_enemy != nullptr)
	{
		_enemy->init();
	}
	// ========================================
	// ***		Enemy energy bar			***
	// ========================================
	_enemyNrg = new Gauge(GAUGE::GG_ENERGY);
	_enemyNrg->init();
	center.x = (LONG)(_enemyHp->get_center().x + 112);
	center.y = (LONG)(_enemyHp->get_center().y + 35);
	_enemyNrg->set_center(center);
}

void FightGauge::init_round()
{
	string path;
	POINT center;
	path = _imgPath + "round_counter_back.bmp";
	_round_back = new Image;
	_round_back->init(path.c_str(), (int)(36 * GAME_MULTIPLE), (int)(36 * GAME_MULTIPLE));
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(0 + _round_back->get_height() * 1);
	_round_back_rc = RectMakeCenter(center.x, center.y, 
		_round_back->get_width(), _round_back->get_height());
	path = _imgPath + "round_counter_full.bmp";
	_round_fore = new Image;
	_round_fore->init(path.c_str(), (int)(34 * GAME_MULTIPLE), (int)(34 * GAME_MULTIPLE));
	_round_fore_rc = RectMakeCenter(center.x, center.y,
		_round_fore->get_width(), _round_fore->get_height());
	_round_center = center;
	// 글씨
	_round_title = "라운드";
	_round_desc = "(총 10 라운드)";
	_round_num = "1";
}
void FightGauge::draw_round()
{
	_round_back->render(get_memDC(), _round_back_rc.left, _round_back_rc.top);
	FontTextOut(get_memDC(), _round_center.x - 10, _round_center.y - 12, _round_num.c_str(),
		"휴먼매직체", 35, RGB(254, 254, 254));
	FontTextOut(get_memDC(), _round_center.x - 25, _round_center.y - 50, _round_title.c_str(),
		"휴먼편지체", 25, RGB(253, 199, 56));
	FontTextOut(get_memDC(), _round_center.x - 55, _round_center.y + 25, _round_desc.c_str(),
		"휴먼편지체", 25, RGB(253, 199, 56));
}
void FightGauge::update_round()
{
}
void FightGauge::delete_round()
{
	_round_back->release();
	_round_back = nullptr;
	_round_fore->release();
	_round_fore = nullptr;
}

void FightGauge::sync_player_bars()
{
	double maxHp, currentHp;
	double currentNrg;
	// Hp를 볼 수 있도록 MyText를 추가한다.
	maxHp = PLAYER->get_stat().maxHp;
	currentHp = PLAYER->get_stat().currentHp;
	_playerHp->set_text_toGauge(currentHp, maxHp, _playerHp->get_type());
	// currentHp를 게이지 width와 연동한다.
	currentHp = 1000 * (currentHp / maxHp);
	_playerHp->sync_gauge_fromValue(currentHp);

	currentNrg = PLAYER->get_stat().currentNrg;
	_playerNrg->set_text_toGauge((int)(currentNrg / 10.0), 100, _playerNrg->get_type());
	_playerNrg->sync_gauge_fromValue(currentNrg);
}
void FightGauge::sync_enemy_bars()
{
	double maxHp, currentHp;
	double currentNrg;
	// Hp를 볼 수 있도록 MyText를 추가한다.
	maxHp = _enemy->get_stat().maxHp;
	currentHp = _enemy->get_stat().currentHp;
	_enemyHp->set_text_toGauge(currentHp, maxHp, _enemyHp->get_type());
	// currentHp를 게이지 width와 연동한다.
	currentHp = 1000 * (currentHp / maxHp);
	_enemyHp->sync_gauge_fromValue(currentHp);

	currentNrg = _enemy->get_stat().currentNrg;
	_enemyNrg->set_text_toGauge((int)(currentNrg / 10.0), 100, _enemyNrg->get_type());
	_enemyNrg->sync_gauge_fromValue(currentNrg);
}

HRESULT FightGauge::init()
{
	set_imgPath("UI/Fight/");
	init_round();
	init_player_bars();
	init_enemy_bars();
	return S_OK;
}
void FightGauge::release()
{
	delete_round();
	Release(_playerHp);
	Release(_playerNrg);
	Release(_enemyHp);
	Release(_enemyNrg);
}
void FightGauge::update()
{
	update_round();
	sync_player_bars();
	sync_enemy_bars();
}
void FightGauge::render()
{
	draw_round();
	Draw(_playerHp);
	Draw(_playerNrg);
	Draw(_enemyHp);
	Draw(_enemyNrg);
}
FightGauge::FightGauge()
{
}
FightGauge::~FightGauge()
{
}