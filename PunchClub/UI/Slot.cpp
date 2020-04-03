#include "stdafx.h"
#include "Slot.h"
#include "Object/Player.h"
void Slot::init_bg(SLOT::TYPE type)
{
	string path;
	switch (type)
	{
	case SLOT::SLT_ACTIVE_SKILL:
		path = _imgPath + "skill_lock_cell.bmp";
		_bg = new Image;
		_bg->init(path.c_str(), (int)(36 * GAME_MULTIPLE), (int)(36 * GAME_MULTIPLE));
		break;
	case SLOT::SLT_ITEM_SHOP:
	case SLOT::SLT_ITEM_FRIGER:
		set_imgPath("UI/Slot/");
		_bg = new Image;
		path = _imgPath + "Inven_slot.bmp";
		_bg->init(path.c_str(), (int)(210 * GAME_MULTIPLE), (int)(60 * GAME_MULTIPLE));
		// Item initial to type
		init_item();
		// Green button
		_btn = new Button(BUTTON::BTN_GREEN_INVEN);
		_btn->init();
		break;
	}
}
void Slot::draw_bg()
{
	Draw(_bg, get_memDC());
	draw_item();
}
void Slot::delete_bg()
{
	Release(_bg);
}

void Slot::init_item()
{
	string path;
	// FG Image's background
	_fg_back = new Image;
	path = _imgPath + "Item_bg.bmp";
	_fg_back->init(path.c_str(), (int)(40 * GAME_MULTIPLE), (int)(40 * GAME_MULTIPLE));
	switch (_itemType)
	{
	case SLOT::ITM_MEAT:
		_fg = new Image;
		path = _imgPath + "Meat.bmp";
		_fg->init(path.c_str(), (int)(39 * GAME_MULTIPLE), (int)(40 * GAME_MULTIPLE));
		
		_title = MyText(MYTEXT::TXT_DESCR, "고기", RGB(241, 223, 187));
		_title.set_size(30);
		_descr = MyText(MYTEXT::TXT_DESCR, "음메에?", RGB(54, 50, 39));
		break;
	case SLOT::ITM_SODA:
		_fg = new Image;
		path = _imgPath + "Soda.bmp";
		_fg->init(path.c_str(), (int)(27 * GAME_MULTIPLE), (int)(40 * GAME_MULTIPLE));

		_title = MyText(MYTEXT::TXT_DESCR, "소다", RGB(241, 223, 187));
		_title.set_size(30);
		_descr = MyText(MYTEXT::TXT_DESCR, "달고 맛있다. 하지만 건강에는 나쁘다.", RGB(54, 50, 39));
		_descr.set_size(22);
		break;
	case SLOT::ITM_PIZZA_BOX:
		_fg = new Image;
		path = _imgPath + "Pizza_box.bmp";
		_fg->init(path.c_str(), (int)(46 * GAME_MULTIPLE), (int)(32 * GAME_MULTIPLE));

		_title = MyText(MYTEXT::TXT_DESCR, "냉동 피자", RGB(241, 223, 187));
		_title.set_size(30);
		_descr = MyText(MYTEXT::TXT_DESCR, "평범한 피자와 같지만 냉동이 되어있다.", RGB(54, 50, 39));
		_descr.set_size(20);
		
		break;
	}
	_icon = new Icon(ICON::ICN_FRIGER);
	_icon->init();
}
void Slot::draw_item()
{
	Draw(_fg_back, get_memDC());
	Draw(_fg, get_memDC());
	_title.render(get_memDC());
	_descr.render(get_memDC());
	Draw(_icon);
}
void Slot::setup_fg_center()
{
	POINT center;
	
	if (_fg != nullptr)
	{
		// Setup positions
		center.x = (LONG)(_bg->get_rect().left + _fg->get_width() * 0.65);
		center.y = (LONG)(_bg->get_center().y);
		_fg->set_center(center);
	}
	if (_fg_back != nullptr)
	{
		_fg_back->set_center(center);
	}
}
void Slot::setup_text_pos()
{
	POINT pos;
	if (_fg_back != nullptr)
	{
		pos.x = (LONG)(_fg_back->get_rect().right + 10);
		pos.y = (LONG)(_fg_back->get_rect().top - 10);
		_title.set_pos(pos);
		pos.y += 40;
		_descr.set_pos(pos);
	}
}
void Slot::setup_button()
{
	POINT center;
	
	if (_btn != nullptr)
	{
		switch (_type)
		{
		case SLOT::SLT_ITEM_SHOP:
			center.x = (LONG)(_bg->get_rect().right - _btn->get_width() * 0.6);
			center.y = (LONG)(_bg->get_rect().bottom - _btn->get_height() * 0.7);
			_btn->set_center(center);
			switch (_itemType)
			{
			case SLOT::ITM_MEAT:
				_btn->set_text_toButton("$20", 25, MYTEXT::TXT_DESCR);
				break;
			case SLOT::ITM_SODA:
				_btn->set_text_toButton("$6", 25, MYTEXT::TXT_DESCR);
				break;
			case SLOT::ITM_PIZZA_BOX:
				_btn->set_text_toButton("$9", 25, MYTEXT::TXT_DESCR);
				break;
			}
			break;
		case SLOT::SLT_ITEM_FRIGER:
			center.x = (LONG)(_bg->get_rect().right - _btn->get_width() * 0.6);
			center.y = (LONG)(_bg->get_rect().bottom - _btn->get_height() * 0.7);
			_btn->set_center(center);
			switch (_itemType)
			{
			case SLOT::ITM_MEAT:
			case SLOT::ITM_SODA:
			case SLOT::ITM_PIZZA_BOX:
				_btn->set_text_toButton("먹다", 25, MYTEXT::TXT_DESCR);
				break;
			}
			break;
		}
	}
}
void Slot::setup_icon()
{
	POINT center;
	if (_itemType != SLOT::ITM_EMPTY)
	{
		center.x = (LONG)(_bg->get_rect().right - _icon->get_width() * 0.8);
		center.y = (LONG)(_bg->get_rect().top + _icon->get_height() * 0.5);
		_icon->set_center(center);
		_icon->set_text_toIcon(to_string(PLAYER->how_many_items(_itemType)));
	}
	switch (_itemType)
	{
	case SLOT::ITM_MEAT:
		init_icons(10, 0, 1, 40);
		break;
	case SLOT::ITM_SODA:
		init_icons(0, 0, 1, 9);
		break;
	case SLOT::ITM_PIZZA_BOX:
		init_icons(10, 0, 1, 17);
		break;
	}//switch: icons
}

HRESULT Slot::init_icons(int health, int energy, int mood, int food)
{
	Icon * icon;
	POINT center;
	int blank = 50;
	center.x = (LONG)(_fg_back->get_rect().right - 30);
	center.y = (LONG)(_fg_back->get_rect().bottom);
	if (health != 0)
	{
		icon = new Icon(ICON::ICN_HEALTH);
		icon->init();
		center.x += blank;
		icon->set_center(center);
		icon->set_text_toIcon(to_string(health));
		_icons.push_back(icon);
		icon = nullptr;
	}
	if (energy != 0)
	{
		icon = new Icon(ICON::ICN_ENERGY);
		icon->init();
		center.x += blank;
		icon->set_center(center);
		icon->set_text_toIcon(to_string(energy));
		_icons.push_back(icon);
		icon = nullptr;
	}
	if (mood != 0)
	{
		icon = new Icon(ICON::ICN_MOOD);
		icon->init();
		center.x += blank;
		icon->set_center(center);
		icon->set_text_toIcon(to_string(mood));
		_icons.push_back(icon);
		icon = nullptr;
	}
	if (food != 0)
	{
		icon = new Icon(ICON::ICN_FOOD);
		icon->init();
		center.x += blank;
		icon->set_center(center);
		icon->set_text_toIcon(to_string(food));
		_icons.push_back(icon);
		icon = nullptr;
	}

	return S_OK;
}

void Slot::delete_icons()
{
	auto iter = _icons.begin();
	for (; iter != _icons.end();)
	{
		Release(*iter);
		iter = _icons.erase(iter);
	}
	swap(_icons, Icons());
}
void Slot::draw_icons()
{
	auto iter = _icons.begin();
	for (; iter != _icons.end(); iter++)
	{
		Draw(*iter);
	}
}

HRESULT Slot::init()
{
	set_imgPath("UI/Skill/");
	init_bg(_type);
	return S_OK;
}
void Slot::release()
{
	delete_bg();
	Release(_fg);
	Release(_fg_back);
	Release(_btn);
	Release(_icon);
	delete_icons();
}
void Slot::update()
{
	_btn->update();
	if (_icon != nullptr)
	{
		_icon->set_text_toIcon(to_string(PLAYER->how_many_items(_itemType)));
	}
}
void Slot::render()
{
	draw_bg();
	draw_item();
	Draw(_btn);
	draw_icons();
}
Slot::Slot(SLOT::TYPE type)
{
	_type = type;
}
Slot::Slot(SLOT::TYPE type, SLOT::ITEM itemType)
{
	_type = type;
	_itemType = itemType;
}
Slot::~Slot()
{
}

void Slot::set_slotCenter(POINT center)
{
	if (_bg != nullptr)
	{
		_bg->set_center(center);
		setup_fg_center();
		setup_text_pos();
		setup_button();
		setup_icon();
	}
}
void Slot::set_slotPos(POINT pos)
{
	if (_bg != nullptr)
	{
		_bg->set_pos(pos);
		setup_fg_center();
		setup_text_pos();
		setup_button();
		setup_icon();
	}
}
