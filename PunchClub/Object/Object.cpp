#include "stdafx.h"
#include "Object.h"

bool Object::_fObjMove = true;
bool Object::_fObjClickLock = false;
HRESULT Object::init()
{
	return S_OK;
}
void Object::release()
{
}
void Object::update()
{
}
void Object::render()
{
}
Object::Object()
{
}
Object::~Object()
{
}
