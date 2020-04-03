#pragma once
#include "Base/GameNode.h"
#include "uiEnum.h"
class MyText: public GameNode
{
private:
	typedef vector<string> Strings;
private:
	MYTEXT::TYPE _type;
	string _text = "";
	string _font;
	int _size;
	POINT _pos;
	COLORREF _color;
	// 최대 출력할 글자 수를 정한다.
	// 나머지 글자는 아래로 내려서 렌더한다.
	Strings _texts;
	int _maxChars = 0;
protected:
	int find_space_near_maxChar(string text, int maxChar);
	void draw_texts(HDC hdc);
	void delete_texts();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
public:
	MyText(); 
	MyText(MYTEXT::TYPE type, string text, COLORREF color = NULL);
	~MyText();
public:
	void set_pos(POINT pos) { _pos = pos; }
	POINT get_pos() { return _pos; }
	void set_size(int size) { _size = size; }
	void set_font(string font) { _font = font; }
	void set_maxChars(int maxChars);
	vector<string> get_texts() { return _texts; }
	string get_text() { return _text; }
	void set_text(string str) { _text = str; }
};

