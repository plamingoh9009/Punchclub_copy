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
	Furniture * _kitchentable;	// �ֹ� ���̺�
	Furniture * _friger;		// �����
	Furniture * _stand;			// ���ĵ�
	Furniture * _sofa;			// ����
	Furniture * _aquarium;		// ����
	Furniture * _tv;			// TV
	Furniture * _fan;			// õ�� ��ǳ��
	Furniture * _table;			// ��Ź
	Furniture * _bookshelf;		// å��
	Furniture * _clock;			// �ð�
	Furniture * _phone;			// ��ȭ��
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

