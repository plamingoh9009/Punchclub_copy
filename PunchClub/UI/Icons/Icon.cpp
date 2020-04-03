#include "stdafx.h"
#include "Icon.h"

void Icon::init_icons()
{
	string path;
	string title;
	string descr;
	// 이미지 불러오기
	_bg = new Image;
	path = _imgPath + "Hud_btn_main_bg.bmp";
	_bg->init(path.c_str(), (int)(41 * GAME_MULTIPLE), (int)(41 * GAME_MULTIPLE));
	_fg = new Image;
	switch (_type)
	{
	case ICON::ICN_HUD_MAP:
		path = _imgPath + "Icon_map.bmp";
		_fg->init(path.c_str(), (int)(35 * GAME_MULTIPLE), (int)(33 * GAME_MULTIPLE));
		title = "시내 지도";
		descr = "클릭하면 시내 지도를 열어, 다른 장소로 이동할 수 있습니다.";
		// Hint
		_hint = new Hint(HINT::HINT_NORMAL);
		_hint->init();
		_hint->set_texts(title, descr);
		break;
	case ICON::ICN_LEAGUE:
		path = _imgPath + "Icon_league.bmp";
		_fg->init(path.c_str(), (int)(26 * GAME_MULTIPLE), (int)(29 * GAME_MULTIPLE));
		title = "파이트 리그";
		descr = "리그, 대전 상태, 다음 시합에 관한 정보를 볼 수 있습니다.";
		// Hint
		_hint = new Hint(HINT::HINT_NORMAL);
		_hint->init();
		_hint->set_texts(title, descr);
		break;
	case ICON::ICN_SKILLTREE:
		path = _imgPath + "Icon_skilltree.bmp";
		_fg->init(path.c_str(), (int)(37 * GAME_MULTIPLE), (int)(37 * GAME_MULTIPLE));
		title = "스킬 트리";
		descr = "스킬 목록을 열어 새로운 기술을 구입하려면, 이곳을 클릭하세요.";
		// Hint
		_hint = new Hint(HINT::HINT_NORMAL);
		_hint->init();
		_hint->set_texts(title, descr);
		break;
	case ICON::ICN_ENERGY:
		path = _imgPath + "Energy_icon.bmp";
		_fg->init(path.c_str(), (int)(13 * GAME_MULTIPLE), (int)(13 * GAME_MULTIPLE));
		_fFgOnly = true;
		break;
	case ICON::ICN_MOOD:
		path = _imgPath + "Feel_icon.bmp";
		_fg->init(path.c_str(), (int)(13 * GAME_MULTIPLE), (int)(13 * GAME_MULTIPLE));
		_fFgOnly = true;
		break;
	case ICON::ICN_FOOD:
		path = _imgPath + "Food_icon.bmp";
		_fg->init(path.c_str(), (int)(13 * GAME_MULTIPLE), (int)(13 * GAME_MULTIPLE));
		_fFgOnly = true;
		break;
	case ICON::ICN_HEALTH:
		path = _imgPath + "Health_icon.bmp";
		_fg->init(path.c_str(), (int)(13 * GAME_MULTIPLE), (int)(13 * GAME_MULTIPLE));
		_fFgOnly = true;
		break;
	case ICON::ICN_STR:
		path = _imgPath + "icon_str.bmp";
		_fg->init(path.c_str(), (int)(20 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
		_fFgOnly = true;
		break;
	case ICON::ICN_AGL:
		path = _imgPath + "icon_agl.bmp";
		_fg->init(path.c_str(), (int)(20 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
		_fFgOnly = true;
		break;
	case ICON::ICN_STM:
		path = _imgPath + "icon_stm.bmp";
		_fg->init(path.c_str(), (int)(20 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
		_fFgOnly = true;
		break;
	case ICON::ICN_FRIGER:
		path = _imgPath + "fridge_icon.bmp";
		_fg->init(path.c_str(), (int)(14 * GAME_MULTIPLE), (int)(24 * GAME_MULTIPLE));
		_fFgOnly = true;
		break;
	case ICON::ICN_HUNGER:
		path = _imgPath + "icon_hunger.bmp";
		_fg->init(path.c_str(), (int)(200 * 1.6), (int)(21 * 1.6), 8, 1);
		_fg->set_frameSection(1, 0, 7, 0.1f);
		_fFgOnly = true;
		// Hint
		_hint = new Hint(HINT::HINT_THINK);
		_hint->init();
		_fHint_bg = true;
		_fUseDrawTime = true;
		break;
	}
}
void Icon::draw_icons()
{
	if (_fUseDrawTime)
	{
		if (_fVisible)
		{
			draw_icon(false);
		}
	}
	else
	{
		draw_icon();
	}
}
void Icon::delete_icons()
{
	Release(_bg);
	Release(_fg);
}
void Icon::draw_icon(bool isAlwaysVisible)
{
	if (isAlwaysVisible)
	{
		if (_fFgOnly == false)
		{
			Draw(_bg, get_memDC());
		}

		if (is_frameImg(_fg))
		{
			if (_fHint_bg)
			{
				Draw(_hint);
			}
			_fg->frameRender(get_memDC());
		}
		else
		{
			Draw(_fg, get_memDC());
		}
	}
	else
	{
		_drawTime += TIMEMANAGER->get_elapsedTime();
		if (_drawTime < _maxVisibleTime)
		{
			if (_fFgOnly == false)
			{
				Draw(_bg, get_memDC());
			}
			else
			{
				if (is_frameImg(_fg))
				{
					if (_fHint_bg)
					{
						Draw(_hint);
					}
					_fg->frameRender(get_memDC());
				}
				else
				{
					Draw(_fg, get_memDC());
				}
			}

		}//if: Wait 2.5 Sec
		else
		{
			_fVisible = false;
			_drawTime = 0;
		}
	}
}
void Icon::draw_hint()
{
	Draw(_hint);
}

HRESULT Icon::init()
{
	set_imgPath("UI/Icon/");
	init_icons();
	return S_OK;
}
void Icon::release()
{
	delete_icons();
}
void Icon::update()
{
	//==========================================
	//##			아이콘 클릭처리			  ##
	//==========================================
	if (PtInRect(&_bg->get_rect(), m_ptMouse))
	{
		if (_fClick == true)
		{
			switch (_type)
			{
			case ICON::ICN_HUD_MAP:
				_scene_forChange = SCENE_HUD_MAP;
				break;
			case ICON::ICN_LEAGUE:
				_fLeague = true;
				break;
			case ICON::ICN_SKILLTREE:
				_scene_forChange = SCENE_SKILLTREE;
				break;
			default:
				_fLeague = false;
				break;
			}
			// 아이콘을 누를 때 플레이어 못움직이게 한다.
			if (_type != ICON::ICN_EMPTY) { _obj->set_fObjMove(false); }
		}//if: 클릭 했다면
		if (_hint != nullptr)
		{
			_hint->update();
			_fHint = true;
		}
	}//if: 마우스가 지나가면 힌트를 띄운다.
	else
	{
		_fHint = false;
	}
	//==========================================
	//##			아이콘 프레임처리			  ##
	//==========================================
	if (is_frameImg(_fg))
	{
		_fg->frameUpdate(false);
	}
}
void Icon::render()
{
	draw_icons();
	if (_fIconText == true)
	{
		_icon_txt.render(get_memDC());
	}
}
Icon::Icon(ICON::TYPE type)
{
	_type = type;
}
Icon::~Icon()
{
}

void Icon::set_center(POINT center)
{
	POINT myCenter;
	if (_bg != nullptr)
	{
		_bg->set_center(center);
	}
	if (_fg != nullptr)
	{
		_fg->set_center(center);
	}
	switch (_type)
	{
	case ICON::ICN_HUNGER:
		if (_hint != nullptr)
		{
			myCenter.x = (LONG)(center.x);
			myCenter.y = (LONG)(center.y + 5);
			_hint->set_center(myCenter);
		}
		break;
	default:
		if (_hint != nullptr)
		{
			_hint->set_center(center);
		}
		break;
	}
}

int Icon::get_width()
{
	if (_fFgOnly == true)
	{
		if (is_frameImg(_fg))
		{
			return _fg->get_frameWidth();
		}
		else
		{
			return _fg->get_width();
		}
	}
	else
	{
		return _bg->get_width();
	}
}
int Icon::get_height()
{
	if (_fFgOnly == true)
	{
		if (is_frameImg(_fg))
		{
			return _fg->get_frameHeight();
		}
		else
		{
			return _fg->get_height();
		}
	}
	else
	{
		return _bg->get_height();
	}
}
POINT Icon::get_center()
{
	if (_fFgOnly == true)
	{
		return _fg->get_center();
	}
	else
	{
		return _bg->get_center();
	}
}

void Icon::set_text_toIcon(string str, int size, COLORREF color)
{
	POINT pos;
	switch (_type)
	{
	case ICON::ICN_STR:
	case ICON::ICN_AGL:
	case ICON::ICN_STM:
		_icon_txt = MyText(MYTEXT::TXT_TITLE, str, RGB(254, 254, 254));
		pos.x = (LONG)(_fg->get_rect().right + 10);
		pos.y = (LONG)(_fg->get_rect().top + 8);
		_icon_txt.set_pos(pos);
		_icon_txt.set_size(30);
		_fIconText = true;
		break;
	case ICON::ICN_FRIGER:
		_icon_txt = MyText(MYTEXT::TXT_DESCR, str, RGB(254, 239, 41));
		pos.x = (LONG)(_fg->get_rect().left - 6);
		pos.y = (LONG)(_fg->get_rect().bottom - 20);
		_icon_txt.set_pos(pos);
		_icon_txt.set_size(20);
		_fIconText = true;
		break;
	case ICON::ICN_HEALTH:
	case ICON::ICN_ENERGY:
	case ICON::ICN_MOOD:
	case ICON::ICN_FOOD:
		_icon_txt = MyText(MYTEXT::TXT_DESCR, str, RGB(82, 249, 97));
		pos.x = (LONG)(_fg->get_rect().right);
		pos.y = (LONG)(_fg->get_rect().top + 3);
		_icon_txt.set_pos(pos);
		_icon_txt.set_size(20);
		_fIconText = true;
		break;
	}
}
