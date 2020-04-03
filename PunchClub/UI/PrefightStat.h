#pragma once
#include "UI.h"
class PrefightStat: public UI
{
private:
	Image * _bg;
	RECT _bg_rc;
	// ÅØ½ºÆ®
	string _name;
	POINT _name_pos;
	bool _fName_left;
	// ½ºÅÈ
	string _str, _stm, _agl;
	Image * _str_icon;
	Image * _agl_icon;
	Image * _stm_icon;
	RECT _str_rc, _agl_rc, _stm_rc;
	bool _fStat = false;
protected:
	void draw_name();
	void init_icons();
	void draw_icons();
	void delete_icons();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	PrefightStat();
	~PrefightStat();
public:
	// center: Window's center for draw
	// name: Unit name
	// name_left: Unit name position for draw [left|right]
	void set_window(POINT center, string name, bool name_left = true);
	void set_stat(int str, int stm, int agl);
	EnemyStat get_enemyStat() { return _enemy->get_stat(); }
};

