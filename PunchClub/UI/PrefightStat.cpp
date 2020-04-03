#include "stdafx.h"
#include "PrefightStat.h"

void PrefightStat::draw_name()
{
	FontTextShadow(get_memDC(), _name_pos.x, _name_pos.y, _name.c_str(),
		"ÈÞ¸Õ¸ÅÁ÷Ã¼", 30, RGB(254, 254, 254));
}

void PrefightStat::init_icons()
{
	string path;
	POINT center;
	center.x = (LONG)((_bg_rc.left + _bg_rc.right) * 0.5);
	center.y = (LONG)((_bg_rc.top + _bg_rc.bottom) * 0.5);
	// ½ºÅÈ ÀÌ¹ÌÁö
	path = _imgPath + "icon_agl.bmp";
	_agl_icon = new Image;
	_agl_icon->init(path.c_str(), (int)(20 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
	center.x = (LONG)(center.x - _agl_icon->get_width() * 2.75);
	_agl_rc = RectMakeCenter(center.x, center.y,
		_agl_icon->get_width(), _agl_icon->get_height());
	path = _imgPath + "icon_str.bmp";
	_str_icon = new Image;
	_str_icon->init(path.c_str(), (int)(20 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
	_str_rc = RectMakeCenter(center.x, (int)(center.y - _str_icon->get_height() * 1.25),
		_str_icon->get_width(), _str_icon->get_height());
	path = _imgPath + "icon_stm.bmp";
	_stm_icon = new Image;
	_stm_icon->init(path.c_str(), (int)(20 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
	_stm_rc = RectMakeCenter(center.x, (int)(center.y + _stm_icon->get_height() * 1.25),
		_stm_icon->get_width(), _stm_icon->get_height());
}
void PrefightStat::draw_icons()
{
	_agl_icon->render(get_memDC(), _agl_rc.left, _agl_rc.top);
	FontTextShadow(get_memDC(), _agl_rc.left + 45, _agl_rc.top + 8, _agl.c_str(),
		"ÈÞ¸Õ¸ÅÁ÷Ã¼", 30, RGB(254, 254, 254));
	_str_icon->render(get_memDC(), _str_rc.left, _str_rc.top);
	FontTextShadow(get_memDC(), _str_rc.left + 45, _str_rc.top + 8, _str.c_str(),
		"ÈÞ¸Õ¸ÅÁ÷Ã¼", 30, RGB(254, 254, 254));
	_stm_icon->render(get_memDC(), _stm_rc.left, _stm_rc.top);
	FontTextShadow(get_memDC(), _stm_rc.left + 45, _stm_rc.top + 8, _stm.c_str(),
		"ÈÞ¸Õ¸ÅÁ÷Ã¼", 30, RGB(254, 254, 254));
}
void PrefightStat::delete_icons()
{
	_agl_icon->release();
	_agl_icon = nullptr;
	_str_icon->release();
	_str_icon = nullptr;
	_stm_icon->release();
	_stm_icon = nullptr;
}

HRESULT PrefightStat::init()
{
	set_imgPath("UI/Fight/");
	string path = _imgPath + "prefight_window_brw.bmp";
	_bg = new Image;
	_bg->init(path.c_str(), (int)(186 * GAME_MULTIPLE), (int)(93 * GAME_MULTIPLE));
	return S_OK;
}

void PrefightStat::release()
{
	_bg->release();
	_bg = nullptr;
	if (_fStat)
	{
		delete_icons();
	}
}

void PrefightStat::update()
{
}

void PrefightStat::render()
{
	_bg->render(get_memDC(), _bg_rc.left, _bg_rc.top);
	draw_name();
	if (_fStat)
	{
		draw_icons();
	}
}

PrefightStat::PrefightStat()
{
}

PrefightStat::~PrefightStat()
{
}

void PrefightStat::set_window(POINT center, string name, bool name_left)
{
	_bg_rc = RectMakeCenter(center.x, center.y, _bg->get_width(), _bg->get_height());
	_name = name;
	_fName_left = name_left;
	POINT pos;
	if (name_left)
	{
		pos.x = (LONG)(_bg_rc.left + 5);
		pos.y = (LONG)(_bg_rc.top - 40);
		_name_pos = pos;
	}
	else
	{
		pos.x = (LONG)(_bg_rc.right - name.length() * 20);
		pos.y = (LONG)(_bg_rc.top - 40);
		_name_pos = pos;
	}
}
void PrefightStat::set_stat(int str, int stm, int agl)
{
	_str = to_string(str);
	_stm = to_string(stm);
	_agl = to_string(agl);
	init_icons();
	_fStat = true;
}
