#pragma once
#include "Unit.h"
class Enemy: public Unit
{
private:
	EnemyStat _myStat;
protected:
	HRESULT init_stat();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
public:
	Enemy();
	Enemy(int enemyLevel);
	~Enemy();
public:
	EnemyStat get_stat() { return _myStat; }
};