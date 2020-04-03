#pragma once
#include "Scene.h"
#include "UI/Icons/MapIcon.h"
#include "UI/Window.h"
class HudMapScene: public Scene
{
private:
	typedef vector<MapIcon *> MapIcons;
private:
	Image * _bg;
	// 아이콘
	MapIcons _icons;
	MapIcon * _player;
	MapIcon * _home;
	MapIcon * _shop;
	MapIcon * _gym;
	MapIcon * _build;
	// 윈도우
	Window * _bus_wnd;
	Window * _build_wnd;
protected:
	void update_player_pos();
	HRESULT init_background();
	void draw_background();
	void delete_background();
	HRESULT init_map_icons();
	void draw_map_icons();
	// 힌트는 맵 아이콘보다 나중에 렌더한다.
	void draw_hints();
	void update_map_icons();
	void delete_map_icons();
	// 모든 윈도우를 닫는다.
	void close_windowsAll(bool fResetClick);
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	HudMapScene();
	~HudMapScene();
};

