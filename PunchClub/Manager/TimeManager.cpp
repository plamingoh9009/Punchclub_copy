#include "stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init()
{
	_timer = new Timer;
	_timer->init();
	return S_OK;
}
void TimeManager::release()
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
		_timer = nullptr;
	}
}
void TimeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}
void TimeManager::render(HDC hdc)
{
	char str[256];

	string strFrame;
	//배경모드
	SetBkMode(hdc, TRANSPARENT);
	//색상
	SetTextColor(hdc, RGB(255, 0, 255));
	//디버그 모드라면
#ifdef _DEBUG

	if (_timer != nullptr)
	{
		//FPS
		sprintf_s(str, "FPS :  %d", _timer->get_frameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		//전체 경과 시간
		sprintf_s(str, "worldTime :  %f", _timer->get_worldTime());
		TextOut(hdc, 0, 20, str, strlen(str));
		//한프레임당 경과시간
		sprintf_s(str, "ElapsedTime :  %f", _timer->get_elapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}

#else
	if (_timer != nullptr)
	{
		//FPS
		sprintf_s(str, "FPS :  %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif // _DEBUG

}
TimeManager::TimeManager()
{
}
TimeManager::~TimeManager()
{
}
