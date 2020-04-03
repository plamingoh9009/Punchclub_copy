#include "stdafx.h"
#include "MapIcon.h"
#include "Object/Player.h"
void MapIcon::update_playerIcon()
{
	if (_fplayerIcon_move == true)
	{
		_playerIcon_location = PLAYER->get_playerLocation();
		_fplayerIcon_move = false;
	}
}

bool MapIcon::is_player_atHere()
{
	if (_type != MAPICON::ICN_PLAYER)
	{
		if (_type == _playerIcon_location)
		{
			return true;
		}
	}//if: �÷��̾ ���� ���� ������ true
	return false;
}

HRESULT MapIcon::init_icon()
{
	string path;
	POINT center;
	_icon_off = new Image;
	_icon_on = new Image;
	switch (_type)
	{
	case MAPICON::ICN_HOME:
		path = _imgPath + "Hud_home.bmp";
		_icon_off->init(path.c_str(), (int)(46 * GAME_MULTIPLE), (int)(33 * GAME_MULTIPLE));
		path = _imgPath + "Hud_home_on.bmp";
		_icon_on->init(path.c_str(), (int)(46 * GAME_MULTIPLE), (int)(33 * GAME_MULTIPLE));

		center.x = (LONG)(WIN_HALF_W - WIN_HALF_W * 0.38);
		center.y = (LONG)(WIN_HALF_H + WIN_HALF_H * 0.42);
		_icon_off->set_center(center);
		_icon_on->set_center(center);
		_sceneType = SCENE_HOME;
		break;
	case MAPICON::ICN_SHOP:
		path = _imgPath + "Hud_shop.bmp";
		_icon_off->init(path.c_str(), (int)(46 * GAME_MULTIPLE), (int)(32 * GAME_MULTIPLE));
		path = _imgPath + "Hud_shop_on.bmp";
		_icon_on->init(path.c_str(), (int)(46 * GAME_MULTIPLE), (int)(32 * GAME_MULTIPLE));
		center.x = (LONG)(WIN_HALF_W + _icon_off->get_width() * 0.7);
		center.y = (LONG)(WIN_HALF_H + _icon_off->get_height() * 0.25);
		_icon_off->set_center(center);
		_icon_on->set_center(center);
		_sceneType = SCENE_SHOP;
		break;
	case MAPICON::ICN_GYM:
		path = _imgPath + "Hud_gym.bmp";
		_icon_off->init(path.c_str(), (int)(48 * GAME_MULTIPLE), (int)(31 * GAME_MULTIPLE));
		path = _imgPath + "Hud_gym_on.bmp";
		_icon_on->init(path.c_str(), (int)(48 * GAME_MULTIPLE), (int)(31 * GAME_MULTIPLE));
		center.x = (LONG)(WIN_HALF_W - _icon_off->get_width() * 0.85);
		center.y = (LONG)(WIN_HALF_H - _icon_off->get_height() * 0.3);
		_icon_off->set_center(center);
		_icon_on->set_center(center);
		_sceneType = SCENE_GYM;
		break;
	case MAPICON::ICN_BUILD:
		path = _imgPath + "Hud_build.bmp";
		_icon_off->init(path.c_str(), (int)(46 * GAME_MULTIPLE), (int)(42 * GAME_MULTIPLE));
		path = _imgPath + "Hud_build_on.bmp";
		_icon_on->init(path.c_str(), (int)(46 * GAME_MULTIPLE), (int)(42 * GAME_MULTIPLE));
		center.x = (LONG)(WIN_HALF_W - _icon_off->get_width() * 4.3125);
		center.y = (LONG)(WIN_HALF_H - _icon_off->get_height() * 2);
		_icon_off->set_center(center);
		_icon_on->set_center(center);
		_sceneType = SCENE_BUILD;
		break;
	case MAPICON::ICN_PLAYER:
		path = _imgPath + "Map_player.bmp";
		_icon_off->init(path.c_str(), (int)(30 * GAME_MULTIPLE), (int)(40 * GAME_MULTIPLE));
		_icon_on = nullptr;
		break;
	default:
		break;
	}
	// Result
	if (_type == MAPICON::ICN_PLAYER)
	{
		if (_icon_off != nullptr)
		{
			return S_OK;
		}
	}
	else
	{
		if (_icon_off != nullptr && _icon_on != nullptr)
		{
			return S_OK;
		}
	}
	return E_FAIL;
}
void MapIcon::draw_icon()
{
	if (_type == MAPICON::ICN_PLAYER)
	{
		if (_icon_off != nullptr)
		{
			Draw(_icon_off, get_memDC());
		}
	}
	else
	{
		if (_icon_on != nullptr && _fIcon == true)
		{
			Draw(_icon_on, get_memDC());
		}
		else if (_icon_off != nullptr && _fIcon == false)
		{
			Draw(_icon_off, get_memDC());
		}
	}//else: �÷��̾� �ƴ� ������ ����
}
void MapIcon::delete_icon()
{
	if (_icon_off != nullptr)
	{
		_icon_off->release();
		_icon_off = nullptr;
	}
	if (_icon_on != nullptr)
	{
		_icon_on->release();
		_icon_on = nullptr;
	}
}
void MapIcon::update_icon()
{
	if (PtInRect(&_icon_off->get_rect(), m_ptMouse))
	{
		_fIcon = true;
		if (_fClick && _type != MAPICON::ICN_PLAYER)
		{
			if (is_player_atHere() == true)
			{
				_scene_forChange = _sceneType;
				_fClick = false;
				// ������ ������ �� �� ���� �ִ�.
				_fOpenWindow = true;
			}
			else
			{
				PLAYER->set_playerLocation(_type);
				_fOpenBus = true;
			}
		}//if: Ŭ���ϸ� �÷��̾��� ��ġ ������Ʈ, �÷��̾ ���� ������ ������Ʈ X
	}//if: ���콺�� �ö���� �����ܿ� �����
	else
	{
		_fIcon = false;
	}
	if (_type == MAPICON::ICN_PLAYER)
	{
		update_playerIcon();
	}
}
HRESULT MapIcon::init_hint()
{
	POINT center;
	string title, descr;
	if (_type != MAPICON::ICN_PLAYER)
	{
		center.x = (LONG)(_icon_off->get_center().x);
		center.y = (LONG)(_icon_off->get_center().y);
		_hint->set_center(center);
	}
	switch (_type)
	{
	case MAPICON::ICN_HOME:
		title = "����";
		descr = "������� ���� �԰ų�, �濡�� �޽��� �� �ֽ��ϴ�.";
		_hint->set_texts(title, descr);
		break;
	case MAPICON::ICN_SHOP:
		title = "����";
		descr = "�ķ�ǰ �� �������帵ũ�� ������ �� �ֽ��ϴ�.";
		_hint->set_texts(title, descr);
		break;
	case MAPICON::ICN_GYM:
		title = "ü����";
		descr = "������ ������ �����Ͽ� ������ Ʈ���̴��� �մϴ�.";
		_hint->set_texts(title, descr);
		break;
	case MAPICON::ICN_BUILD:
		title = "��";
		descr = "�ð��� ü���� �Ҹ��ؼ� ���� ���ϴ�.";
		_hint->set_texts(title, descr);
		break;
	}
	return S_OK;
}
//==========================================
//##			Hint					  ##
//==========================================
void MapIcon::update_hint()
{
	if (_fIcon == true)
	{
		_hint->update();
	}
}
void MapIcon::draw_hint()
{
	if (_fIcon == true)
	{
		Draw(_hint);
	}
}

HRESULT MapIcon::init(MAPICON::TYPE type)
{
	set_imgPath("UI/Icon/");
	HRESULT result;
	int result_cnt = 0;

	_type = type;
	result = init_icon();
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);
	_hint = new Hint(HINT::HINT_NORMAL);
	result = _hint->init();
	result_cnt = (result == S_OK ? result_cnt : result_cnt++);
	result = (result_cnt == 0 ? S_OK : E_FAIL);
	// Hint
	init_hint();
	return result;
}
void MapIcon::release()
{
	delete_icon();
	Release(_hint);
}
void MapIcon::update()
{
	update_icon();
	update_hint();
}
void MapIcon::render()
{
	draw_icon();
}
MapIcon::MapIcon()
{
}
MapIcon::~MapIcon()
{
}

HRESULT MapIcon::set_center(POINT center)
{
	RECT rc;
	rc = RectMakeCenter(center.x, center.y, _icon_off->get_width(), _icon_off->get_height());
	if (_type == MAPICON::ICN_PLAYER)
	{
		_icon_off->set_rect(rc);
		return S_OK;
	}
	else
	{
		_icon_off->set_rect(rc);
		_icon_on->set_rect(rc);
		return S_OK;
	}//else: �÷��̾� ������ ���� �ٸ� �������̸� on, off ����
	return E_FAIL;
}
