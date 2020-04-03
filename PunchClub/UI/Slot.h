#pragma once
#include "UI.h"
#include "Button.h"
#include "Icons/Icon.h"

class Slot: public UI
{
private:
	typedef vector<Icon*> Icons;
private:
	SLOT::TYPE _type;
	SLOT::ITEM _itemType = SLOT::ITM_EMPTY;
	Image * _bg = nullptr;
	Image * _fg = nullptr;
	Image * _fg_back = nullptr;
	MyText _title;
	MyText _descr;
	Button * _btn = nullptr;
	Icon * _icon = nullptr;
	Icons _icons;
protected:
	void init_bg(SLOT::TYPE type);
	void draw_bg();
	void delete_bg();
	void init_item();
	void draw_item();
	void setup_fg_center();
	void setup_text_pos();
	void setup_button();
	void setup_icon();
	HRESULT init_icons(int health, int energy, int mood, int food);
	void delete_icons();
	void draw_icons();
public:
	// type: {SLOT::TYPE; enum}
	// center: Center for draw slot
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	Slot(SLOT::TYPE type);
	Slot(SLOT::TYPE type, SLOT::ITEM itemType);
	~Slot();
public:
	void set_slotCenter(POINT center);
	void set_slotPos(POINT pos);
	int get_width() { return _bg->get_width(); }
	int get_height() { return _bg->get_height(); }
	POINT get_center() { return _bg->get_center(); }
	SLOT::ITEM get_itemType() { return _itemType; }
	bool is_clickButton() { return _btn->is_clickButton(); }
	void set_clickButton_false() { _btn->set_fClickButton(false); }
};