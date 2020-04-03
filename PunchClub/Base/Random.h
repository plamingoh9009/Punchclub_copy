#pragma once
#include "Base/SingletonBase.h"
class Random : public SingletonBase<Random>
{
public:
	Random()
	{
		srand(GetTickCount());
	}
	~Random() {}

	//������ ���ڹ��������� ������ �޾ƿ´�.0~������ ����
	inline int get_int(int num)
	{
		return rand() % num;
	}
	inline int get_fromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};
