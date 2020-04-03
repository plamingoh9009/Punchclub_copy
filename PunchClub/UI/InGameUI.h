#pragma once
#include "Base/GameNode.h"
#include "Base/SingletonBase.h"
// UI
#include "Cursor.h"
#include "Icons/Icon.h"
#include "HudBack.h"
#include "Button.h"
#include "Bead.h"
// 클릭했을 때
#include "Window.h"
// 싸울 때
#include "FightGauge.h"
enum UI_TYPE
{
	UI_NONE,
	UI_LEAGUE,
};
class InGameUI: public GameNode, public SingletonBase<InGameUI>
{
private:
	// 오브젝트에 값을 넣기 위해서 필요하다
	Object * _obj;
	typedef vector<Bead *> Beads;
private:
	// Cursor
	Cursor * _cursor = nullptr;
	// Icons
	Icon * _icn_hud_map = nullptr;
	Icon * _icn_league = nullptr;
	Icon * _icn_skilltree = nullptr;

	HudBack * _hud_back;
	// 빨간 버튼은 렌더를 할지, 말지 정할 수 있다.
	Button * _red_button;
	bool _fRedButton;
	// Windows
	Window * _window_league;	// 리그 창
	Window * _ingame_wnd = nullptr;
	bool _fIngame_wnd = false;
	bool _fClose_ingame_wnd = false;
	Window * _setting_wnd;
	// 리그에서 쓰는 게이지 클래스
	FightGauge * _gauge;
	// Stat Beads
	Beads _beads;
	// 현재 UI에 무엇을 띄울 것인지 기준
	UI_TYPE _type = UI_NONE;
	WINDOW::TYPE _wndType = WINDOW::WND_NONE;
protected:
	void run_red_button();
	// Icons
	HRESULT init_icons();
	void delete_icons();
	void draw_icons();
	void update_icons();
	// Beads
	void erase_beads();
	void draw_beads();
	void update_beads();
	// League
	void update_league();
	// 게이지
	void init_gauges();
	void draw_gauges();
	void update_gauges();
	void delete_gauges();
	// 상점
	void update_ingame_wnd();
	void draw_ingame_wnd();
	// 커서
	HRESULT init_cursor();
public:
	virtual HRESULT init();
	virtual HRESULT init(UI_TYPE type);
	virtual void release();
	virtual void update();
	virtual void render();
public:
	InGameUI();
	~InGameUI();
public : 
	void CloseWnd();
	void draw_cursor();
	void update_cursor();
public:
	void set_fRedButton(bool fResult) { _fRedButton = fResult; }
	void set_windowType(WINDOW::TYPE type);
	void set_fIngame_wnd(bool fResult) { _fIngame_wnd = fResult; }
	bool is_close_ingame_wnd() { return _fClose_ingame_wnd; }
	bool is_open_setting_wnd();
	void reset_ingame_wnd();
};
#define INGAME_UI	InGameUI::get_singleton()