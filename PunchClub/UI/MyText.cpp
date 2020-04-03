#include "stdafx.h"
#include "MyText.h"

int MyText::find_space_near_maxChar(string text, int maxChars)
{
	int result = 0;
	int index = 0;
	int compare_result, compare_index;
	string myText = text;
	string subText;
	while (true)
	{
		index = myText.find(" ", index);
		if (index == -1) { break; }
		else
		{
			subText = myText.substr(index, -1);
			compare_result = abs(maxChars - result);
			compare_index = abs(maxChars - index);
			if (compare_index <= compare_result)
			{
				result = index;
			}
			index++;
		}
	}
	return result;
}

void MyText::draw_texts(HDC hdc)
{
	auto iter = _texts.begin();
	POINT myPos = _pos;
	switch (_type)
	{
	case MYTEXT::TXT_TITLE:
		for (; iter != _texts.end(); iter++)
		{
			FontTextShadow(hdc, myPos.x, myPos.y, (*iter).c_str(), _font.c_str(), _size, _color);
			myPos.y = (LONG)(myPos.y + _size);
		}
		break;
	case MYTEXT::TXT_DESCR:
		for (; iter != _texts.end(); iter++)
		{
			FontTextOut(hdc, myPos.x, myPos.y, (*iter).c_str(), _font.c_str(), _size, _color);
			myPos.y = (LONG)(myPos.y + _size);
		}
		break;
	}
}
void MyText::delete_texts()
{
	auto iter = _texts.begin();
	for (; iter != _texts.end();)
	{
		iter = _texts.erase(iter);
	}
	swap(Strings(), _texts);
}

HRESULT MyText::init()
{
	return E_NOTIMPL;
}
void MyText::release()
{
	delete_texts();
}
void MyText::update()
{
}
void MyText::render(HDC hdc)
{
	if (_text != "" && _maxChars == 0)
	{
		switch (_type)
		{
		case MYTEXT::TXT_TITLE:
			FontTextShadow(hdc, _pos.x, _pos.y, _text.c_str(), _font.c_str(), _size, _color);
			break;
		case MYTEXT::TXT_DESCR:
			FontTextOut(hdc, _pos.x, _pos.y, _text.c_str(), _font.c_str(), _size, _color);
			break;
		}
	}
	else if (_text != "" && _maxChars != 0)
	{
		draw_texts(hdc);
	}
}
MyText::MyText()
{
}
MyText::MyText(MYTEXT::TYPE type, string text, COLORREF color)
{
	_type = type;
	switch (type)
	{
	case MYTEXT::TXT_TITLE:
		_size = 35;
		_font = "ÈÞ¸Õ¸ÅÁ÷Ã¼";
		if (color == NULL)
		{
			_color = RGB(254, 254, 254);
		}
		break;
	case MYTEXT::TXT_DESCR:
		_size = 25;
		_font = "ÈÞ¸ÕÆíÁöÃ¼";
		if (color == NULL)
		{
			_color = RGB(1, 1, 1);
		}
		break;
	default:
		_size = 20;
		_font = "±Ã¼­Ã¼";
		if (color == NULL)
		{
			_color = RGB(1, 1, 1);
		}
		break;
	}
	// default Color
	if (color != NULL)
	{
		_color = color;
	}
	// Text
	_text = text;
}
MyText::~MyText()
{
}
void MyText::set_maxChars(int maxChars)
{
	string myText = _text;
	string subText;
	int index;
	while ((int)(myText.length()) > maxChars)
	{
		index = find_space_near_maxChar(myText, maxChars);
		subText = myText.substr(0, index+1);
		myText = myText.substr(index+1, -1);
		_texts.push_back(subText);
	}
	_texts.push_back(myText);
	_maxChars = maxChars;
}
