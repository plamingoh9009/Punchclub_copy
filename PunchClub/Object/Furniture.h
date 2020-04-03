#pragma once
#include "Facility.h"
class Furniture: public Facility
{
protected:
	virtual HRESULT init_objs();
	virtual void update_objImgFrame(Image * img);
	virtual void change_player_run(bool isStart = true);
	virtual void runType_case_toUpdate();
	void make_collisions();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	Furniture();
	Furniture(MYOBJECT::TYPE type);
	Furniture(MYOBJECT::TYPE type, MYOBJECT::RUN_TYPE run_type);
	~Furniture();
public:
	void set_furniture_center(POINT center);
	void set_furniture_pos(POINT pos);
};

