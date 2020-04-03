#include "stdafx.h"
#include "Cursor.h"

HRESULT Cursor::init()
{
	set_imgPath("UI/Cursor/");
	HRESULT result;
	int result_cnt = 0;
	string path;
	_arrow = new Image;
	path = _imgPath + "cursor_arrow.bmp";
	result = _arrow->init(path.c_str(), (int)(26 * 1.5), (int)(26 * 1.5));
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);
	_wait = new Image;
	path = _imgPath + "cursor_wait.bmp";
	result = _wait->init(path.c_str(), (int)(26 * 1.5), (int)(26 * 1.5));
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);
	ShowCursor(false);
	return S_OK;
}
void Cursor::release()
{
	Release(_arrow);
	Release(_wait);
}
void Cursor::update()
{
	POINT pos = m_ptMouse;
	pos.x = pos.x - 3;
	pos.y = pos.y - 3;
	if (_fWait == true)
	{
		_wait->set_pos(pos);
	}
	else
	{
		_arrow->set_pos(pos);
	}
}
void Cursor::render()
{
	if (_fWait == true)
	{
		Draw(_wait, get_memDC());
	}
	else
	{
		Draw(_arrow, get_memDC());
	}
}
Cursor::Cursor()
{
}
Cursor::~Cursor()
{
}
