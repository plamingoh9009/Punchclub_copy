#pragma once
#include "Slot.h"
class PrefightSkillSet: public UI
{
private:
	Image * _bg;
	RECT _bg_rc;
	string _text;
	POINT _text_pos;
	// ½½·Ô
	Slot * _slots[6];
protected:
	void init_slots();
	void draw_slots();
	void delete_slots();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	PrefightSkillSet();
	~PrefightSkillSet();
public:
	int get_width() { return _bg->get_width(); }
	int get_height() { return _bg->get_height(); }
	void set_center(POINT center);
};

