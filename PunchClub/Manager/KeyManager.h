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
	//�ѹ��� ������
	bool is_onceKeyDown(int key);
	//�����ٰ� �³�
	bool is_onceKeyUp(int key);
	//������ �ֳ�
	bool is_stayKeyDown(int key);
	//���Ű��
	bool is_toggleKey(int key);
public:
	KeyManager();
	~KeyManager();
};

