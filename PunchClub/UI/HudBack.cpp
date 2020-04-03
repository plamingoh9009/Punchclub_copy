#include "stdafx.h"
#include "HudBack.h"
#include "Object/Player.h"
void HudBack::update_datas_fromPlayer()
{
	update_gauges();
	_skillPoint.set_text(to_string(PLAYER->get_stat().skillPoint));
	_money.set_text(to_string(PLAYER->get_stat().money));
	update();
}

string HudBack::Stat(double stat)
{
	int result = (int)(stat / 1000);
	return to_string(result);
}

double HudBack::Exp(double stat)
{
	int result = (int)(stat);
	return (result % 1000);
}

HRESULT HudBack::init_gauges()
{
	POINT center;
	LONG blank;
	_health = new Gauge(GAUGE::GG_STAT_SMALL);
	_health->init();
	center.x = (LONG)(_hud_back->get_center().x - _health->get_width() * 2.85);
	center.y = (LONG)(_hud_back->get_center().y - _health->get_height() * 2.125);
	_health->set_center(center);
	_hud_gauges.push_back(_health);
	blank = (LONG)(_health->get_height() * 1.5);
	_food = new Gauge(GAUGE::GG_STAT_SMALL);
	_food->init();
	center.y += blank;
	_food->set_center(center);
	_hud_gauges.push_back(_food);
	_mood = new Gauge(GAUGE::GG_STAT_SMALL);
	_mood->init();
	center.y += blank;
	_mood->set_center(center);
	_hud_gauges.push_back(_mood);
	_energy = new Gauge(GAUGE::GG_STAT_SMALL);
	_energy->init();
	center.y += blank;
	_energy->set_center(center);
	_hud_gauges.push_back(_energy);
	// Stat for fight
	_agl = new Gauge(GAUGE::ST_AGL);
	_agl->init();
	center.x = (LONG)(_hud_back->get_center().x - _agl->get_width() * 0.45);
	center.y = (LONG)(_hud_back->get_center().y + _agl->get_height() * 0.725);
	_agl->set_center(center);
	_hud_gauges.push_back(_agl);
	_str = new Gauge(GAUGE::ST_STR);
	_str->init();
	center.x = (LONG)(_agl->get_center().x - _str->get_width() * 1.125);
	center.y = (LONG)(_agl->get_center().y);
	_str->set_center(center);
	_hud_gauges.push_back(_str);
	_stm = new Gauge(GAUGE::ST_STM);
	_stm->init();
	center.x = (LONG)(_agl->get_center().x + _stm->get_width() * 1.15);
	center.y = (LONG)(_agl->get_center().y);
	_stm->set_center(center);
	_hud_gauges.push_back(_stm);
	return S_OK;
}
void HudBack::delete_gauges()
{
	auto iter = _hud_gauges.begin();
	for (; iter != _hud_gauges.end();)
	{
		Release(*iter);
		iter = _hud_gauges.erase(iter);
	}
	swap(_hud_gauges, Gauges());

	Release(_health);
	Release(_food);
	Release(_mood);
	Release(_energy);
	// Stat for Fight
	Release(_str);
	Release(_agl);
	Release(_stm);
}
void HudBack::draw_gauges()
{
	auto iter = _hud_gauges.begin();
	for (; iter != _hud_gauges.end(); iter++)
	{
		Draw(*iter);
	}
}
void HudBack::update_gauges()
{
	_health->sync_gauge_fromValue(PLAYER->get_stat().health);
	_food->sync_gauge_fromValue(PLAYER->get_stat().food);
	_mood->sync_gauge_fromValue(PLAYER->get_stat().mood);
	_energy->sync_gauge_fromValue(PLAYER->get_stat().energy);
	// Stat for fight
	_agl->sync_gauge_fromValue(Exp(PLAYER->get_stat().agl));
	_icon_agl->set_text_toIcon(Stat(PLAYER->get_stat().agl));
	_str->sync_gauge_fromValue(Exp(PLAYER->get_stat().str));
	_icon_str->set_text_toIcon(Stat(PLAYER->get_stat().str));
	_stm->sync_gauge_fromValue(Exp(PLAYER->get_stat().stm));
	_icon_stm->set_text_toIcon(Stat(PLAYER->get_stat().stm));
}
HRESULT HudBack::init_icons()
{
	POINT center;
	// Aglity
	_icon_agl = new Icon(ICON::ICN_AGL);
	_icon_agl->init();
	center.x = (LONG)(_hud_back->get_center().x - _icon_agl->get_width() * 1.5);
	center.y = (LONG)(_hud_back->get_center().y - _icon_agl->get_height() * 0.35);
	_icon_agl->set_center(center);
	_icon_agl->set_text_toIcon(Stat(PLAYER->get_stat().agl));
	// Strength
	_icon_str = new Icon(ICON::ICN_STR);
	_icon_str->init();
	center.x = (LONG)(_icon_agl->get_center().x - _icon_str->get_width() * 3);
	center.y = (LONG)(_icon_agl->get_center().y);
	_icon_str->set_center(center);
	_icon_str->set_text_toIcon(Stat(PLAYER->get_stat().str));
	// Stamina
	_icon_stm = new Icon(ICON::ICN_STM);
	_icon_stm->init();
	center.x = (LONG)(_icon_agl->get_center().x + _icon_stm->get_width() * 3);
	center.y = (LONG)(_icon_agl->get_center().y);
	_icon_stm->set_center(center);
	_icon_stm->set_text_toIcon(Stat(PLAYER->get_stat().stm));
	return S_OK;
}
void HudBack::delete_icons()
{
	Release(_icon_str);
	Release(_icon_agl);
	Release(_icon_stm);
}
void HudBack::draw_icons()
{
	Draw(_icon_str);
	Draw(_icon_agl);
	Draw(_icon_stm);
}

HRESULT HudBack::init()
{
	POINT pos;
	// Icons
	init_icons();
	// SkillPoint
	_skillPoint = MyText(MYTEXT::TXT_TITLE, "0", RGB(253, 204, 109));
	pos.x = (LONG)(_hud_back->get_center().x + 194);
	pos.y = (LONG)(_hud_back->get_center().y - 30);
	_skillPoint.set_pos(pos);
	_skillPoint.set_size(28);
	// Money
	_money = MyText(MYTEXT::TXT_TITLE, "0", RGB(215, 237, 94));
	pos.x = (LONG)(_hud_back->get_center().x + 194);
	pos.y = (LONG)(_hud_back->get_center().y + 8);
	_money.set_pos(pos);
	_money.set_size(28);
	return S_OK;
}
void HudBack::release()
{
	Release(_hud_back);
	delete_gauges();
	delete_icons();
}

void HudBack::update()
{
	if (PtInRect(&_hud_back->get_rect(), m_ptMouse)) { _obj->set_fObjMove(false); }
}
void HudBack::render()
{
	Draw(_hud_back, get_memDC());
	// Gauges
	draw_gauges();
	// Icons
	draw_icons();
	// Sp
	_skillPoint.render(get_memDC());
	// Money
	_money.render(get_memDC());
}
HudBack::HudBack()
{
	POINT center;
	set_imgPath("UI/");
	string path = _imgPath + "Hud_back.bmp";
	_hud_back = new Image;
	_hud_back->init(path.c_str(), (int)(400 * GAME_MULTIPLE), (int)(70 * GAME_MULTIPLE));
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(0 + _hud_back->get_height() * 0.33);
	_hud_back->set_center(center);
	// Gauges
	init_gauges();
}
HudBack::~HudBack()
{
}
