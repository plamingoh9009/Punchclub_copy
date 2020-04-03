#pragma once
#include "UI.h"
class Cursor: public UI
{
private:
	Image * _arrow;
	Image * _wait;
	bool _fWait = false;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	Cursor();
	~Cursor();
public:
	void set_fWait(bool fResult) { _fWait = fResult; }
};

