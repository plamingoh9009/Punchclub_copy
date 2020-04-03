#include "stdafx.h"
#include "TitleScene.h"

void TitleScene::control_light_onButtons()
{
	int enabledCounter = 0;
	if (PtInRect(&_play_rc, m_ptMouse))
	{
		_play->set_frameX(1);
		_buttonType = BUTTON_PLAY;
		enabledCounter++;
	}
	else { _play->set_frameX(0); }
	if (PtInRect(&_exit_rc, m_ptMouse))
	{
		_exit->set_frameX(1);
		_buttonType = BUTTON_EXIT;
		enabledCounter++;
	}
	else { _exit->set_frameX(0); }
	// 아무 버튼도 활성화 되지 않은 경우
	if (enabledCounter < 1)
	{
		_buttonType = BUTTON_DISABLED;
	}
}
void TitleScene::run_buttons()
{
	if (_buttonType == BUTTON_PLAY) { _fPlayGame = true; }
	else if (_buttonType == BUTTON_EXIT) 
	{
		PostQuitMessage(0); 
	}
}
void TitleScene::update_loopsRenders()
{
	if (_cloud_up_x > 1366)
	{
		_cloud_up_x -= 1366;
	}
	else
	{
		_cloud_up_x++;
	}
	if (_cloud_under_x > 1366)
	{
		_cloud_under_x -= 1366;
	}
	else
	{
		_cloud_under_x++;
	}
}
//==========================================
//##			이미지 초기화				  ##
//==========================================
void TitleScene::init_background()
{
	POINT center;
	string path;
	_sky_black = new Image;
	path = _imgPath + "sky_black.bmp";
	_sky_black->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(210 * GAME_MULTIPLE));
	_sky_color = new Image;
	path = _imgPath + "sky_color.bmp";
	_sky_color->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(108 * GAME_MULTIPLE));
	center.x = (int)(WIN_HALF_W);
	center.y = (int)(WIN_HALF_H - 65);
	_sky_color->set_center(center);
	// Cloud
	_cloud_up = new Image;
	path = _imgPath + "sky_up.bmp";
	_cloud_up->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(58 * GAME_MULTIPLE));
	center.x = (int)(WIN_HALF_W);
	center.y = (int)(WIN_HALF_H - 200);
	_cloud_up->set_center(center);
	_cloud_under = new Image;
	path = _imgPath + "sky_under.bmp";
	_cloud_under->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(69 * GAME_MULTIPLE));
	center.x = (int)(WIN_HALF_W);
	center.y = (int)(WIN_HALF_H - 170);
	_cloud_under->set_center(center);

	_cloud_up_x = RAND->get_int(1366);
	_cloud_under_x = RAND->get_int(1366);
	// City 
	_city_bg = new Image;
	path = _imgPath + "bridge_bg_city.bmp";
	_city_bg->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(162 * GAME_MULTIPLE));
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(WIN_HALF_H);
	_city_bg->set_center(center);
	// City fg left
	_city_fg_left[0] = new Image;
	path = _imgPath + "city_fg_left_01.bmp";
	_city_fg_left[0]->init(path.c_str(), (int)(102 * GAME_MULTIPLE), (int)(198 * GAME_MULTIPLE));
	center.x = (LONG)(0 + _city_fg_left[0]->get_width() * 0.5);
	center.y = (LONG)(WIN_HALF_H);
	_city_fg_left[0]->set_center(center);
	_city_fg_left[1] = new Image;
	path = _imgPath + "city_fg_left_02.bmp";
	_city_fg_left[1]->init(path.c_str(), (int)(93 * GAME_MULTIPLE), (int)(98 * GAME_MULTIPLE));
	center.x = (LONG)(_city_fg_left[0]->get_center().x + _city_fg_left[1]->get_width() * 0.9);
	center.y = (LONG)(_city_fg_left[0]->get_center().y + 35);
	_city_fg_left[1]->set_center(center);
	_city_fg_left[2] = new Image;
	path = _imgPath + "city_fg_left_03.bmp";
	_city_fg_left[2]->init(path.c_str(), (int)(98 * GAME_MULTIPLE), (int)(61 * GAME_MULTIPLE));
	center.x = (LONG)(_city_fg_left[1]->get_center().x + _city_fg_left[2]->get_width() * 0.6);
	center.y = (LONG)(_city_fg_left[1]->get_center().y - 10);
	_city_fg_left[2]->set_center(center);
	// City fg right
	_city_fg_right[0] = new Image;
	path = _imgPath + "city_fg_right_01.bmp";
	_city_fg_right[0]->init(path.c_str(), (int)(102 * GAME_MULTIPLE), (int)(198 * GAME_MULTIPLE));
	center.x = (LONG)(WINSIZEX - _city_fg_right[0]->get_width() * 0.5);
	center.y = (LONG)(WIN_HALF_H);
	_city_fg_right[0]->set_center(center);
	_city_fg_right[1] = new Image;
	path = _imgPath + "city_fg_right_02.bmp";
	_city_fg_right[1]->init(path.c_str(), (int)(93 * GAME_MULTIPLE), (int)(98 * GAME_MULTIPLE));
	center.x = (LONG)(_city_fg_right[0]->get_center().x - _city_fg_right[1]->get_width() * 0.9);
	center.y = (LONG)(_city_fg_right[0]->get_center().y + 35);
	_city_fg_right[1]->set_center(center);
	_city_fg_right[2] = new Image;
	path = _imgPath + "city_fg_right_03.bmp";
	_city_fg_right[2]->init(path.c_str(), (int)(98 * GAME_MULTIPLE), (int)(61 * GAME_MULTIPLE));
	center.x = (LONG)(_city_fg_right[1]->get_center().x - _city_fg_right[2]->get_width() * 0.6);
	center.y = (LONG)(_city_fg_right[1]->get_center().y - 10);
	_city_fg_right[2]->set_center(center);
	// Bridge
	_bridge = new Image;
	path = _imgPath + "bridge_bg_bridge.bmp";
	_bridge->init(path.c_str(), (int)(448 * GAME_MULTIPLE), (int)(105 * GAME_MULTIPLE));
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(WIN_HALF_H);
	_bridge->set_center(center);
	// Water
	_water_bg_top = new Image;
	path = _imgPath + "water_bg_top.bmp";
	_water_bg_top->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(110 * GAME_MULTIPLE));
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(WIN_HALF_H + _water_bg_top->get_height() * 0.6);
	_water_bg_top->set_center(center);
	_water_bg_bottom = new Image;
	path = _imgPath + "water_bg_bottom.bmp";
	_water_bg_bottom->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(156 * GAME_MULTIPLE));
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(WINSIZEY - _water_bg_bottom->get_height() * 0.5);
	_water_bg_bottom->set_center(center);
}
void TitleScene::draw_background()
{
	_sky_black->render(get_memDC());
	_sky_color->loopRender(get_memDC(), &_sky_color->get_rect(), _cloud_up_x, 0);
	// cloud
	_cloud_up->loopRender(get_memDC(), &_cloud_up->get_rect(), _cloud_up_x, 0);
	_cloud_under->loopRender(get_memDC(), &_cloud_under->get_rect(), _cloud_under_x, 0);
	// water bg
	Draw(_water_bg_bottom, get_memDC());
	_city_bg->alphaRender(get_memDC(), 224);
	Draw(_water_bg_top, get_memDC());
	// City fg
	Draw(_city_fg_left[2], get_memDC());
	Draw(_city_fg_right[2], get_memDC());
	Draw(_bridge, get_memDC());				// bridge
	Draw(_city_fg_left[1], get_memDC());
	Draw(_city_fg_left[0], get_memDC());
	Draw(_city_fg_right[1], get_memDC());
	Draw(_city_fg_right[0], get_memDC());
}
void TitleScene::delete_background()
{
	Release(_sky_black);
	Release(_sky_color);
	Release(_cloud_up);
	Release(_cloud_under);
	Release(_city_bg);
	Release(_bridge);
}
HRESULT TitleScene::init_stars()
{
	Image * star;
	string path = _imgPath + "Star_fx.bmp";
	star = new Image;
	star->init(path.c_str(), (int)(250 * GAME_MULTIPLE), (int)(50 * GAME_MULTIPLE), 5, 1);
	// Setup Var
	int minWidth = (int)(0 + star->get_frameWidth() * 0.5);
	int maxWidth = (int)(WINSIZEX - star->get_frameWidth() * 0.5);
	int minHeight = (int)(0 + star->get_frameHeight() * 0.5);
	int maxHeight = (int)(200 - star->get_frameHeight() * 0.5);
	POINT center;
	int frameX;
	for (int i = 0; i < 30; i++)
	{
		center.x = (LONG)(RAND->get_fromIntTo(minWidth, maxWidth));
		center.y = (LONG)(RAND->get_fromIntTo(minHeight, maxHeight));
		frameX = RAND->get_int(4);
		star = new Image;
		star->init(path.c_str(), (int)(250 * GAME_MULTIPLE), (int)(50 * GAME_MULTIPLE), 5, 1);
		star->set_frameSection(1, 0, 4, 0.3f);
		star->set_frameX(frameX);
		star->set_center(center);
		_stars.push_back(star);
		star = nullptr;
	}
	SAFE_DELETE(star);
	return S_OK;
}
void TitleScene::draw_stars()
{
	auto iter = _stars.begin();
	for (; iter != _stars.end(); iter++)
	{
		(*iter)->frameAlphaRender(get_memDC(), 192);
	}
}
void TitleScene::delete_stars()
{
	auto iter = _stars.begin();
	for (; iter != _stars.end();)
	{
		Release(*iter);
		iter = _stars.erase(iter);
	}
	swap(_stars, Stars());
}
void TitleScene::update_stars()
{
	auto iter = _stars.begin();
	for (; iter != _stars.end(); iter++)
	{
		(*iter)->frameUpdate(false);
	}
}

void TitleScene::init_logos()
{
	string path;
	_logo[0] = new Image;
	path = _imgPath + "Logo.bmp";
	_logo[0]->init(path.c_str(), 191, 167);
	_logo[1] = new Image;
	path = _imgPath + "Logo_darkFist.bmp";
	_logo[1]->init(path.c_str(), 254, 152);
	// 위치를 잡는 중
	POINT center;
	// 첫 좌표는 윈도우를 기준으로 잡는다.
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(WINSIZEY * 0.22);
	_logo_center[0] = center;
	_logo_rc[0] = RectMakeCenter(center.x, center.y,
		_logo[0]->get_width(), _logo[0]->get_height());
	// 두번째 좌표는 펀치클럽 로고를 기준으로 잡는다.
	center.x = center.x - 20;
	center.y = (LONG)(center.y + (_logo[0]->get_height() * 0.45));
	_logo_center[1] = center;
	_logo_rc[1] = RectMakeCenter(center.x, center.y,
		_logo[1]->get_width(), _logo[1]->get_height());
}
void TitleScene::draw_logos()
{
	_logo[0]->render(get_memDC(), _logo_rc[0].left, _logo_rc[0].top);
	_logo[1]->render(get_memDC(), _logo_rc[1].left, _logo_rc[1].top);
}
void TitleScene::delete_logos()
{
	_logo[0]->release();
	_logo[1]->release();
	_logo[0] = nullptr;
	_logo[1] = nullptr;
}

void TitleScene::init_texts()
{
	string path;
	_play = new Image;
	path = _imgPath + "Font_Play.bmp";
	_play->init(path.c_str(), 164, 40, 2, 1);
	_play->set_frameX(0);
	_play->set_frameY(0);
	_exit = new Image;
	path = _imgPath + "Font_Exit.bmp";
	_exit->init(path.c_str(), 100, 40, 2, 1);
	_exit->set_frameX(0);
	_exit->set_frameY(0);
	// 여기서 위치를 잡아준다.
	POINT center = _logo_center[0];
	center.y = (LONG)(center.y + _logo[0]->get_width() * 1.2);
	_play_rc = RectMakeCenter(center.x, center.y,
		_play->get_frameWidth(), _play->get_frameHeight());
	// 종료 버튼
	center.y = (LONG)(center.y + _play->get_frameHeight() * 1.5);
	_exit_rc = RectMakeCenter(center.x, center.y,
		_exit->get_frameWidth(), _exit->get_frameHeight());
}
void TitleScene::draw_texts()
{
	_play->frameRender(get_memDC(), _play_rc.left, _play_rc.top,
		_play->get_frameX(), _play->get_frameY());
	_exit->frameRender(get_memDC(), _exit_rc.left, _exit_rc.top,
		_exit->get_frameX(), _exit->get_frameY());
}
void TitleScene::delete_texts()
{
	_play->release();
	_play = nullptr;
	_exit->release();
	_exit = nullptr;
}

HRESULT TitleScene::init()
{
	add_currentScene_toList(SCENE_TITLE);
	set_imgPath("Title/");
	init_background();
	init_stars();
	// 로고 이미지
	init_logos();
	init_texts();
	// UI
	INGAME_UI->init(UI_NONE);
	return S_OK;
}
void TitleScene::release()
{
	delete_background();
	delete_stars();
	delete_logos();
	delete_texts();
}
void TitleScene::update()
{
	control_light_onButtons();
	update_loopsRenders();
	if (KEYMANAGER->is_onceKeyDown(VK_LBUTTON)) { run_buttons(); }
	// 여기서 씬 체인지
	if (_fPlayGame == true)
	{
		SCENEMANAGER->changeScene("Home");
		_fPlayGame = false;
	}
	update_stars();
	// Cursor
	INGAME_UI->update_cursor();
	//==========================================
	//##			디버그 모드				  ##
	//==========================================
	update_checkDebugMode();
}
void TitleScene::render()
{
	// 배경 이미지 렌더
	draw_background();
	// 별 렌더
	draw_stars();
	// 로고 이미지 렌더
	draw_logos();
	draw_texts();
	// Cursor
	INGAME_UI->draw_cursor();
}
TitleScene::TitleScene()
{
}
TitleScene::~TitleScene()
{
}
