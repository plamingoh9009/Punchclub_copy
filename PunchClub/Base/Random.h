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

	//지정한 숫자범위내에서 난수를 받아온다.0~지정한 숫자
	inline int get_int(int num)
	{
		return rand() % num;
	}
	inline int get_fromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};
