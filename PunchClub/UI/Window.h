#pragma once
#include "UI.h"
#include "Button.h"
#include "Slot.h"
#include "Gauge.h"

struct LeagueSlot
{
	Image * back = nullptr;
	Image * lock_back = nullptr;
	Image * lock = nullptr;
	RECT back_rc;
	RECT lock_back_rc;
	RECT lock_rc;
	POINT slot_center;
	// fore
	Image * icon = nullptr;
	Image * icon_back = nullptr;
	RECT icon_rc;
	RECT icon_back_rc;
	POINT icon_center;
	// Text
	string title;
	string desc_type[2];
	string desc_rank[2];
	string desc_next[2];
	POINT title_pos;
	POINT desc_pos;
	// ��ư
	Image * btn_show;
	Image * btn_start;
	Image * icon_show;
	RECT btn_show_rc;
	RECT icon_show_rc;
	POINT btn_show_center;
};
class Window: public UI
{
private:
	typedef vector<Slot *> Slots;
private:
	WINDOW::TYPE _type;
	Image * _bg;
	Image * _locked_back;
	// Button
	Button * _red_button;
	Button * _btn_window;
	// fg ����
	Image * _fg;
	MyText _fg_title;
	MyText _fg_descr;
	// Inside Window
	Image * _inside;
	// ���� ��ġ
	POINT _line_pos;
	POINT _line_pos_ver;
	// ���� ������ ���� ��Ʈ
	RECT _league_slots_rc;
	LeagueSlot _league_slot[3];
	// ���� �����츦 ���� ����
	Image * _bus;
	MyText _bus_distance_str;
	int _bus_distance = 10;
	Button * _btn_bus;
	Button * _btn_walk;
	// ������ �����츦 ���� ����
	Image * _work_jhammer;
	Image * _work_dust;
	Button * _btn_build;
	Gauge * _gauge;
	bool _fClose = false;
	bool _fOpen = false;
	// ���� ����
	Slots _slots;
	// ���� �����쿡�� ����� bool ����
	bool _fOpenBus = false;
	bool _fClickButton = false;
protected:
	HRESULT init_window_bg(WINDOW::TYPE type);
	void delete_window_bg();
	void draw_window_bg();
	// �κ��丮 â�� �ʱ�ȭ�Ѵ�.
	void init_inventory();
	void draw_inventory();
	void delete_inventory();
	void update_friger();
	// ����â�� �ʱ�ȭ�Ѵ�.
	void init_league();
	void draw_league();
	void update_league();
	void delete_league();
	// ���� ���� â�� �ʱ�ȭ�Ѵ�.
	void init_league_slots();
	void draw_league_slots();
	void delete_league_slots();
	// ���� �����츦 �ʱ�ȭ�Ѵ�.
	HRESULT init_bus_fg();
	void draw_bus();
	void delete_bus();
	void update_bus();
	// bus_str: {string; Data} for description Text
	// bus_dist: {int; Data} that destination how far from player
	string map_bus_distance(string bus_str, int bus_dist);
	// ������ �����츦 �ʱ�ȭ�Ѵ�.
	HRESULT init_build_fg();
	void draw_build();
	void delete_build();
	void update_build();
	// ���� â�� �ʱ�ȭ�Ѵ�.
	HRESULT init_setting_fg();
	void draw_setting();
	void delete_setting();
	void update_setting();
	// ���� ������ �ʱ�ȭ�Ѵ�.
	HRESULT init_slots();
	void delete_slots();
	void draw_slots();
	void update_shop();
public:
	void close_window(bool fResetClick = true);
public:
	virtual HRESULT init(WINDOW::TYPE type);
	virtual void release();
	virtual void update();
	virtual void render();
public:
	Window();
	~Window();
	bool is_closeWindow() { return _fClose; }
	void reset_closeWindow() { _fClose = false; }
	bool is_openWindow() { return _fOpen; }
	void set_openWindow(bool fResult) { _fOpen = fResult; }
	bool is_openBus() { return _fOpenBus; }
	void set_fOpenBus(bool fResult) { _fOpenBus = fResult; }
	bool is_clickButton() { return _fClickButton; }
	void set_fClickButton(bool fResult) { _fClickButton = fResult; }
};

