#pragma once
#include "Scene.h"
#include "Object/Furniture.h"
class HomeScene: public Scene
{
private:
	typedef vector<Furniture*> Furnitures;
private:
	Image * _bg;
	Image * _ceil;
	// Furnitures
	Furnitures _objs;
	Furniture * _kitchentable;	// 주방 테이블
	Furniture * _friger;		// 냉장고
	Furniture * _stand;			// 스탠드
	Furniture * _sofa;			// 소파
	Furniture * _aquarium;		// 수조
	Furniture * _tv;			// TV
	Furniture * _fan;			// 천장 선풍기
	Furniture * _table;			// 식탁
	Furniture * _bookshelf;		// 책장
	Furniture * _clock;			// 시계
	Furniture * _phone;			// 전화기
protected:
	void init_friger();
	void init_sofa();
	void init_tv();
	void init_aquarium();
	void init_fan();
	void init_clock();
	void init_kitchentable();
	void init_stand();
	void init_table();
	void init_bookshelf();
	void init_phone();
protected:
	void init_furnitures();
	void draw_furnitures();
	void delete_furnitures();
	void update_furnitures();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	HomeScene();
	~HomeScene();
};

