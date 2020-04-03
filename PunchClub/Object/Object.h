#pragma once
#include "Base/GameNode.h"
#include "objEnum.h"
class Object: public GameNode
{
protected:
	static bool _fObjMove;
	static bool _fObjClickLock;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
public:
	Object();
	~Object();
public:
	bool get_fObjMove() { return _fObjMove; }
	void set_fObjMove(bool fResult) { _fObjMove = fResult; }
};

