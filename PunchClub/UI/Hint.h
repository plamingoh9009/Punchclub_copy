#pragma once
#include "UI.h"
class Hint: public UI
{
private:
	HINT::TYPE _type;
	Image * _bg = nullptr;
	string _bg_fileName;
	Image * _corner_under = nullptr;
	Image * _corner_under_shdw = nullptr;
	Image * _corner_upper = nullptr;
	MyText _title;
	MyText _descr;
	double _time = 0;
	bool _fPositionOK = false;
	bool _fCorner_upper = false;
protected:
	HRESULT init_imgs();
	void delete_imgs();
	void draw_imgs();
	void draw_texts();
	void update_imgPos();
	void update_textPos();
	void resize_bg();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	Hint(HINT::TYPE type);
	~Hint();
public:
	void set_center(POINT center);
	void set_texts(string title, string descr);
	//bool is_positionOK() { return _fPositionOK; }
};

