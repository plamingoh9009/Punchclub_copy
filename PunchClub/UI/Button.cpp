#include "stdafx.h"
#include "Button.h"

HRESULT Button::init_red_button()
{
	_button = new Image;
	// Init
	string path;
	path = _imgPath + "Btn_red_back.bmp";
	_button->init(path.c_str(), (int)(20 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
	return S_OK;
}
//==========================================
//##		Long Red Button			  ##
//==========================================
HRESULT Button::init_long_red_button()
{
	_button = new Image;
	string path = _imgPath + "Btn_red_long.bmp";
	_button->init(path.c_str(), (int)(57 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
	return S_OK;
}
void Button::update_long_red_button()
{
}
HRESULT Button::init_delete_red_button()
{
	string path;
	// Init
	_button = new Image;
	path = _imgPath + "Btn_red_back.bmp";
	_button->init(path.c_str(), (int)(20 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
	_icon = new Image;
	path = _imgPath + "del_icon.bmp";
	_icon->init(path.c_str(), (int)(18 * GAME_MULTIPLE), (int)(18 * GAME_MULTIPLE));
	_iconType = BUTTON::ICN_DELETE;
	return S_OK;
}
void Button::update_delete_red_button()
{
	if (_fClick)
	{
		if (PtInRect(&_button->get_rect(), m_ptMouse))
		{
			_fCloseWindow = true;
		}
	}
}
//==========================================
//##		Long Green Button			  ##
//==========================================
HRESULT Button::init_long_green_button()
{
	_button = new Image;
	string path = _imgPath + "Btn_green_long.bmp";
	_button->init(path.c_str(), (int)(57 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
	return S_OK;
}
void Button::update_long_green_button()
{
}
//==========================================
//##		Bus Green Button			  ##
//==========================================
HRESULT Button::init_bus_green_button()
{
	_button = new Image;
	string path = _imgPath + "Btn_bus_green.bmp";
	_button->init(path.c_str(), (int)(107 * GAME_MULTIPLE), (int)(30 * GAME_MULTIPLE));
	return S_OK;
}
void Button::update_bus_green_button()
{
	if (_fClick)
	{
		if (PtInRect(&_button->get_rect(), m_ptMouse))
		{
			switch (_iconType)
			{
			case BUTTON::ICN_DOLLAR:
				break;
			case BUTTON::ICN_TIME_DAYS:
				break;
			}
			_fCloseWindow = true;
			_fplayerIcon_move = true;
		}
	}
}

HRESULT Button::init_green_button()
{
	_button = new Image;
	string path = _imgPath + "Btn_green.bmp";
	_button->init(path.c_str(), (int)(19 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
	return S_OK;
}
void Button::update_green_button()
{
}

HRESULT Button::init_green_inven()
{
	string path = _imgPath + "Btn_green_inven.bmp";
	_button = new Image;
	_button->init(path.c_str(), (int)(35 * GAME_MULTIPLE), (int)(15 * GAME_MULTIPLE));
	return E_NOTIMPL;
}

void Button::update_green_inven()
{
}

void Button::draw_text_toButton()
{
	_text.render(get_memDC());
}

void Button::check_click_button()
{
	if (_button != nullptr)
	{
		if (PtInRect(&_button->get_rect(), m_ptMouse))
		{
			_fClickButton = true;
			_fToggleButton = !_fToggleButton;
		}
	}
}

HRESULT Button::init()
{
	set_imgPath("UI/Button/");
	switch (_type)
	{
	case BUTTON::BTN_RED:
		init_red_button();
		break;
	case BUTTON::BTN_RED_LONG:
		init_long_red_button();
		break;
	case BUTTON::BTN_DELETE_RED:
		init_delete_red_button();
		break;
	case BUTTON::BTN_GREEN_LONG:
		init_long_green_button();
		break;
	case BUTTON::BTN_BUS_GREEN:
	case BUTTON::BTN_WORK_GREEN:
		init_bus_green_button();
		break;
	case BUTTON::BTN_GREEN:
		init_green_button();
		break;
	case BUTTON::BTN_GREEN_INVEN:
		init_green_inven();
		break;
	}
	return S_OK;
}
void Button::release()
{
	if (_button != nullptr)
	{
		Release(_button);
	}
	if (_icon != nullptr)
	{
		Release(_icon);
	}
}
void Button::update()
{
	switch (_type)
	{
	case BUTTON::BTN_DELETE_RED:
		update_delete_red_button();
		break;
	case BUTTON::BTN_BUS_GREEN:
		update_bus_green_button();
		break;
	}

	if (_fClick == true)
	{
		check_click_button();
	}
	else
	{
		_fClickButton = false;
	}
}
void Button::render()
{
	if (_button != nullptr) { Draw(_button, get_memDC()); }
	if (_icon != nullptr) { Draw(_icon, get_memDC()); }
	if (_fText) { draw_text_toButton(); }
}
Button::Button(BUTTON::TYPE type)
{
	_type = type;
}
Button::~Button()
{
}

void Button::set_text_toButton(string text, int size, MYTEXT::TYPE type)
{
	POINT pos;
	_text = MyText(type, text, RGB(254, 254, 254));
	pos.x = (LONG)(_button->get_center().x - text.length() * 5);
	pos.y = (LONG)(_button->get_center().y - size * 0.5);
	_text.set_pos(pos);
	_text.set_size(size);
	_fText = true;
}

void Button::set_icon_toButton(BUTTON::ICON type, POINT center)
{
	string path;
	_icon = new Image;
	_iconType = type;
	switch (type)
	{
	case BUTTON::ICN_DOLLAR:
		path = _imgPath + "dollar_icon.bmp";
		_icon->init(path.c_str(), (int)(15 * GAME_MULTIPLE), (int)(15 * GAME_MULTIPLE));
		break;
	case BUTTON::ICN_TIME_DAYS:
		path = _imgPath + "time_days_icon.bmp";
		_icon->init(path.c_str(), (int)(11 * GAME_MULTIPLE), (int)(11 * GAME_MULTIPLE));
		break;
	}
	_icon->set_center(center);
}
void Button::set_center(POINT center)
{
	_button->set_center(center);
}

void Button::set_pos_toRT_edge(RECT rc)
{
	POINT center;
	center.x = (LONG)(rc.right - _button->get_width() * 0.7);
	center.y = (LONG)(rc.top + _button->get_height() * 0.7);
	_button->set_center(center);

	center.x -= (LONG)(_icon->get_width() * 0.06);
	center.y -= (LONG)(_icon->get_height() * 0.06);
	_icon->set_center(center);
}
