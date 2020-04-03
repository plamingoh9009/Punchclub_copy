#pragma once
#include "Object.h"
class Unit: public Object
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
public:
	Unit();
	~Unit();
};

