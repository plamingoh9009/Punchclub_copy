#pragma once
#include "UI.h"
class Gauge: public UI
{
private:
	GAUGE::TYPE _type;
	GAUGE::STAT _statType;
	Image * _bg = nullptr;
	Image * _fg = nullptr;
	MyText _text;
	double _maxGauge = 1000;
	double _currentGauge = 1000;
	double _currentWidth = 0;
	double _gaugeSpeed = 0;
	float _time = 0;
	bool _fGaugeRun = false;
	bool _fText = false;
protected:
	void init_fight_stat();
protected:
	void action();
	void run_gauge(bool isSyncValue = false);
	double limit_value(double value, bool fZeroSet = false);
	void sync_gauge_fromValue();
	POINT correct_fg_position(POINT position);
public:
	void sync_gauge_fromValue(double value);
	void set_text_toGauge(double currentValue, double maxValue, GAUGE::TYPE type);
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	// fExtraValue: 외부의 값으로 게이지를 띄워야 하는 경우 true, default는 false
	Gauge(GAUGE::TYPE type);
	Gauge(GAUGE::STAT statType);
	~Gauge();
public:
	void set_center(POINT center);
	void set_pos(POINT pos);
	POINT get_center();
	int get_width() { return _fg->get_width(); }
	int get_height() { return _fg->get_height(); }
	GAUGE::TYPE get_type() { return _type; }
	void start();
	void pause();
};