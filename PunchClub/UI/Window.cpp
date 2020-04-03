#include "stdafx.h"
#include "Window.h"
#include "Object/Player.h"
HRESULT Window::init_window_bg(WINDOW::TYPE type)
{
	_type = type;
	string path;
	POINT center, pos;
	switch (type)
	{
	case WINDOW::WND_NONE:
	case WINDOW::WND_SHOP:
	case WINDOW::WND_FRIGER:
	case WINDOW::WND_LEAGUE:
		// Background Image
		path = _imgPath + "Window_back.bmp";
		_bg = new Image;
		_bg->init(path.c_str(), (int)(425 * GAME_MULTIPLE), (int)(300 * GAME_MULTIPLE));
		center.x = (LONG)(WIN_HALF_W);
		center.y = (LONG)(WIN_HALF_H + _bg->get_height() * 0.07);
		_bg->set_center(center);
		// Delete Button
		_red_button = new Button(BUTTON::BTN_DELETE_RED);
		_red_button->init();
		_red_button->set_pos_toRT_edge(_bg->get_rect());
		// 라인을 그리는 기준
		path = _imgPath + "Locked_back.bmp";
		_locked_back = new Image;
		_locked_back->init(path.c_str(),
			(int)(419 * GAME_MULTIPLE), (int)(234 * GAME_MULTIPLE));
		pos.x = (LONG)(_bg->getX() + 6);
		pos.y = (LONG)(_bg->getY() + _bg->get_height() * 0.2 + 4);
		_locked_back->set_pos(pos);
		break;
	case WINDOW::WND_BUS:
	case WINDOW::WND_SETTING:
		set_imgPath("UI/Window/Bus/");
		// Background Image
		path = _imgPath + "bus_window_back.bmp";
		_bg = new Image;
		_bg->init(path.c_str(), (int)(265 * GAME_MULTIPLE), (int)(225 * GAME_MULTIPLE));
		center.x = (LONG)(WIN_HALF_W);
		center.y = (LONG)(WIN_HALF_H + _bg->get_height() * 0.07);
		_bg->set_center(center);
		// Red button Class
		_red_button = new Button(BUTTON::BTN_DELETE_RED);
		_red_button->init();
		_red_button->set_pos_toRT_edge(_bg->get_rect());
		break;
	case WINDOW::WND_BUILD:
		set_imgPath("UI/Window/Build/");
		//Background Image
		path = _imgPath + "build_window_back.bmp";
		_bg = new Image;
		_bg->init(path.c_str(), (int)(285 * GAME_MULTIPLE), (int)(280 * GAME_MULTIPLE));
		center.x = (LONG)(WIN_HALF_W);
		center.y = (LONG)(WIN_HALF_H + _bg->get_height() * 0.07);
		_bg->set_center(center);
		break;
	}
	return S_OK;
}
void Window::delete_window_bg()
{
	Release(_bg);
	Release(_red_button);
	Release(_locked_back);
}
void Window::draw_window_bg()
{
	Draw(_bg, get_memDC());
}

void Window::init_inventory()
{
	string path;
	POINT pos;
	_fg = new Image;
	switch (_type)
	{
	case WINDOW::WND_FRIGER:
		path = _imgPath + "Hdr_friger.bmp";
		_fg->init(path.c_str(), (int)(79 * GAME_MULTIPLE), (int)(40 * GAME_MULTIPLE));
		// 글씨
		_fg_title = MyText(MYTEXT::TXT_TITLE, "냉장고", RGB(254, 254, 254));
		_fg_descr = MyText(MYTEXT::TXT_DESCR,
			"당신이 산 식료품이 보관됩니다. 식료품을 슈퍼에서 구입할 수 있습니다.", RGB(58, 47, 24));
		break;
	case WINDOW::WND_SHOP:
		path = _imgPath + "Hdr_shop.bmp";
		_fg->init(path.c_str(), (int)(89 * GAME_MULTIPLE), (int)(47 * GAME_MULTIPLE));
		// 글씨
		_fg_title = MyText(MYTEXT::TXT_TITLE, "슈퍼", RGB(254, 254, 254));
		_fg_descr = MyText(MYTEXT::TXT_DESCR,
			"식료품 및 에너지 드링크를 구입할 수 있습니다.", RGB(58, 47, 24));
		break;
	}
	_fg->set_rect(
		RectMake(
		(int)(_bg->getX()), (int)(_bg->getY() + 10),
			(int)(_bg->get_width() * 0.25), (int)(_bg->get_height() * 0.2)
		)
	);
	pos.x = _fg->get_rect().right;
	pos.y = _fg->get_rect().top + 20;
	_fg_title.set_pos(pos);
	pos.x = _fg_title.get_pos().x;
	pos.y = _fg_title.get_pos().y + 40;
	_fg_descr.set_pos(pos);
	_fg->set_rect(
		RectMakeCenter(
			_fg->get_center().x, _fg->get_center().y,
			_fg->get_width(), _fg->get_height()
		)
	);
	// 라인 초기화
	_line_pos.x = (LONG)(_locked_back->getX());
	_line_pos.y = (LONG)(_locked_back->getY());
}
void Window::draw_inventory()
{
	// Line을 그린다.
	ColorLine(get_memDC(), _line_pos.x, (int)(_line_pos.y - 2),
		_locked_back->get_rect().right, (int)(_line_pos.y - 2),
		1, RGB(94, 84, 64));
	ColorLine(get_memDC(), _line_pos.x, _line_pos.y,
		_locked_back->get_rect().right - 1, _line_pos.y,
		2, RGB(78, 68, 50));
	_locked_back->alphaRender(get_memDC(), 32);
	// fg 이미지를 그린다.
	Draw(_fg, get_memDC());
	_fg_title.render(get_memDC());
	_fg_descr.render(get_memDC());
	// Delete button을 그린다.
	Draw(_red_button);
}
void Window::delete_inventory()
{
	Release(_fg);
}
void Window::update_friger()
{
	SLOT::ITEM itemType;
	auto iter = _slots.begin();
	for (; iter != _slots.end(); iter++)
	{
		(*iter)->update();
		if ((*iter)->is_clickButton())
		{
			itemType = (*iter)->get_itemType();
			PLAYER->use_item(itemType);
			break;
		}
	}
}

void Window::init_league()
{
	set_imgPath("UI/Window/League/");
	string path;
	POINT pos, center;
	path = _imgPath + "League_fg.bmp";
	// 라인 초기화
	_line_pos.x = (LONG)(_locked_back->get_rect().left);
	_line_pos.y = (LONG)((_bg->get_rect().top + _locked_back->get_rect().top) * 0.5);
	_line_pos_ver.x = (LONG)((_bg->get_rect().left + _bg->get_rect().right) * 0.45);
	_line_pos_ver.y = (LONG)(_bg->get_rect().bottom - 8);
	// 리그 아저씨 이미지
	_fg = new Image;
	_fg->init(path.c_str(), (int)(159 * GAME_MULTIPLE), (int)(180 * GAME_MULTIPLE));
	pos.x = (LONG)(_line_pos.x);
	pos.y = (LONG)(_line_pos.y);
	_fg->set_rect(
		RectMake(pos.x, pos.y,
		(int)(_line_pos_ver.x - _line_pos.x),
			(int)(_line_pos_ver.y - _line_pos.y)
		)
	);
	center.x = (LONG)((_fg->get_rect().left + _fg->get_rect().right) * 0.5);
	center.y = (LONG)((_fg->get_rect().top + _fg->get_rect().bottom) * 0.525);
	_fg->set_center(center);
	// 리그 글씨
	_fg_title = MyText(MYTEXT::TXT_TITLE, "리그", RGB(254, 254, 254));
	pos.x = (LONG)(_bg->get_center().x);
	pos.y = (LONG)((_line_pos.y + _bg->get_rect().top) * 0.46);
	_fg_title.set_pos(pos);
	// 리그 슬롯을 위한 렉트
	init_league_slots();
}
void Window::draw_league()
{
	// 가로 Line을 그린다.
	ColorLine(get_memDC(), _locked_back->get_rect().left, (int)(_line_pos.y - 2),
		_locked_back->get_rect().right, (int)(_line_pos.y - 2),
		1, RGB(94, 84, 64));
	ColorLine(get_memDC(), _locked_back->get_rect().left, _line_pos.y,
		_locked_back->get_rect().right - 1, _line_pos.y,
		2, RGB(78, 68, 50));
	// 세로 Line을 잡는다.
	ColorLine(get_memDC(), _line_pos_ver.x, _line_pos.y,
		_line_pos_ver.x, _line_pos_ver.y, 2, RGB(94, 84, 64));
	// 리그 아저씨를 그린다
	Draw(_fg, get_memDC());
	// 리그 타이틀을 띄운다.
	_fg_title.render(get_memDC());
	draw_league_slots();
	// Delete button Draw
	Draw(_red_button);
}
void Window::update_league()
{
	if (PtInRect(&_league_slot[0].btn_show_rc, m_ptMouse))
	{
		_fClose = true;
		_scene_forChange = SCENE_LEAGUE_WAIT;
	}
}
void Window::delete_league()
{
	Release(_fg);
	delete_league_slots();
}
void Window::init_league_slots()
{
	string path;
	POINT pos;
	int width = (int)(_bg->get_rect().right - _line_pos_ver.x - 6);
	int height = (int)(_bg->get_rect().bottom - _line_pos.y - 6);
	_league_slots_rc = RectMake(_line_pos_ver.x + 2, _line_pos.y, width, height);
	height = (int)(height / 3);
	for (int i = 0; i < 3; i++)
	{
		_league_slot[i].back_rc = RectMake(
			_league_slots_rc.left,
			(int)(_league_slots_rc.top + i * height),
			width, height);
		_league_slot[i].slot_center.x = (LONG)((_league_slot[i].back_rc.left + _league_slot[i].back_rc.right) * 0.5);
		_league_slot[i].slot_center.y = (LONG)((_league_slot[i].back_rc.top + _league_slot[i].back_rc.bottom) * 0.5);
		_league_slot[i].back = new Image;
		path = _imgPath + "League_slot.bmp";
		_league_slot[i].back->init(path.c_str(),
			(int)(243 * GAME_MULTIPLE), (int)(88 * GAME_MULTIPLE));
		if (i == 0)
		{
			path = _imgPath + "League_icon.bmp";
			_league_slot[i].icon = new Image;
			_league_slot[i].icon->init(path.c_str(),
				(int)(27 * GAME_MULTIPLE), (int)(42 * GAME_MULTIPLE));
			path = _imgPath + "League_icon_bg.bmp";
			_league_slot[i].icon_back = new Image;
			_league_slot[i].icon_back->init(path.c_str(),
				(int)(61 * GAME_MULTIPLE), (int)(61 * GAME_MULTIPLE));
			pos.x = (LONG)(_league_slot[i].back_rc.left + 10);
			pos.y = (LONG)(_league_slot[i].back_rc.bottom -
				_league_slot[i].icon_back->get_height() * 1.05);
			_league_slot[i].icon_back_rc = RectMake(pos.x, pos.y,
				_league_slot[i].icon_back->get_width(),
				_league_slot[i].icon_back->get_height());
			_league_slot[i].icon_center.x = (LONG)((_league_slot[i].icon_back_rc.left +
				_league_slot[i].icon_back_rc.right) * 0.5);
			_league_slot[i].icon_center.y = (LONG)((_league_slot[i].icon_back_rc.top +
				_league_slot[i].icon_back_rc.bottom) * 0.5);
			_league_slot[i].icon_rc = RectMakeCenter(
				_league_slot[i].icon_center.x,
				_league_slot[i].icon_center.y,
				_league_slot[i].icon->get_width(), _league_slot[i].icon->get_height());
			// 슬롯의 텍스트를 정하는 부분
			_league_slot[i].title = "루키 리그";
			_league_slot[i].desc_type[0] = "종류: ";
			_league_slot[i].desc_type[1] = "스코어리그";
			_league_slot[i].desc_rank[0] = "현재 순위: ";
			_league_slot[i].desc_rank[1] = "12";
			_league_slot[i].desc_next[0] = "다음 싸움: ";
			_league_slot[i].desc_next[1] = "2 일 후";
			_league_slot[i].title_pos.x = (LONG)(_league_slot[i].slot_center.x - 30);
			_league_slot[i].title_pos.y = (LONG)(_league_slot[i].back_rc.top + 10);
			_league_slot[i].desc_pos.x = (LONG)(_league_slot[i].icon_back_rc.right + 5);
			_league_slot[i].desc_pos.y = (LONG)(_league_slot[i].icon_back_rc.top + 5);
			// 버튼
			path = _imgPath + "Btn_show.bmp";
			_league_slot[i].btn_show = new Image;
			_league_slot[i].btn_show->init(path.c_str(),
				(int)(57 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
			path = _imgPath + "Icon_show.bmp";
			_league_slot[i].icon_show = new Image;
			_league_slot[i].icon_show->init(path.c_str(),
				(int)(24 * GAME_MULTIPLE), (int)(24 * GAME_MULTIPLE));
			// 버튼 위치
			pos.x = (LONG)(_league_slot[i].back_rc.right -
				_league_slot[i].btn_show->get_width() * 1.075);
			pos.y = (LONG)(_league_slot[i].back_rc.bottom -
				_league_slot[i].btn_show->get_height() * 1.15);
			_league_slot[i].btn_show_rc = RectMake(pos.x, pos.y,
				_league_slot[i].btn_show->get_width(),
				_league_slot[i].btn_show->get_height());
			_league_slot[i].btn_show_center.x = (LONG)(
				(_league_slot[i].btn_show_rc.left + _league_slot[i].btn_show_rc.right) * 0.5);
			_league_slot[i].btn_show_center.y = (LONG)(
				(_league_slot[i].btn_show_rc.top + _league_slot[i].btn_show_rc.bottom) * 0.5);
			_league_slot[i].icon_show_rc = RectMakeCenter(
				_league_slot[i].btn_show_center.x,
				_league_slot[i].btn_show_center.y,
				_league_slot[i].icon_show->get_width(),
				_league_slot[i].icon_show->get_height());
		}
		else
		{
			path = _imgPath + "League_lock_back2.bmp";
			_league_slot[i].lock_back = new Image;
			_league_slot[i].lock_back->init(path.c_str(),
				(int)(241 * GAME_MULTIPLE), (int)(86 * GAME_MULTIPLE));
			_league_slot[i].lock_back_rc = RectMakeCenter(
				_league_slot[i].slot_center.x, _league_slot[i].slot_center.y,
				_league_slot[i].lock_back->get_width(), _league_slot[i].lock_back->get_height());
			path = _imgPath + "League_lock.bmp";
			_league_slot[i].lock = new Image;
			_league_slot[i].lock->init(path.c_str(),
				(int)(45 * GAME_MULTIPLE), (int)(52 * GAME_MULTIPLE));
			_league_slot[i].lock_rc = RectMakeCenter(
				_league_slot[i].slot_center.x,
				_league_slot[i].slot_center.y,
				_league_slot[i].lock->get_width(),
				_league_slot[i].lock->get_height());
		}
	}//loop: 슬롯의 이미지, 렉트를 잡기 위한 루프
}
void Window::draw_league_slots()
{
	for (int i = 0; i < 3; i++)
	{
		_league_slot[i].back->render(get_memDC(),
			_league_slot[i].back_rc.left, _league_slot[i].back_rc.top);
		if (i == 0)
		{
			_league_slot[i].icon_back->render(get_memDC(),
				_league_slot[i].icon_back_rc.left, _league_slot[i].icon_back_rc.top);
			_league_slot[i].icon->render(get_memDC(),
				_league_slot[i].icon_rc.left, _league_slot[i].icon_rc.top);
			// 텍스트
			FontTextShadow(get_memDC(), _league_slot[i].title_pos.x, _league_slot[i].title_pos.y,
				_league_slot[i].title.c_str(), "휴먼매직체", 35, RGB(246, 204, 111));

			FontTextOut(get_memDC(), _league_slot[i].desc_pos.x, _league_slot[i].desc_pos.y,
				_league_slot[i].desc_type[0].c_str(), "휴먼편지체", 25, RGB(255, 193, 59));
			FontTextOut(get_memDC(), _league_slot[i].desc_pos.x + 40, _league_slot[i].desc_pos.y,
				_league_slot[i].desc_type[1].c_str(), "휴먼편지체", 25, RGB(254, 254, 254));
			FontTextOut(get_memDC(), _league_slot[i].desc_pos.x, _league_slot[i].desc_pos.y + 30,
				_league_slot[i].desc_rank[0].c_str(), "휴먼편지체", 25, RGB(255, 193, 59));
			FontTextOut(get_memDC(), _league_slot[i].desc_pos.x + 90, _league_slot[i].desc_pos.y + 30,
				_league_slot[i].desc_rank[1].c_str(), "휴먼편지체", 25, RGB(254, 254, 254));
			FontTextOut(get_memDC(), _league_slot[i].desc_pos.x, _league_slot[i].desc_pos.y + 60,
				_league_slot[i].desc_next[0].c_str(), "휴먼편지체", 25, RGB(255, 193, 59));
			FontTextOut(get_memDC(), _league_slot[i].desc_pos.x + 90, _league_slot[i].desc_pos.y + 60,
				_league_slot[i].desc_next[1].c_str(), "휴먼편지체", 25, RGB(254, 254, 254));
			// 버튼
			_league_slot[i].btn_show->render(get_memDC(),
				_league_slot[i].btn_show_rc.left,
				_league_slot[i].btn_show_rc.top);
			_league_slot[i].icon_show->render(get_memDC(),
				_league_slot[i].icon_show_rc.left,
				_league_slot[i].icon_show_rc.top);
		}
		else
		{
			_league_slot[i].lock_back->alphaRender(get_memDC(),
				_league_slot[i].lock_back_rc.left, _league_slot[i].lock_back_rc.top, 80);
			_league_slot[i].lock->alphaRender(get_memDC(),
				_league_slot[i].lock_rc.left, _league_slot[i].lock_rc.top, 255);
		}
	}
}
void Window::delete_league_slots()
{
	for (int i = 0; i < 3; i++)
	{
		Release(_league_slot[i].back);
		Release(_league_slot[i].lock_back);
		Release(_league_slot[i].lock);
		Release(_league_slot[i].icon);
		Release(_league_slot[i].icon_back);
	}
}
//==========================================
//##		버스 Foreground 초기화		  ##
//==========================================
HRESULT Window::init_bus_fg()
{
	//set_imgPath("UI/Window/Bus/");
	string path;
	POINT center, pos;
	string str;

	// Bus Window
	_inside = new Image;
	path = _imgPath + "bus_inside.bmp";
	_inside->init(path.c_str(), (int)(250 * GAME_MULTIPLE), (int)(98 * GAME_MULTIPLE));
	center.x = (LONG)(_bg->get_center().x);
	center.y = (LONG)(_bg->get_center().y - _inside->get_height() * 0.25);
	_inside->set_center(center);
	// FG
	_fg = new Image;
	path = _imgPath + "bus_back_st.bmp";
	_fg->init(path.c_str(), (int)(496), (int)(192));
	center.x = (LONG)(_inside->get_center().x);
	center.y = (LONG)(_inside->get_center().y);
	_fg->set_center(center);
	// Bus
	_bus = new Image;
	path = _imgPath + "ingame_bus.bmp";
	_bus->init(path.c_str(), (int)(210), (int)(147));
	pos.x = (LONG)(_fg->getX());
	pos.y = (LONG)(_fg->get_rect().bottom - _bus->get_height());
	_bus->set_pos(pos);
	// Text
	_fg_title = MyText(MYTEXT::TXT_TITLE, "이동");
	pos.x = (LONG)(_bg->get_center().x - 20);
	pos.y = (LONG)(_inside->getY() - 55);
	_fg_title.set_pos(pos);
	_fg_descr = MyText(MYTEXT::TXT_DESCR, "일", RGB(30, 83, 103));
	pos.x = (LONG)(_bg->get_center().x - 5);
	pos.y = (LONG)(_inside->get_rect().bottom + 15);
	_fg_descr.set_pos(pos);
	_bus_distance_str = MyText(MYTEXT::TXT_DESCR,
		map_bus_distance("이동 거리: ", _bus_distance), RGB(30, 83, 103));
	pos.x = (LONG)(pos.x - 60);
	pos.y = (LONG)(pos.y + 30);
	_bus_distance_str.set_pos(pos);
	//==========================================
	//##				Button			  ##
	//==========================================
	// Bus
	_btn_bus = new Button(BUTTON::BTN_BUS_GREEN);
	_btn_bus->init();
	center.x = (LONG)(_bg->get_center().x - _btn_bus->get_width() * 0.6);
	center.y = (LONG)(_bg->get_rect().bottom - _btn_bus->get_height());
	_btn_bus->set_center(center);
	str = "버스로 이동:    ";
	str.append(to_string(_bus_distance));
	_btn_bus->set_text_toButton(str);
	// Icon
	center.x = (LONG)(_btn_bus->get_center().x + _btn_bus->get_width() * 0.2188);
	center.y = (LONG)(_btn_bus->get_center().y - _btn_bus->get_height() * 0.0625);
	_btn_bus->set_icon_toButton(BUTTON::ICN_DOLLAR, center);
	// Walk
	_btn_walk = new Button(BUTTON::BTN_BUS_GREEN);
	_btn_walk->init();
	center.x = (LONG)(_bg->get_center().x + _btn_walk->get_width() * 0.6);
	center.y = (LONG)(_bg->get_rect().bottom - _btn_walk->get_height());
	_btn_walk->set_center(center);
	str = "걸어서 이동:    ";
	str.append(to_string((int)(_bus_distance * 0.5)));
	_btn_walk->set_text_toButton(str);
	// Icon
	center.x = (LONG)(_btn_walk->get_center().x + _btn_walk->get_width() * 0.25);
	center.y = (LONG)(_btn_walk->get_center().y - _btn_walk->get_height() * 0.0313);
	_btn_walk->set_icon_toButton(BUTTON::ICN_TIME_DAYS, center);

	//Return result
	return S_OK;
}
void Window::draw_bus()
{
	Draw(_inside, get_memDC());
	Draw(_fg, get_memDC());
	Draw(_bus, get_memDC());
	// Text
	_fg_title.render(get_memDC());
	_fg_descr.render(get_memDC());
	_bus_distance_str.render(get_memDC());
	// Button
	Draw(_btn_bus);
	Draw(_btn_walk);
	Draw(_red_button);
}
void Window::delete_bus()
{
	Release(_inside);
	Release(_fg);
	Release(_bus);
	Release(_btn_bus);
	Release(_btn_walk);
}
void Window::update_bus()
{
	_btn_bus->update();
	_btn_walk->update();
	// Close Window
	if (_btn_bus->is_closeWindow() == true)
	{
		close_window();
		_fClickButton = true;
		PLAYER->add_money(-_bus_distance);
	}
	else if (_btn_walk->is_closeWindow() == true)
	{
		close_window();
		_fClickButton = true;
	}
}
string Window::map_bus_distance(string bus_str, int bus_dist)
{
	bus_str.append(to_string(bus_dist));
	bus_str.append(" km");
	return bus_str;
}
//==========================================
//##		공사장 Foreground 초기화		  ##
//==========================================
HRESULT Window::init_build_fg()
{
	string path;
	POINT center, pos;
	HRESULT result;
	int result_cnt = 0;
	// Inside Window
	_inside = new Image;
	path = _imgPath + "build_inside.bmp";
	result = _inside->init(path.c_str(), (int)(267 * GAME_MULTIPLE), (int)(152 * GAME_MULTIPLE));
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);
	center.x = (LONG)(_bg->get_center().x);
	center.y = (LONG)(_bg->get_center().y - _inside->get_height() * 0.36);
	_inside->set_center(center);
	// Foreground Image
	_fg = new Image;
	path = _imgPath + "work_jhammer_bg.bmp";
	result = _fg->init(path.c_str(), (int)(265 * GAME_MULTIPLE), (int)(150 * GAME_MULTIPLE));
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);
	_fg->set_center(_inside->get_center());
	// Work Image
	_work_jhammer = new Image;
	path = _imgPath + "work_jhammer.bmp";
	result = _work_jhammer->init(path.c_str(), (int)(276 * GAME_MULTIPLE), (int)(75 * GAME_MULTIPLE), 3, 1);
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);
	_work_jhammer->set_frameSection(1, 0, 2, 0.3f);
	center.x = (LONG)(_fg->get_center().x - _work_jhammer->get_frameWidth() * 0.2);
	center.y = (LONG)(_fg->get_center().y);
	_work_jhammer->set_center(center);
	_work_dust = new Image;
	path = _imgPath + "work_dust.bmp";
	result = _work_dust->init(path.c_str(), (int)(228 * GAME_MULTIPLE), (int)(27 * GAME_MULTIPLE), 6, 1);
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);
	_work_dust->set_frameSection(1, 0, 5, 0.3f);
	center.x = (LONG)(_work_jhammer->get_rect().right - _work_dust->get_frameWidth() * 0.375);
	center.y = (LONG)(_work_jhammer->get_rect().bottom - _work_dust->get_frameHeight() * 0.25);
	_work_dust->set_center(center);
	// Text
	_fg_title = MyText(MYTEXT::TXT_DESCR, "일을 끝낼 때마다 다음을 획득:", RGB(0, 43, 61));
	pos.x = (LONG)(_inside->get_center().x - 150);
	pos.y = (LONG)(_inside->get_rect().bottom + 20);
	_fg_title.set_size(30);
	_fg_title.set_pos(pos);
	_fg_descr = MyText(MYTEXT::TXT_DESCR, "50", RGB(0, 43, 61));
	pos.x = (LONG)(_inside->get_center().x);
	pos.y = (LONG)(pos.y + 45);
	_fg_descr.set_size(30);
	_fg_descr.set_pos(pos);

	// Start Green Button
	_btn_build = new Button(BUTTON::BTN_WORK_GREEN);
	_btn_build->init();
	center.x = (LONG)(_bg->get_center().x);
	center.y = (LONG)(_bg->get_rect().bottom - _btn_build->get_height() * 0.75);
	_btn_build->set_center(center);
	_btn_build->set_text_toButton("시작");
	center.x = (LONG)(_fg_descr.get_pos().x - 20);
	center.y = (LONG)(_fg_descr.get_pos().y + 10);
	_btn_build->set_icon_toButton(BUTTON::ICN_DOLLAR, center);

	// Work Gauge
	_gauge = new Gauge(GAUGE::GG_WORK);
	_gauge->init();
	center.x = (LONG)(_btn_build->get_center().x);
	center.y = (LONG)(_btn_build->get_center().y - _gauge->get_height() * 1.65);
	_gauge->set_center(center);

	// Red button Class
	_red_button = new Button(BUTTON::BTN_DELETE_RED);
	result = _red_button->init();
	_red_button->set_pos_toRT_edge(_inside->get_rect());
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);

	return S_OK;
}
void Window::draw_build()
{
	Draw(_inside, get_memDC());
	Draw(_fg, get_memDC());
	_work_dust->frameAlphaRender(get_memDC(), 128);
	_work_jhammer->frameRender(get_memDC());
	// Text
	_fg_title.render(get_memDC());
	_fg_descr.render(get_memDC());
	// Work Gauge
	Draw(_gauge);

	// Button
	Draw(_btn_build);
	Draw(_red_button);
}
void Window::delete_build()
{
	Release(_inside);
	Release(_fg);
	Release(_work_jhammer);
	Release(_btn_build);
}
void Window::update_build()
{
	// 시작버튼 업데이트
	_btn_build->update();

	// 게이지 업데이트
	_gauge->update();
	// 여기서 시작 버튼을 눌렀는지 여부를 게이지에 넘겨준다.
	if (_btn_build->is_toggleButton() == true)
	{
		// 플레이어 위치를 윈도우 가운데로 다시 잡아준다.
		PLAYER->set_playerCenter(_inside->get_center());
		PLAYER->set_playerAction(MYOBJECT::WORK_PLAYER | MYOBJECT::RUN_PLAYER);
		PLAYER->action_start();
		_btn_build->set_text_toButton("중지");
		// 플레이어가 지치면 윈도우를 멈춘다.
		if (PLAYER->is_tired())
		{
			PLAYER->Tired();
			PLAYER->set_playerAction(MYOBJECT::RUN_EMPTY);
			PLAYER->action_pause();
			_btn_build->set_text_toButton("시작");
		}
	}
	else
	{
		PLAYER->set_playerAction(MYOBJECT::RUN_EMPTY);
		PLAYER->action_pause();
		_btn_build->set_text_toButton("시작");
	}

	// 프레임 업데이트
	_work_jhammer->frameUpdate(false);
	_work_dust->frameUpdate(false);
}
HRESULT Window::init_setting_fg()
{
	POINT pos, center;
	_fg_title = MyText(MYTEXT::TXT_TITLE, "설정");
	pos.x = (LONG)(_bg->get_center().x - 20);
	pos.y = (LONG)(_bg->get_rect().top + 20);
	_fg_title.set_pos(pos);
	// Button
	_btn_window = new Button(BUTTON::BTN_BUS_GREEN);
	_btn_window->init();
	center.x = (LONG)(_bg->get_center().x);
	center.y = (LONG)(_bg->get_rect().bottom - _btn_window->get_height());
	_btn_window->set_center(center);
	_btn_window->set_text_toButton("게임종료");
	return S_OK;
}
void Window::draw_setting()
{
	Draw(_red_button);
	_fg_title.render(get_memDC());
	Draw(_btn_window);
}
void Window::delete_setting()
{
	Release(_btn_window);
}
void Window::update_setting()
{
	_btn_window->update();
	if (_btn_window->is_clickButton() && _fOpen)
	{
		_scene_forChange = SCENE_TITLE;
		close_window();
	}
	// 윈도우를 열지, 말지 정한다.
	if (_fOpen == false && KEYMANAGER->is_onceKeyDown(VK_ESCAPE))
	{
		_fOpen = true;
	}
	else if (_fOpen == true && KEYMANAGER->is_onceKeyDown(VK_ESCAPE))
	{
		_fOpen = false;
	}
}
//======================================
//##		상점 슬롯 초기화			  ##
//======================================
HRESULT Window::init_slots()
{
	Slot * slot;
	POINT pos;
	switch (_type)
	{
	case WINDOW::WND_SHOP:
		slot = new Slot(SLOT::SLT_ITEM_SHOP, SLOT::ITM_MEAT);
		slot->init();
		pos.x = (LONG)(_locked_back->get_rect().left);
		pos.y = (LONG)(_locked_back->get_rect().top);
		slot->set_slotPos(pos);
		_slots.push_back(slot);
		slot = new Slot(SLOT::SLT_ITEM_SHOP, SLOT::ITM_SODA);
		slot->init();
		slot->set_slotPos(PointMake(pos.x + slot->get_width(), pos.y));
		_slots.push_back(slot);
		slot = new Slot(SLOT::SLT_ITEM_SHOP, SLOT::ITM_PIZZA_BOX);
		slot->init();
		pos.x = (LONG)(_locked_back->get_rect().left);
		pos.y = (LONG)(_locked_back->get_rect().top);
		slot->set_slotPos(PointMake(pos.x, pos.y + slot->get_height()));
		_slots.push_back(slot);
		break;
	case WINDOW::WND_FRIGER:
		slot = new Slot(SLOT::SLT_ITEM_FRIGER, SLOT::ITM_MEAT);
		slot->init();
		pos.x = (LONG)(_locked_back->get_rect().left);
		pos.y = (LONG)(_locked_back->get_rect().top);
		slot->set_slotPos(pos);
		_slots.push_back(slot);
		slot = new Slot(SLOT::SLT_ITEM_FRIGER, SLOT::ITM_SODA);
		slot->init();
		slot->set_slotPos(PointMake(pos.x + slot->get_width(), pos.y));
		_slots.push_back(slot);
		slot = new Slot(SLOT::SLT_ITEM_FRIGER, SLOT::ITM_PIZZA_BOX);
		slot->init();
		pos.x = (LONG)(_locked_back->get_rect().left);
		pos.y = (LONG)(_locked_back->get_rect().top);
		slot->set_slotPos(PointMake(pos.x, pos.y + slot->get_height()));
		_slots.push_back(slot);
		break;
	}
	slot = nullptr;
	return S_OK;
}
void Window::delete_slots()
{
	auto iter = _slots.begin();
	for (; iter != _slots.end();)
	{
		Release(*iter);
		iter = _slots.erase(iter);
	}
	swap(_slots, Slots());
}
void Window::draw_slots()
{
	auto iter = _slots.begin();
	for (; iter != _slots.end(); iter++)
	{
		Draw(*iter);
	}
}
void Window::update_shop()
{
	SLOT::ITEM itemType;
	auto iter = _slots.begin();
	for (; iter != _slots.end(); iter++)
	{
		(*iter)->update();
		if ((*iter)->is_clickButton())
		{
			itemType = (*iter)->get_itemType();
			PLAYER->buy_item(itemType);
			break;
		}
	}
}

void Window::close_window(bool fResetClick)
{
	_fClose = true;
	_fOpen = false;
	_fOpenBus = false;
	if (fResetClick)
	{
		_fClick = false;
	}
	switch (_type)
	{
	case WINDOW::WND_BUILD:
		// 그냥 닫기를 눌러도 종료한다.
		if (_fOpen == false)
		{
			PLAYER->set_playerAction(MYOBJECT::RUN_EMPTY);
			PLAYER->action_pause();
			_btn_build->set_fToggleButton(false);
		}
		break;
	}
}

HRESULT Window::init(WINDOW::TYPE type)
{
	set_imgPath("UI/Window/");
	_type = type;
	// Background 초기화
	init_window_bg(type);
	// Foreground Image 초기화
	switch (type)
	{
	case WINDOW::WND_FRIGER:
		init_inventory();
		init_slots();
		break;
	case WINDOW::WND_SHOP:
		init_inventory();
		init_slots();
		break;
	case WINDOW::WND_LEAGUE:
		init_league();
		break;
	case WINDOW::WND_BUS:
		init_bus_fg();
		break;
	case WINDOW::WND_BUILD:
		init_build_fg();
		break;
	case WINDOW::WND_SETTING:
		init_setting_fg();
		break;
	}
	_fClose = false;
	return S_OK;
}
void Window::release()
{
	delete_window_bg();
	switch (_type)
	{
	case WINDOW::WND_FRIGER:
		delete_inventory();
		break;
	case WINDOW::WND_SHOP:
		delete_inventory();
		break;
	case WINDOW::WND_LEAGUE:
		delete_league();
		break;
	case WINDOW::WND_BUS:
		delete_bus();
		break;
	case WINDOW::WND_BUILD:
		delete_build();
		break;
	case WINDOW::WND_SETTING:
		delete_setting();
		break;
	}
	delete_slots();
}
void Window::update()
{
	switch (_type)
	{
	case WINDOW::WND_BUILD:
		update_build();
		break;
	case WINDOW::WND_SHOP:
		update_shop();
		break;
	case WINDOW::WND_FRIGER:
		update_friger();
		break;
	case WINDOW::WND_SETTING:
		update_setting();
		break;
	default:
		break;
	}//switch: 언제나 업데이트 되어야 하는 것
	if (_fClick == true)
	{
		if (PtInRect(&_red_button->get_rc(), m_ptMouse))
		{
			close_window();
		}// 닫기 버튼을 누르면 닫는다.

		switch (_type)
		{
		case WINDOW::WND_LEAGUE:
			update_league();
			break;
		case WINDOW::WND_BUS:
			update_bus();
			break;
		}//switch: 클릭했을 때 update 되어야 함
	}//if: 클릭 했을 때 인벤토리를 닫는다.
}
void Window::render()
{
	draw_window_bg();
	switch (_type)
	{
	case WINDOW::WND_FRIGER:
		draw_inventory();
		break;
	case WINDOW::WND_SHOP:
		draw_inventory();
		break;
	case WINDOW::WND_LEAGUE:
		draw_league();
		break;
	case WINDOW::WND_BUS:
		draw_bus();
		break;
	case WINDOW::WND_BUILD:
		draw_build();
		break;
	case WINDOW::WND_SETTING:
		draw_setting();
		break;
	}
	draw_slots();
}
Window::Window()
{
	_type = WINDOW::WND_NONE;
}
Window::~Window()
{
}
