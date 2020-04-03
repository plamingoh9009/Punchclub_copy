#pragma once
#include "Object.h"
class Facility: public Object
{
private:
	typedef vector<Collision *> Collisions;
protected:
	MYOBJECT::TYPE _type = MYOBJECT::OBJ_EMPTY;
	MYOBJECT::RUN_TYPE _run_type = MYOBJECT::RUN_EMPTY;
	Image * _img_off = nullptr;
	Image * _img_off_fg = nullptr;
	Image * _img_on = nullptr;
	Image * _img_shadow = nullptr;
	Image * _img_runback = nullptr;
	Image * _img_runback_shdw = nullptr;
	// Collisions
	Collisions _collisions;

	Image * _img_run = nullptr;
	Image * _img_run_shadow = nullptr;
	bool _fImgOn = false;
	bool _fImgRun = false;
	bool _fImgRunBack = false;
	bool _fImgRunOnly = false;
	bool _fImgOffOnly = false;
	bool _fSelect = false;
	bool _fRun = false;
protected:
	void start_player_action(MYOBJECT::RUN_TYPE runType);
	void stop_player_action(bool isStopUnforced = true);
	void stop_running();
	void run_imgFrame();
	void push_player_fromObj(Collision objCollision);
	// Collision
	virtual void make_collisions();
	void collision_withPlayer(Collision objCollision);
protected:
	virtual HRESULT init_objs();
	void delete_objs();
	void draw_objs();
	void update_objs();
	void draw_img_run();
	void draw_img_off();
	void draw_img_on();
	void draw_img_runback();
	void set_center(POINT center);
	void set_pos(POINT pos);
	virtual void update_objImgFrame(Image * img);
	virtual void runType_case_toUpdate();
	virtual void change_player_run(bool isStart = true);
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	Facility();
	Facility(MYOBJECT::TYPE type);
	Facility(MYOBJECT::TYPE type, MYOBJECT::RUN_TYPE run_type);
	~Facility();
public:
	void set_facility_center(POINT center);
	void set_facility_pos(POINT pos);
	void set_img_off_fg_pos(POINT pos);
	void set_img_run_pos(POINT pos);
	int get_width();
	int get_height();
	POINT get_center() { return _img_off->get_center(); }
	RECT get_rect();
	bool is_run() { return _fRun; }
};

