#include "stdafx.h"
#include "InGameUI.h"
#include "Object/Player.h"
// ====================================
// ***		씬에서 닫기 눌렀을 때		***
// ====================================
void InGameUI::run_red_button()
{
	if (_fClick == true && PtInRect(&_red_button->get_rc(), m_ptMouse))
	{
		_scene_forChange = SCENE_BACK;
		_fClick = false;
	}//if: 버튼을 눌렀다면 씬을 되돌린다.
}
HRESULT InGameUI::init_icons()
{
	HRESULT result;
	int result_cnt = 0;
	POINT center;
	double blank;
	if (_icn_hud_map == nullptr)
	{
		_icn_hud_map = new Icon(ICON::ICN_HUD_MAP);
		result = _icn_hud_map->init();
		result_cnt = (result == S_OK ? result_cnt : result_cnt++);
		// 위치 잡기
		center.x = (LONG)(_icn_hud_map->get_width() - _icn_hud_map->get_width() * 0.2);
		center.y = (LONG)(_icn_hud_map->get_height() - _icn_hud_map->get_height() * 0.2);
		_icn_hud_map->set_center(center);
	}
	blank = _icn_hud_map->get_height() * 0.2;
	if (_icn_league == nullptr)
	{
		_icn_league = new Icon(ICON::ICN_LEAGUE);
		result = _icn_league->init();
		result_cnt = (result == S_OK ? result_cnt : result_cnt++);
		// 위치 잡기
		center.x = (LONG)(_icn_hud_map->get_center().x);
		center.y = (LONG)(_icn_hud_map->get_center().y + _icn_league->get_height() + blank);
		_icn_league->set_center(center);
	}
	if (_icn_skilltree == nullptr)
	{
		_icn_skilltree = new Icon(ICON::ICN_SKILLTREE);
		result = _icn_skilltree->init();
		result_cnt = (result == S_OK ? result_cnt : result_cnt++);
		// 위치 잡기
		center.x = (LONG)(_icn_league->get_center().x);
		center.y = (LONG)(_icn_league->get_center().y + _icn_skilltree->get_height() + blank);
		_icn_skilltree->set_center(center);
	}
	result = (result_cnt == 0 ? S_OK : E_FAIL);
	return result;
}
void InGameUI::delete_icons()
{
	Release(_icn_hud_map);
	Release(_icn_league);
	Release(_icn_skilltree);
}
void InGameUI::draw_icons()
{
	Draw(_icn_hud_map);
	Draw(_icn_league);
	Draw(_icn_skilltree);
	// Hints
	if (_icn_hud_map->get_fHint() == true)
	{
		_icn_hud_map->draw_hint();
	}
	else if (_icn_league->get_fHint() == true)
	{
		_icn_league->draw_hint();
	}
	else if (_icn_skilltree->get_fHint() == true)
	{
		_icn_skilltree->draw_hint();
	}
}
void InGameUI::update_icons()
{
	_icn_hud_map->update();
	_icn_league->update();
	_icn_skilltree->update();
}
// ========================================
// ***		스탯 구슬 함수					***
// ========================================
void InGameUI::erase_beads()
{
	auto iter = _beads.begin();
	for (; iter != _beads.end();)
	{
		if ((*iter)->is_deleteOK())
		{
			Release(*iter);
			iter = _beads.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}
void InGameUI::draw_beads()
{
	auto iter = _beads.begin();
	for (; iter != _beads.end(); iter++)
	{
		Draw(*iter);
	}
}
void InGameUI::update_beads()
{
	auto iter = _beads.begin();
	for (; iter != _beads.end(); iter++)
	{
		(*iter)->update();
	}
}
// ====================================
// ***		리그창 열었을 때			***
// ====================================
void InGameUI::update_league()
{
	_window_league->update();
	if (_window_league->is_closeWindow())
	{
		_icn_league->set_fLeague(false);
		_window_league->init(WINDOW::WND_LEAGUE);
	}
}

void InGameUI::init_gauges()
{
	_gauge = new FightGauge;
	_gauge->init();
}
void InGameUI::draw_gauges()
{
	_gauge->render();
}
void InGameUI::update_gauges()
{
	_gauge->update();
}
void InGameUI::delete_gauges()
{
	_gauge->release();
}
// ====================================
// ***		윈도우 열었을 때			***
// ====================================
void InGameUI::update_ingame_wnd()
{
	_ingame_wnd->update();
	if (_ingame_wnd->is_closeWindow() == true)
	{
		CloseWnd();
	}
}
void InGameUI::draw_ingame_wnd()
{
	Draw(_ingame_wnd);
}

HRESULT InGameUI::init_cursor()
{
	if (_cursor == nullptr)
	{
		_cursor = new Cursor;
		_cursor->init();
	}
	return S_OK;
}

void InGameUI::draw_cursor()
{
	Draw(_cursor);
}
void InGameUI::update_cursor()
{
	_cursor->update();
}

void InGameUI::set_windowType(WINDOW::TYPE type)
{
	_wndType = type;
	if (_ingame_wnd == nullptr)
	{
		_ingame_wnd = new Window;
	}
	_ingame_wnd->init(type);
}

bool InGameUI::is_open_setting_wnd()
{
	if (_setting_wnd)
	{
		if (_setting_wnd->is_openWindow())
		{
			return true;
		}
	}
	return false;
}

void InGameUI::reset_ingame_wnd()
{
	_fClose_ingame_wnd = false;
	_ingame_wnd->reset_closeWindow();
}

HRESULT InGameUI::init()
{
	_obj = new Object;

	// Cursor
	init_cursor();
	
	// Icons
	init_icons();
	_hud_back = new HudBack;
	_hud_back->init();
	_red_button = new Button(BUTTON::BTN_DELETE_RED);
	_red_button->init();
	_red_button->set_pos_toRT_edge(
		RectMake(0, 0, WINSIZEX, WINSIZEY)
	);
	_fRedButton = false;
	_window_league = new Window;
	_window_league->init(WINDOW::WND_LEAGUE);
	// Setting
	_setting_wnd = new Window();
	_setting_wnd->init(WINDOW::WND_SETTING);
	return S_OK;
}
HRESULT InGameUI::init(UI_TYPE type)
{
	switch (type)
	{
	case UI_LEAGUE:
		init_gauges();
		_type = type;
		break;
	case UI_NONE:
		init_cursor();
		_type = type;
	default:
		break;
	}
	return S_OK;
}
void InGameUI::release()
{
	_obj = nullptr;

	Release(_cursor);
	delete_icons();
	Release(_hud_back);
	Release(_red_button);
	Release(_window_league);
	Release(_ingame_wnd);
	Release(_setting_wnd);
	delete_gauges();
}
void InGameUI::update()
{
	switch (_type)
	{
	case UI_LEAGUE:
		update_gauges();
		break;
	default:
		_hud_back->update_datas_fromPlayer();
		update_icons();
		if (_fRedButton) { run_red_button(); }
		if (_icn_league->get_fLeague()) { update_league(); }
		break;
	}
	if (_fIngame_wnd == true)
	{
		update_ingame_wnd();
	}
	// Setting Window
	_setting_wnd->update();

	update_cursor();
	if (PLAYER->is_running_action() &&
		PLAYER->get_actionType() != MYOBJECT::RUN_EMPTY)
	{
		_cursor->set_fWait(true);
	}
	else
	{
		_cursor->set_fWait(false);
	}
	// Beads
	_beads = PLAYER->get_beads();
	update_beads();
	erase_beads();
}// Update
void InGameUI::render()
{
	switch (_type)
	{
	case UI_LEAGUE:
		draw_gauges();
		break;
	default:
		draw_icons();
		_hud_back->render();
		draw_beads();
		if (_fRedButton) { _red_button->render(); }
		if (_icn_league->get_fLeague()) { _window_league->render(); }
		break;
	}
	if (_fIngame_wnd == true)
	{
		draw_ingame_wnd();
	}
	// Setting Window
	if (_setting_wnd->is_openWindow())
	{
		Draw(_setting_wnd);
	}
	draw_cursor();
}
InGameUI::InGameUI()
{
}
InGameUI::~InGameUI()
{
}

void InGameUI::CloseWnd()
{
	_fIngame_wnd = false;
	_fClose_ingame_wnd = true;
}
