#pragma once
#include "Unit.h"
#include "UI/Window.h"
class Npc: public Unit
{
private:
	NPC::TYPE _type;
	Image * _img_off;
	Image * _img_on;
	MyText _name;
	bool _fOpenShop = false;
	bool _fImgOn = false;
protected:
	HRESULT init_npc();
	void draw_npc();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
public:
	Npc(NPC::TYPE type);
	~Npc();
public:
	bool is_openShop() { return _fOpenShop; }
};

