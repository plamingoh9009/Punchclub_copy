#include "stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init()
{
	//키가 전부 눌려있지 않은 상태로 초기화하자
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp.set(i, false);
		_keyDown.set(i, false);
	}
	return S_OK;
}
void KeyManager::release()
{
}

bool KeyManager::is_onceKeyDown(int key)
{
	//GetAsyncKeyState현재 키의 상태를 알아오는 녀석
	//키가 눌려졌을때나 떨어졌을때 호출
	//0x8000 이전에는 누른적이 없고 호출시점에서 눌린상태
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		_keyDown.set(key, false);
	}
	return false;
}
bool KeyManager::is_onceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp.set(key, true);
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp.set(key, false);
			return true;
		}
	}
	return false;
}
bool KeyManager::is_stayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)return true;
	return false;
}
bool KeyManager::is_toggleKey(int key)
{

	//GetKeyState :현재 키의 토글상태
	//0x0001이전에 누른적이 있고 호출시점에서 안눌린 상태

	if (GetKeyState(key) & 0x0001)return true;
	return false;
}
KeyManager::KeyManager()
{
}
KeyManager::~KeyManager()
{
}
