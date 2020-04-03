#pragma once
#include "Base/SingletonBase.h"
#include <bitset>
#define KEYMAX 256
class KeyManager: public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
public:
	HRESULT init();
	void release();
	//한번만 눌렀냐
	bool is_onceKeyDown(int key);
	//눌렀다가 뗏냐
	bool is_onceKeyUp(int key);
	//누르고 있냐
	bool is_stayKeyDown(int key);
	//토글키냐
	bool is_toggleKey(int key);
public:
	KeyManager();
	~KeyManager();
};

