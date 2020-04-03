#include "stdafx.h"
#include "PrefightSkillSet.h"

void PrefightSkillSet::init_slots()
{
	POINT center;
	double blank = 0;
	for (int i = 1; i <= 6; i++)
	{
		_slots[i - 1] = new Slot(SLOT::SLT_ACTIVE_SKILL);
		_slots[i - 1]->init();
		
		center.x = (LONG)(_bg_rc.left + _slots[i-1]->get_width() * 0.575 * i + blank);
		center.y = (LONG)(_bg_rc.top + _slots[i-1]->get_height() * 0.5 + 2);
		_slots[i - 1]->set_slotCenter(center);
		blank += _slots[i - 1]->get_width() * 0.525;
	}
}
void PrefightSkillSet::draw_slots()
{
	for (int i = 0; i < 6; i++)
	{
		if (_slots[i] != nullptr)
		{
			_slots[i]->render();
		}
	}
}
void PrefightSkillSet::delete_slots()
{
	for (int i = 0; i < 6; i++)
	{
		if (_slots[0] != nullptr)
		{
			_slots[0]->release();
			_slots[0] = nullptr;
		}
	}
}

HRESULT PrefightSkillSet::init()
{
	set_imgPath("UI/Skill/");
	string path = _imgPath + "active_skill_back.bmp";
	_bg = new Image;
	_bg->init(path.c_str(), (int)(240 * GAME_MULTIPLE), (int)(38 * GAME_MULTIPLE));
	_text = "액티브 스킬:";
	return S_OK;
}
void PrefightSkillSet::release()
{
	_bg->release();
	_bg = nullptr;
	if (_slots[0] != nullptr) { delete_slots(); }
}
void PrefightSkillSet::update()
{
}
void PrefightSkillSet::render()
{
	_bg->render(get_memDC(), _bg_rc.left, _bg_rc.top);
	FontTextOut(get_memDC(), _text_pos.x, _text_pos.y, _text.c_str(),
		"휴먼편지체", 25, RGB(254, 254, 254));
	if (_slots[0] != nullptr) { draw_slots(); }
}
PrefightSkillSet::PrefightSkillSet()
{
}
PrefightSkillSet::~PrefightSkillSet()
{
}

void PrefightSkillSet::set_center(POINT center)
{
	_bg_rc = RectMakeCenter(center.x, center.y, _bg->get_width(), _bg->get_height());
	_text_pos.x = (LONG)(_bg_rc.left + 5);
	_text_pos.y = (LONG)(_bg_rc.top - 25);
	init_slots();
}
