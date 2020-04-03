#include "stdafx.h"
#include "HudMapScene.h"

void HudMapScene::update_player_pos()
{
	MAPICON::TYPE type = _player->get_current_location();
	switch (type)
	{
	case MAPICON::ICN_HOME:
		_player->set_center(_home->get_center());
		break;
	case MAPICON::ICN_SHOP:
		_player->set_center(_shop->get_center());
		break;
	case MAPICON::ICN_GYM:
		_player->set_center(_gym->get_center());
		break;
	case MAPICON::ICN_BUILD:
		_player->set_center(_build->get_center());
		break;
	default:
		break;
	}
}
HRESULT HudMapScene::init_background()
{
	_bg = new Image;
	string path = _imgPath + "HUD_bg.bmp";
	_bg->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(384 * GAME_MULTIPLE));
	if (_bg != nullptr)
	{
		return S_OK;
	}
	return E_FAIL;
}
void HudMapScene::draw_background()
{
	_bg->render(get_memDC());
}
void HudMapScene::delete_background()
{
	_bg->release();
	_bg = nullptr;
}
HRESULT HudMapScene::init_map_icons()
{
	HRESULT result;
	int result_cnt = 0;
	// 집
	_home = new MapIcon;
	result = _home->init(MAPICON::ICN_HOME);
	if (result == S_OK) _icons.push_back(_home);
	else result_cnt++;
	// 수퍼마켓
	_shop = new MapIcon;
	result = _shop->init(MAPICON::ICN_SHOP);
	if (result == S_OK) _icons.push_back(_shop);
	else result_cnt++;
	// 체육관
	_gym = new MapIcon;
	result = _gym->init(MAPICON::ICN_GYM);
	if (result == S_OK) _icons.push_back(_gym);
	else result_cnt++;
	// 공사장
	_build = new MapIcon;
	result = _build->init(MAPICON::ICN_BUILD);
	if (result == S_OK) _icons.push_back(_build);
	else result_cnt++;
	// 캐릭터 이미지 로드
	_player = new MapIcon;
	result = _player->init(MAPICON::ICN_PLAYER);
	_player->set_center(_home->get_center());
	if (result == S_OK) {}
	else result_cnt++;
	// Return
	if (result_cnt == 0) return S_OK;
	else return E_FAIL;
}
void HudMapScene::draw_map_icons()
{
	auto iter = _icons.begin();
	for (; iter != _icons.end(); iter++)
	{
		(*iter)->render();
	}
	_player->render();
}
void HudMapScene::draw_hints()
{
	auto iter = _icons.begin();
	for (; iter != _icons.end(); iter++)
	{
		(*iter)->draw_hint();
	}
}
void HudMapScene::update_map_icons()
{
	auto iter = _icons.begin();
	for (; iter != _icons.end(); iter++)
	{
		(*iter)->update();
		if ((*iter)->get_fOpenBus())
		{
			_bus_wnd->set_fOpenBus(true);
			(*iter)->set_fOpenBus(false);
		}
		// 공사장 윈도우 열때 쓰고 있다.
		if ((*iter)->is_openWindow())
		{
			_build_wnd->set_openWindow(true);
			(*iter)->set_fOpenWindow(false);
		}
	}
	_player->update();
}
void HudMapScene::delete_map_icons()
{
	auto iter = _icons.begin();
	for (; iter != _icons.end();)
	{
		(*iter)->release();
		iter = _icons.erase(iter);
	}
	_home = nullptr;
	_gym = nullptr;
	_shop = nullptr;
	_build = nullptr;
	_player->release();
	_player = nullptr;
	swap(MapIcons(), _icons);
}

void HudMapScene::close_windowsAll(bool fResetClick)
{
	if (_bus_wnd != nullptr)
	{
		_bus_wnd->close_window(fResetClick);
	}
	if (_build_wnd != nullptr)
	{
		_build_wnd->close_window(fResetClick);
	}
}

HRESULT HudMapScene::init()
{
	HRESULT result;
	int result_cnt = 0;
	add_currentScene_toList(SCENE_HUD_MAP);
	set_imgPath("Hud_map/");
	result = init_background();
	(result == S_OK ? 1 : result_cnt++);
	result = init_map_icons();
	(result == S_OK ? 1 : result_cnt++);
	// 버스 윈도우
	_bus_wnd = new Window;
	_bus_wnd->init(WINDOW::WND_BUS);
	// 공사장 윈도우
	_build_wnd = new Window;
	_build_wnd->init(WINDOW::WND_BUILD);
	// UI
	INGAME_UI->init();
	INGAME_UI->set_fRedButton(true);
	// Result
	result = (result_cnt == 0 ? S_OK : E_FAIL);
	return result;
}
void HudMapScene::release()
{
	delete_background();
	delete_map_icons();
	Release(_bus_wnd);
	Release(_build_wnd);
}
void HudMapScene::update()
{
	update_scene();

	if (_bus_wnd->is_openBus() == true)
	{
		_bus_wnd->update();

		// 윈도우의 버튼을 클릭했을 때
		if (_bus_wnd->is_clickButton() == true)
		{
			switch (PLAYER->get_playerLocation())
			{
			case MAPICON::ICN_HOME:
				_scene_forChange = SCENE_HOME;
				break;
			case MAPICON::ICN_BUILD:
				_build_wnd->set_openWindow(true);
				break;
			case MAPICON::ICN_SHOP:
				_scene_forChange = SCENE_SHOP;
				_fClick = false;
				break;
			case MAPICON::ICN_GYM:
				_scene_forChange = SCENE_GYM;
				_fClick = false;
				break;
			}
			_bus_wnd->set_fClickButton(false);
		}
	}// if: 버스창이 열려 있거나
	else if (_build_wnd->is_openWindow() == true)
	{
		_build_wnd->update();
	}// if: 공사장이 열려 있는 경우
	else
	{
		close_windowsAll(false);
		update_map_icons();
		update_player_pos();
	}
	PLAYER->update();
	INGAME_UI->update();
	change_scene();
}
void HudMapScene::render()
{
	draw_background();
	draw_map_icons();
	draw_hints();
	if (_bus_wnd->is_openBus() == true)
	{
		Draw(_bus_wnd);
	}
	else if (_build_wnd->is_openWindow() == true)
	{
		Draw(_build_wnd);
	}
	INGAME_UI->render();
}
HudMapScene::HudMapScene()
{
}
HudMapScene::~HudMapScene()
{
}
