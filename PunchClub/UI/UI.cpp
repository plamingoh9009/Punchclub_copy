#include "stdafx.h"
#include "UI.h"

bool UI::_fplayerIcon_move = false;
POINT UI::_playerIcon_center = {0, 0};
MAPICON::TYPE UI::_playerIcon_location = MAPICON::ICN_EMPTY;
Enemy * UI::_enemy = new Enemy();
HRESULT UI::init()
{
	return S_OK;
}
void UI::release()
{
}
void UI::update()
{
}
void UI::render()
{
}
UI::UI()
{
	_obj = new Object;
}
UI::~UI()
{
	_obj->release();
	_obj = nullptr;
}
