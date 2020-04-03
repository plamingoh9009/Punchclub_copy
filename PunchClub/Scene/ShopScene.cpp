#include "stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init()
{
	add_currentScene_toList(SCENE_SHOP);
	set_imgPath("Shop/");
	string path;
	POINT center;
	_bg = new Image;
	path = _imgPath + "shop_bg.bmp";
	_bg->init(path.c_str(), (int)(683 * GAME_MULTIPLE), (int)(384 * GAME_MULTIPLE));
	// Shop NPC
	_shop = new Npc(NPC::NPC_SHOP);
	_shop->init();
	// 플레이어 초기화
	center.x = (LONG)(WIN_HALF_W - WIN_HALF_W * 0.45);
	center.y = (LONG)(WIN_HALF_H - 20);
	PLAYER->init();
	PLAYER->set_playerCenter(center);
	INGAME_UI->init();
	INGAME_UI->set_windowType(WINDOW::WND_SHOP);
	INGAME_UI->set_fRedButton(false);
	return S_OK;
}

void ShopScene::release()
{
	Release(_bg);
	Release(_shop);
}

void ShopScene::update()
{
	update_scene();
	_shop->update();
	if (_shop->is_openShop() == true)
	{
		INGAME_UI->set_fIngame_wnd(true);
	}
	else
	{
		PLAYER->update();
	}
	INGAME_UI->update();
	change_scene();
}

void ShopScene::render()
{
	Draw(_bg, get_memDC());
	Draw(_shop);
	PLAYER->render();
	INGAME_UI->render();
}
ShopScene::ShopScene()
{
}
ShopScene::~ShopScene()
{
}
