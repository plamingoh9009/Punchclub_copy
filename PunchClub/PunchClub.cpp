// PunchClub.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "PunchClub.h"

// 전역변수
HINSTANCE m_hInstance;
HWND m_hWnd;
POINT m_ptMouse = { 0,0 };
MainGame mg;	// 메인게임

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	m_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	//윈도우 클래스에서 사용하고자 하는 여분의 메모리양을 바이트 단위로 지정
	wndClass.cbWndExtra = 0;	//cbClsExtra 유사하되 개별 윈도우에서 사용하고자 하는 여분의 메모리양을 지정
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 작업영역에 칠할 배경 브러시를 지정
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//클래스 커서를 지정
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//타이틀바의 좌상단에 보여줄 아이콘과 윈도우가 최소화 되었을대 보여줄 아이콘을 지정
	wndClass.hInstance = hInstance;	//윈도우 클래스를 등록한 응용프로그램의 인스턴스 핸들
	wndClass.lpfnWndProc = (WNDPROC)WndProc;	//메세지를 처리하는 함수를 지정(윈도우 프로시져)
	wndClass.lpszClassName = WINNAME;	//등록하고자 하는 윈도우 클래스 이름
	wndClass.lpszMenuName = NULL;			//클래스로부터 만들어진 윈도우가 사용할 메뉴를 지정
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//윈도우 클래스의 스타일을 지정

	RegisterClass(&wndClass);

	m_hWnd = CreateWindow(
		WINNAME,		//윈도우 클래스의 이름
		WINNAME,		//윈도우 타이틀바 이름
		WS_OVERLAPPEDWINDOW,//윈도우 스타일
		WINSTARTX,				//윈도우 화면의 x좌표
		WINSTARTY,				//윈도우 화면의 y좌표
		WINSIZEX,				//윈도우 화면의 가로크기
		WINSIZEY,				//윈도우 화면의 세로크기
		NULL,				//부모윈도우
		(HMENU)NULL,		//메뉴핸들
		hInstance,			//인스턴스 지정
		NULL);				//사용하지 않음
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(m_hWnd, nCmdShow);

	// 메인게임 클래스가 초기화가 실패하면 종료 시켜라
	if (FAILED(mg.init())) { return 0; }

	MSG message;

	// 메인루프
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			//초당 60프레임으로 업데이트 시켜라
			TIMEMANAGER->update(60.0f);
			mg.update();
			mg.render();
		}
	}

	//메시지 루프를 다 돌았다면 해제
	mg.release();
	return message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//=================================================================
//	## 윈도우 크기 조정 ## (클라이언트 영역의 사이즈를 정확히 잡아준다)
//=================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WINSTYLE, false);

	//위 RECT 정보로 윈도우 사이즈 셋팅
	SetWindowPos(m_hWnd, NULL, x, y, 
		(rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}