#pragma once
#include "UI.h"
class Bead: public UI
{
private:
	BEAD::TYPE _type;
	Image * _img;
	POINT _dest;
	POINT _nextPos;
	int _positionIdx;
	// ������ �ӵ��� �ٲٴ� ����
	float _distance_dest;
	float _distance_next;
	int _speed = 1;				// ���� �ӵ�
	// ������ �����̱� ���� ����
	bool _fReverse;
	bool _fNextPos = true;
	bool _fDestination = false;
	bool _fDelete = false;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	Bead();
	Bead(BEAD::TYPE type, bool isReverse = false);
	~Bead();
protected:
	HRESULT init_bead();
	void setup_bead_position();
	void setup_bead_destination();
	void move_toNext();
	void move_toDestination();
	void change_speed(bool isDestination = true);
	bool is_positionOK(POINT currentPos, POINT targetPos);
	bool is_positionOK(LONG currentPos, LONG targetPos);
public:
	void set_position(int idx);
	inline bool is_deleteOK() { return _fDelete; }
};

