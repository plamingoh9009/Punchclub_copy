#include "stdafx.h"
#include "Npc.h"

HRESULT Npc::init_npc()
{
	string path;
	POINT center, pos;
	switch (_type)
	{
	case NPC::NPC_SHOP:
		_img_off = new Image;
		path = _imgPath + "shop_off.bmp";
		_img_off->init(path.c_str(), (int)(57 * GAME_MULTIPLE), (int)(43 * GAME_MULTIPLE));
		center.x = (LONG)(WIN_HALF_W - _img_off->get_width() * 1.711);
		center.y = (LONG)(WIN_HALF_H - _img_off->get_height() * 1.8672);
		_img_off->set_center(center);
		_img_on = new Image;
		path = _imgPath + "shop_on.bmp";
		_img_on->init(path.c_str(), (int)(57 * GAME_MULTIPLE), (int)(43 * GAME_MULTIPLE));
		center.x = (LONG)(WIN_HALF_W - _img_off->get_width() * 1.711);
		center.y = (LONG)(WIN_HALF_H - _img_off->get_height() * 1.8672);
		_img_on->set_center(center);
		// Name
		_name = MyText(MYTEXT::TXT_DESCR, "상점 주인", RGB(244, 221, 15));
		_name.init();
		pos.x = (LONG)(_img_off->get_center().x - 25);
		pos.y = (LONG)(_img_off->get_rect().top - 25);
		_name.set_pos(pos);
		break;
	}
	return S_OK;
}
void Npc::draw_npc()
{
	if (_fImgOn == true)
	{
		if (_img_on != nullptr)
		{
			Draw(_img_on, get_memDC());
			_name.render(get_memDC());
		}
	}
	else
	{
		if (_img_off != nullptr)
		{
			Draw(_img_off, get_memDC());
		}
	}
}

HRESULT Npc::init()
{
	set_imgPath("Object/NPC/");
	init_npc();
	return S_OK;
}
void Npc::release()
{
	Release(_img_off);
	Release(_img_on);
	_name.release();
}
void Npc::update()
{
	if (PtInRect(&_img_off->get_rect(), m_ptMouse))
	{
		_fImgOn = true;
		if (_fClick == true)
		{
			_fOpenShop = true;
		}
	}
	else
	{
		_fImgOn = false;
		_fOpenShop = false;
	}
}
void Npc::render()
{
	draw_npc();
}
Npc::Npc(NPC::TYPE type)
{
	_type = type;
}
Npc::~Npc()
{
}
