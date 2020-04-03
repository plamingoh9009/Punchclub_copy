#pragma once
#include "Scene.h"
#include "UI/InGameUI.h"
class GymScene: public Scene
{
private:
	typedef vector<Object *> Facilitys;
private:
	Image * _bg;
	Image * _door;
	Facilitys _objs;
	Facility * _treadmill_left;
	Facility * _treadmill_mid;
	Facility * _treadmill_right;
	Facility * _barbell;
	Facility * _yungchun;
	Facility * _tire;
	Facility * _benchPress;
	Facility * _punchbug;
protected:
	HRESULT init_objs();
	void delete_objs();
	void draw_objs();
	void update_objs();
	HRESULT init_treadmills();
	void delete_treadmills();
	HRESULT init_barbells();
	void delete_barbells();
	HRESULT init_yungchun();
	void delete_yungchun();
	HRESULT init_tire();
	void delete_tire();
	HRESULT init_benchPress();
	void delete_benchPress();
	HRESULT init_punchbugs();
	void delete_punchbugs();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	GymScene();
	~GymScene();
};

