#pragma once
#include "Base/Timer.h"
#include "Base/SingletonBase.h"
class TimeManager: public SingletonBase<TimeManager>
{
private:
	Timer * _timer;
public:
	HRESULT init();
	void release();
	void update(float lock = 0.0f);
	void render(HDC hdc);
public:
	TimeManager();
	~TimeManager();
public:
	float get_elapsedTime()const { return _timer->get_elapsedTime(); }
	float get_worldTime()const { return _timer->get_worldTime(); }
};

