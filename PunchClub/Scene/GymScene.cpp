#include "stdafx.h"
#include "GymScene.h"


HRESULT GymScene::init_objs()
{
	init_treadmills();
	init_barbells();
	init_yungchun();
	init_tire();
	init_benchPress();
	init_punchbugs();
	return S_OK;
}
void GymScene::delete_objs()
{
	auto iter = _objs.begin();
	for (; iter != _objs.end();)
	{
		Release((*iter));
		iter = _objs.erase(iter);
	}
	delete_treadmills();
	delete_barbells();
	delete_yungchun();
	delete_tire();
	delete_benchPress();
	delete_punchbugs();
	swap(Facilitys(), _objs);
}
void GymScene::draw_objs()
{
	auto iter = _objs.begin();
	for (; iter != _objs.end(); iter++)
	{
		Draw((*iter));
	}
}
void GymScene::update_objs()
{
	auto iter = _objs.begin();
	for (; iter != _objs.end(); iter++)
	{
		(*iter)->update();
	}
}

HRESULT GymScene::init_treadmills()
{
	POINT center;
	_treadmill_mid = new Facility(MYOBJECT::OBJ_TREADMILL, MYOBJECT::TRM_YELLOW_GIRL);
	_treadmill_mid->init();
	center.x = (LONG)(WIN_HALF_W + _treadmill_mid->get_width() * 1.8);
	center.y = (LONG)(WIN_HALF_H - _treadmill_mid->get_height());
	_treadmill_mid->set_facility_center(center);
	_objs.push_back(_treadmill_mid);
	_treadmill_left = new Facility(MYOBJECT::OBJ_TREADMILL, MYOBJECT::TRM_ORANGE_GIRL);
	_treadmill_left->init();
	_treadmill_left->set_facility_center(PointMake(center.x - 100, center.y));
	_objs.push_back(_treadmill_left);
	_treadmill_right = new Facility(MYOBJECT::OBJ_TREADMILL, MYOBJECT::TRM_PLAYER);
	_treadmill_right->init();
	_treadmill_right->set_facility_center(PointMake(center.x + 100, center.y));
	_objs.push_back(_treadmill_right);

	return S_OK;
}
void GymScene::delete_treadmills()
{
	Release(_treadmill_left);
	Release(_treadmill_mid);
	Release(_treadmill_right);
}
HRESULT GymScene::init_barbells()
{
	POINT center;
	_barbell = new Facility(MYOBJECT::OBJ_BARBELL, MYOBJECT::BBL_PLAYER);
	_barbell->init();
	center.x = (LONG)(_door->get_rect().left - _barbell->get_width() * 0.85);
	center.y = (LONG)(_door->get_rect().top - _barbell->get_height() * 0.2438);
	_barbell->set_facility_center(center);
	_objs.push_back(_barbell);
	return S_OK;
}
void GymScene::delete_barbells()
{
	Release(_barbell);
}
HRESULT GymScene::init_yungchun()
{
	POINT center;
	_yungchun = new Facility(MYOBJECT::OBJ_YUNGCHUN, MYOBJECT::YCN_PLAYER);
	_yungchun->init();
	center.x = (LONG)(_treadmill_right->get_center().x);
	center.y = (LONG)(WINSIZEY - _yungchun->get_height() * 1);
	_yungchun->set_facility_center(center);
	_objs.push_back(_yungchun);
	return S_OK;
}
void GymScene::delete_yungchun()
{
	Release(_yungchun);
}
HRESULT GymScene::init_tire()
{
	POINT center;
	_tire = new Facility(MYOBJECT::OBJ_TIRE, MYOBJECT::TIR_PLAYER);
	_tire->init();
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(_yungchun->get_center().y);
	_tire->set_facility_center(center);
	_objs.push_back(_tire);
	return S_OK;
}
void GymScene::delete_tire()
{
	Release(_tire);
}
HRESULT GymScene::init_benchPress()
{
	POINT center;
	_benchPress = new Facility(MYOBJECT::OBJ_BENCH_PRESS, MYOBJECT::BP_PLAYER);
	_benchPress->init();
	center.x = (LONG)(WIN_HALF_W - _benchPress->get_width() * 2);
	center.y = (LONG)(WIN_HALF_H + _benchPress->get_height() * 0.5);
	_benchPress->set_facility_center(center);
	_objs.push_back(_benchPress);
	return S_OK;
}
void GymScene::delete_benchPress()
{
	Release(_benchPress);
}
HRESULT GymScene::init_punchbugs()
{
	POINT center;
	_punchbug = new Facility(MYOBJECT::OBJ_PUNCHBUG, MYOBJECT::PB_PLAYER);
	_punchbug->init();
	center.x = (LONG)(WIN_HALF_W - _punchbug->get_width() * 2);
	center.y = (LONG)(WIN_HALF_H - _punchbug->get_height() * 0.6);
	_punchbug->set_facility_center(center);
	_objs.push_back(_punchbug);
	return S_OK;
}
void GymScene::delete_punchbugs()
{
	Release(_punchbug);
}

HRESULT GymScene::init()
{
	add_currentScene_toList(SCENE_GYM);
	set_imgPath("Gym/");
	POINT center;

	_bg = new Image;
	string path = _imgPath + "gym_bg.bmp";
	_bg->init(path.c_str(), (int)(682 * GAME_MULTIPLE), (int)(383 * GAME_MULTIPLE));
	// 체육관 문
	_door = new Image;
	path = _imgPath + "gym_door.bmp";
	_door->init(path.c_str(), (int)(30 * GAME_MULTIPLE), (int)(140 * GAME_MULTIPLE));
	center.x = (LONG)(WINSIZEX - _door->get_width() * 1.625);
	center.y = (LONG)(WIN_HALF_H + _door->get_height() * 0.375);
	_door->set_center(center);
	// 운동기구들 초기화
	init_objs();
	// 플레이어 초기화
	center.x = (LONG)(WIN_HALF_W);
	center.y = (LONG)(WIN_HALF_H);
	PLAYER->init();
	PLAYER->set_playerCenter(center);
	INGAME_UI->init();
	INGAME_UI->set_fRedButton(false);
	return S_OK;
}
void GymScene::release()
{
	Release(_bg);
	Release(_door);
	delete_objs();
}
void GymScene::update()
{
	update_scene();
	update_objs();
	PLAYER->update();
	INGAME_UI->update();
	change_scene();
}
void GymScene::render()
{
	Draw(_bg, get_memDC());
	Draw(_door, get_memDC());
	draw_objs();
	PLAYER->render();
	INGAME_UI->render();
}
GymScene::GymScene()
{
}
GymScene::~GymScene()
{
}
