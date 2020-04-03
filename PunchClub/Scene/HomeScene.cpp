#include "stdafx.h"
#include "HomeScene.h"

void HomeScene::init_friger()
{
	POINT center;
	_friger = new Furniture(MYOBJECT::OBJ_FRIGER);
	_friger->init();
	// 초기 위치
	center.x = (LONG)(_kitchentable->get_center().x - _friger->get_width() * 0.86);
	center.y = (LONG)(_kitchentable->get_center().y + _friger->get_width() * 0.1);
	_friger->set_furniture_center(center);
}
void HomeScene::init_sofa()
{
	POINT pos;
	_sofa = new Furniture(MYOBJECT::OBJ_SOFA, MYOBJECT::SOFA_PLAYER);
	_sofa->init();
	// Initial position
	pos.x = (LONG)(_stand->get_rect().right - _stand->get_width() * 0.08);
	pos.y = (LONG)(_stand->get_center().y - _stand->get_width() * 0.1);
	_sofa->set_furniture_pos(pos);
}
void HomeScene::init_tv()
{
	POINT pos;
	_tv = new Furniture(MYOBJECT::OBJ_TV, MYOBJECT::TV_PLAYER);
	_tv->init();
	// Position
	pos.x = (LONG)(_sofa->get_rect().left + _stand->get_width() * 0.25);
	pos.y = (LONG)(_aquarium->get_rect().bottom - _stand->get_width() * 0.37);
	_tv->set_furniture_pos(pos);
}
void HomeScene::init_aquarium()
{
	POINT pos;
	_aquarium = new Furniture(MYOBJECT::OBJ_AQUARIUM);
	_aquarium->init();
	pos.x = (LONG)(_sofa->get_rect().right - _aquarium->get_width() * 0.25);
	pos.y = (LONG)(_kitchentable->get_center().y - _aquarium->get_width() * 0.35);
	_aquarium->set_furniture_pos(pos);
}
void HomeScene::init_fan()
{
	POINT center;
	_fan = new Furniture(MYOBJECT::OBJ_FAN);
	_fan->init();
	center.x = (LONG)((_sofa->get_rect().left + _sofa->get_rect().right) * 0.5);
	center.y = (LONG)(_kitchentable->get_center().y - _fan->get_height() * 0.92);
	_fan->set_furniture_center(center);
}
void HomeScene::init_clock()
{
	POINT pos;
	_clock = new Furniture(MYOBJECT::OBJ_CLOCK);
	_clock->init();
	pos.x = (LONG)(_tv->get_rect().right - _clock->get_width() * 0.65);
	pos.y = (LONG)(_stand->get_rect().top - _clock->get_width() * 0.5);
	_clock->set_furniture_pos(pos);
}
void HomeScene::init_kitchentable()
{
	POINT center;
	_kitchentable = new Furniture(MYOBJECT::OBJ_KITCHEN_TABLE);
	_kitchentable->init();
	center.x = (LONG)(WIN_HALF_W - _kitchentable->get_width() * 0.57);
	center.y = (LONG)(WIN_HALF_H - _kitchentable->get_width() * 0.1);
	_kitchentable->set_furniture_center(center);
}
void HomeScene::init_stand()
{
	POINT center;
	_stand = new Furniture(MYOBJECT::OBJ_STAND);
	_stand->init();
	center.x = (LONG)(WIN_HALF_W - _stand->get_width() * 0.015);
	center.y = (LONG)(_kitchentable->get_center().y - _stand->get_width() * 0.1);
	_stand->set_furniture_center(center);
}
void HomeScene::init_table()
{
	POINT center;
	_table = new Furniture(MYOBJECT::OBJ_TABLE);
	_table->init();
	center.x = (LONG)(_stand->get_center().x + _stand->get_width() * 0.25);
	center.y = (LONG)(WINSIZEY - _table->get_height() * 0.5);
	_table->set_furniture_center(center);
}
void HomeScene::init_bookshelf()
{
	POINT pos;
	_bookshelf = new Furniture(MYOBJECT::OBJ_BOOKSHELF);
	_bookshelf->init();
	pos.x = (LONG)(_tv->get_rect().right + _bookshelf->get_width() * 0.25);
	pos.y = (LONG)(WINSIZEY - _bookshelf->get_height() - _bookshelf->get_width() * 0.1);
	_bookshelf->set_furniture_pos(pos);
}
void HomeScene::init_phone()
{
	POINT center;
	_phone = new Furniture(MYOBJECT::OBJ_PHONE);
	_phone->init();
	center.x = (LONG)(_stand->get_center().x + _phone->get_height() * 0.1);
	center.y = (LONG)(_friger->get_rect().bottom - _phone->get_height() * 0.1);
	_phone->set_furniture_center(center);
}

void HomeScene::init_furnitures()
{
	string path;

	init_kitchentable();
	init_friger();
	init_stand();
	init_sofa();
	init_aquarium();
	init_tv();
	init_fan();
	init_table();
	init_bookshelf();
	init_clock();
	init_phone();
	_objs.push_back(_kitchentable);
	_objs.push_back(_friger);
	_objs.push_back(_stand);
	_objs.push_back(_aquarium);
	_objs.push_back(_sofa);
	_objs.push_back(_tv);
	_objs.push_back(_fan);
	_objs.push_back(_table);
	_objs.push_back(_bookshelf);
	_objs.push_back(_clock);
	_objs.push_back(_phone);
}
void HomeScene::draw_furnitures()
{
	auto iter = _objs.begin();
	for (; iter != _objs.end(); iter++)
	{
		Draw(*iter);
	}
}
void HomeScene::delete_furnitures()
{
	auto iter = _objs.begin();
	for (; iter != _objs.end();)
	{
		Release(*iter);
		iter = _objs.erase(iter);
	}
	Release(_kitchentable);
	Release(_friger);
	Release(_stand);
	Release(_aquarium);
	Release(_sofa);
	Release(_tv);
	Release(_fan);
	Release(_table);
}
void HomeScene::update_furnitures()
{
	auto iter = _objs.begin();
	for (; iter != _objs.end(); iter++)
	{
		(*iter)->update();
	}
}
HRESULT HomeScene::init()
{
	add_currentScene_toList(SCENE_HOME);
	set_imgPath("Home/");
	POINT center;
	string path;
	// Background
	_bg = new Image;
	path = _imgPath + "Kitchen_bg.bmp";
	_bg->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(383 * GAME_MULTIPLE));
	// Ceil
	_ceil = new Image;
	path = _imgPath + "home_ceil.bmp";
	_ceil->init(path.c_str(), (int)(456 * GAME_MULTIPLE), (int)(78 * GAME_MULTIPLE));
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(0 + _ceil->get_height() * 0.5);
	_ceil->set_center(center);
	// 배치할 가구 초기화
	init_furnitures();
	// Player
	PLAYER->init();
	// UI
	INGAME_UI->init();
	INGAME_UI->set_windowType(WINDOW::WND_FRIGER);
	return S_OK;
}
void HomeScene::release()
{
	Release(_bg);
	Release(_ceil);
	delete_furnitures();
}
void HomeScene::update()
{
	update_scene();		// 모든 씬에서 공통으로 업데이트 해야 하는 것을 함수화
	update_furnitures();
	INGAME_UI->update();	// UI를 플레이어보다 먼저 받는다.
	if (_friger->is_run())
	{
		INGAME_UI->set_fIngame_wnd(true);
	}
	else if (INGAME_UI->is_open_setting_wnd()) {}
	else
	{
		PLAYER->update();
	}
	change_scene();	// 항상 마지막에 씬을 바꾼다.
}
void HomeScene::render()
{
	Draw(_bg, get_memDC());
	draw_furnitures();
	Draw(_ceil, get_memDC());
	PLAYER->render();
	INGAME_UI->render();
}
HomeScene::HomeScene()
{
}
HomeScene::~HomeScene()
{
}
