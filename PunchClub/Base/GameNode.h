#pragma once
#include "Base/Image.h"
enum SCENE_TYPE
{
	SCENE_EMPTY,
	SCENE_TITLE,
	SCENE_HOME,
	SCENE_HUD_MAP,
	SCENE_GYM,
	SCENE_SHOP,
	SCENE_SKILLTREE,
	SCENE_LEAGUE_WAIT,
	SCENE_LEAGUE_FIGHT,
	SCENE_BUILD,
	SCENE_BACK
};
class GameNode
{
private:
	static Image * _backBuffer;		//백버퍼
	HDC _hdc;
	bool _fManagerInit;
protected:
	string _imgPath = "Images/";	// 게임에서 사용할 이미지 경로
	static SCENE_TYPE _scene_forChange;
	
	static bool _fClick;		// 클릭 처리를 위한 변수
	static bool _fRClick;
	static bool _fDebug;		// 디버그 모드를 위한 변수
protected:
	bool is_frameImg(Image * img);
protected:
	void update_checkDebugMode();
	void update_checkClicked();
	// type: SCENE_TYPE to change you want
	void change_currentScene(SCENE_TYPE type);
	// append: "Images/[append]"
	void set_imgPath(string append = "");
public:
	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void render();
	// 메인 프로시저
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
public:
	GameNode();
	~GameNode();
public:
	static Image* set_backBuffer();
	//백버퍼 얻어오기
	Image* get_backBuffer() { return _backBuffer; }
	//추가(메모리 DC)
	HDC get_memDC() { return _backBuffer->get_memDC(); }
	//추가 HDC얻기
	HDC get_hdc() { return _hdc; }
};

