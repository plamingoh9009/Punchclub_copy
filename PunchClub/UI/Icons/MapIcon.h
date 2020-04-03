#pragma once
#include "UI/Hint.h"
class MapIcon: public UI
{
private:
	MAPICON::TYPE _type = MAPICON::ICN_EMPTY;
	SCENE_TYPE _sceneType = SCENE_EMPTY;
	Image * _icon_off;
	Image * _icon_on;
	// Hint 변수
	Hint * _hint;
	// 건물 아이콘에 사용할 변수
	bool _fIcon = false;	// 아이콘 On, Off에 사용하는 변수
	bool _fOpenBus = false;
	bool _fOpenWindow = false;
protected:
	// Player Icon
	void update_playerIcon();
	bool is_player_atHere();
	HRESULT init_icon();
	void draw_icon();
	void delete_icon();
	void update_icon();
	// Hint
	HRESULT init_hint();
	void update_hint();
public:
	void draw_hint();
public:
	virtual HRESULT init(MAPICON::TYPE type);
	virtual void release();
	virtual void update();
	virtual void render();
public:
	MapIcon();
	~MapIcon();
public:
	HRESULT set_center(POINT center);
	POINT get_center() { return _icon_off->get_center(); }
	int get_width() { return _icon_off->get_width(); }
	int get_height() { return _icon_off->get_height(); }
	bool is_playerIcon_moveOK() { return _fplayerIcon_move; }
	MAPICON::TYPE get_current_location() { return _playerIcon_location; }
	void set_current_location(MAPICON::TYPE location) { _playerIcon_location = location; }
	// 버스 윈도우 컨트롤
	bool get_fOpenBus() { return _fOpenBus; }
	void set_fOpenBus(bool fResult) { _fOpenBus = fResult; }
	bool is_openWindow() { return _fOpenWindow; }
	void set_fOpenWindow(bool fResult) { _fOpenWindow = fResult; }
};