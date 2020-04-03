#pragma once
#include "Gauge.h"
#include "Icons/Icon.h"
#include "Base/SingletonBase.h"
class HudBack: public UI, public SingletonBase<HudBack>
{
private:
	typedef vector<Gauge *> Gauges;
private:
	Image * _hud_back;
	// Gauges
	Gauges _hud_gauges;
	Gauge * _health;
	Gauge * _food;
	Gauge * _mood;
	Gauge * _energy;
	
	Gauge * _str;
	Gauge * _agl;
	Gauge * _stm;
	// Icons
	Icon * _icon_str;
	Icon * _icon_agl;
	Icon * _icon_stm;
	// Money
	MyText _money;
	MyText _skillPoint;
protected:
	string Stat(double stat);
	double Exp(double stat);
protected:
	HRESULT init_gauges();
	void delete_gauges();
	void draw_gauges();
	void update_gauges();
	HRESULT init_icons();
	void delete_icons();
	void draw_icons();
	virtual void update();
public:
	void update_datas_fromPlayer();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void render();
public:
	HudBack();
	~HudBack();
public:
	inline POINT get_health_center() { return _health->get_center(); }
	inline POINT get_food_center() { return _food->get_center(); }
	inline POINT get_mood_center() { return _mood->get_center(); }
	inline POINT get_energy_center() { return _energy->get_center(); }
	inline POINT get_str_center() { return _str->get_center(); }
	inline POINT get_agl_center() { return _agl->get_center(); }
	inline POINT get_stm_center() { return _stm->get_center(); }
};
#define HUDBACK	HudBack::get_singleton()
