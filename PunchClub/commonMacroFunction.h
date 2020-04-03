#pragma once
inline POINT PointMake(int x, int y)
{
	POINT pt = { x ,y };
	return pt;
}
//���׸��� �Լ�
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}
inline void LineMake(HDC hdc, POINT p1, POINT p2)
{
	MoveToEx(hdc, p1.x, p1.y, NULL);
	LineTo(hdc, p2.x, p2.y);
}
inline void ColorLine(HDC hdc, int x1, int y1, int x2, int y2, int width = 1, COLORREF color = RGB(1, 1, 1))
{
	// HPEN �����ϴ� �κ�
	HPEN newPen = CreatePen(PS_SOLID, width, color);
	HPEN oldPen = (HPEN)SelectObject(hdc, newPen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	// �귯�� �����ϴ� �κ�
	SelectObject(hdc, oldPen);
	DeleteObject(newPen);
}
// RECT ���� center ��������
inline POINT CenterFromRect(RECT rc)
{
	POINT result;
	int width = (int)(rc.right - rc.left);
	int height = (int)(rc.bottom - rc.top);
	result.x = rc.left + width;
	result.y = rc.top + height;
	return result;
}
//RECT�����(�»�� ����)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y, x + width, y + height };
	return rc;
}
//RECT�����(�߽������� ����)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}
inline RECT RectMakeCenter(POINT center, int width, int height)
{
	RECT rc = RectMakeCenter(center.x, center.y, width, height);
	return rc;
}
inline RECT RectMakeRightBottom(int x, int y, int width, int height)
{
	RECT rc = { x - width, y - height, x, y };
	return rc;
}
//�簢�� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void RectangleMake(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
//�簢�� �׸���(�߽���)
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
//�簢�� �׸���(Color)
inline void ColorRect(HDC hdc, RECT rc, COLORREF color = RGB(254,254,254))
{
	// �귯�� �����ϴ� �κ�
	HBRUSH rectBrush = (HBRUSH)CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, rectBrush);
	// �簢�� �׸��� �Լ�
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	// �귯�� �����ϴ� �κ�
	SelectObject(hdc, oldBrush);
	DeleteObject(rectBrush);
}
// �� �簢�� �׸��� (Color)
inline void ColorFrameRect(HDC hdc, RECT rc, COLORREF color = RGB(254, 254, 254))
{
	// �귯�� �����ϴ� �κ�
	HBRUSH rectBrush = (HBRUSH)CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, rectBrush);
	// �簢�� �׸��� �Լ�
	FrameRect(hdc, &rc, rectBrush);
	// �귯�� �����ϴ� �κ�
	SelectObject(hdc, oldBrush);
	DeleteObject(rectBrush);
}
//���׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//���׸���(�߽���)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));

}
// ���� ��Ʈ �ٲ㼭 ����ϴ� �Լ�
inline void FontTextOut(HDC hdc, int drawX, int drawY, LPCSTR str,
	LPCSTR fontName, int fontSize = 20, COLORREF color = RGB(0, 0, 0))
{
	// ������ ������ �ٲٴ� �κ�
	COLORREF oldTextColor = SetTextColor(hdc, color);
	// ������ ��Ʈ�� �ٲٴ� �κ�
	HFONT font = CreateFont(fontSize, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, fontName);
	HFONT oldFont = (HFONT)SelectObject(hdc, font);
	// ����� �����ϰ� �ٲٴ� �κ�
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, drawX, drawY, str, strlen(str));
	// �ٲ�� ���� ������ �����ϴ� �κ�
	SetTextColor(hdc, oldTextColor);
	// ��Ʈ�� �����ϴ� �κ�
	SelectObject(hdc, oldFont);
	DeleteObject(font);
}
// �׸��ڸ� �߰����ִ� �Լ�
inline void FontTextShadow(HDC hdc, int drawX, int drawY, LPCSTR str,
	LPCSTR fontName, int fontSize = 20, COLORREF color = RGB(0, 0, 0))
{
	int shadow_move = (int)(fontSize * 0.1);
	FontTextOut(hdc, drawX + shadow_move, drawY + shadow_move, str, fontName, fontSize, RGB(1, 1, 1));
	FontTextOut(hdc, drawX, drawY, str, fontName, fontSize, color);
}

// �����ϰ� �����ϴ� �Լ�
template<class MYCLASS>
inline HRESULT Release(MYCLASS myC)
{
	if (myC != nullptr)
	{
		myC->release();
		myC = nullptr;
		return S_OK;
	}
	else
	{
		delete(myC);
		return S_OK;
	}
	return E_FAIL;
}
template<class MYCLASS>
inline HRESULT Draw(MYCLASS myC)
{
	if (myC != nullptr)
	{
		myC->render();
		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}
template<class MYCLASS>
inline HRESULT Draw(MYCLASS myC, HDC hdc)
{
	if (myC != nullptr)
	{
		myC->render(hdc);
		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}