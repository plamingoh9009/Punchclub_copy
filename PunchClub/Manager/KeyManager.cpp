#include "stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init()
{
	//Ű�� ���� �������� ���� ���·� �ʱ�ȭ����
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
	//GetAsyncKeyState���� Ű�� ���¸� �˾ƿ��� �༮
	//Ű�� ������������ ���������� ȣ��
	//0x8000 �������� �������� ���� ȣ��������� ��������
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

	//GetKeyState :���� Ű�� ��ۻ���
	//0x0001������ �������� �ְ� ȣ��������� �ȴ��� ����

	if (GetKeyState(key) & 0x0001)return true;
	return false;
}
KeyManager::KeyManager()
{
}
KeyManager::~KeyManager()
{
}
