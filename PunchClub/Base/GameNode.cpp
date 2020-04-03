#include "stdafx.h"
#include "Base/GameNode.h"

Image* GameNode::_backBuffer = NULL;
// 인게임 공통 데이터
SCENE_TYPE GameNode::_scene_forChange = SCENE_EMPTY;
bool GameNode::_fClick = false;
bool GameNode::_fRClick = false;
bool GameNode::_fDebug = false;
bool GameNode::is_frameImg(Image * img)
{
	if (img->get_maxFrameX() != 0 || img->get_maxFrameY() != 0)
	{
		return true;
	}
	return false;
}
void GameNode::update_checkDebugMode()
{
	if (KEYMANAGER->is_toggleKey(VK_TAB) == true) { _fDebug = true; }
	else if (KEYMANAGER->is_toggleKey(VK_TAB) == false) { _fDebug = false; }
}
void GameNode::update_checkClicked()
{
	if (KEYMANAGER->is_onceKeyUp(VK_LBUTTON))
	{
		_fClick = true;
	}
	else 
	{ 
		_fClick = false; 
	}
	if (KEYMANAGER->is_onceKeyUp(VK_RBUTTON))
	{
		_fRClick = true;
	}
	else
	{
		_fRClick = false;
	}
}
void GameNode::change_currentScene(SCENE_TYPE type)
{
	switch (type)
	{
	case SCENE_HOME:
		SCENEMANAGER->changeScene("Home");
		break;
	case SCENE_HUD_MAP:
		SCENEMANAGER->changeScene("HudMap");
		break;
	case SCENE_GYM:
		SCENEMANAGER->changeScene("Gym");
		break;
	case SCENE_SHOP:
		SCENEMANAGER->changeScene("Shop");
		break;
	case SCENE_SKILLTREE:
		SCENEMANAGER->changeScene("SkillTree");
		break;
	case SCENE_LEAGUE_WAIT:
		SCENEMANAGER->changeScene("LeagueWait");
		break;
	case SCENE_LEAGUE_FIGHT:
		SCENEMANAGER->changeScene("LeagueFight");
		break;
	case SCENE_TITLE:
		SCENEMANAGER->changeScene("Title");
		break;
	}
}
void GameNode::set_imgPath(string append)
{
	_imgPath = "Images/" + append;
}

HRESULT GameNode::init()
{
	_hdc = GetDC(m_hWnd);
	_fManagerInit = false;
	return S_OK;
}
HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(m_hWnd);
	_fManagerInit = managerInit;

	if (managerInit)
	{
		set_backBuffer();
		//SetTimer(m_hWnd, 1, 10, NULL);
		// 여기서 매니저 초기화
		TIMEMANAGER->init();
		SCENEMANAGER->init();
		KEYMANAGER->init();
	}

	return S_OK;
}
void GameNode::release()
{
	if (_fManagerInit)
	{
		//타이머 해제
		//KillTimer(m_hWnd, 1);
		// 여기서 매니저 해제. 1) release_singleton(), 2) 클래스 release()
		TIMEMANAGER->release_singleton();
		SCENEMANAGER->release_singleton();
		KEYMANAGER->release_singleton();

		TIMEMANAGER->release();
		SCENEMANAGER->release();
		KEYMANAGER->release();
	}
	ReleaseDC(m_hWnd, _hdc);
}
void GameNode::update() {}
void GameNode::render(HDC hdc) {}
void GameNode::render() {}
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			//PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
GameNode::GameNode() {}
GameNode::~GameNode() {}
Image * GameNode::set_backBuffer()
{
	_backBuffer = new Image;
	_backBuffer->init(WINSIZEX, WINSIZEY);

	return _backBuffer;
}