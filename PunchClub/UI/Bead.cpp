#include "stdafx.h"
#include "Bead.h"
#include "HudBack.h"
#include "Object/Player.h"
HRESULT Bead::init()
{
	set_imgPath("UI/Bead/");
	init_bead();
	return S_OK;
}
void Bead::release()
{
	Release(_img);
}
void Bead::update()
{
	// Move to destination
	if (_fDestination)
	{
		if (_fDelete) {}
		else
		{
			move_toDestination();
			change_speed();
		}
	}
	else
	{
		// Move to next
		if (_fNextPos)
		{
			move_toNext();
			change_speed(false);
		}
		else
		{
			setup_bead_destination();
		}
	}
}
void Bead::render()
{
	Draw(_img, get_memDC());
}
Bead::Bead()
{
}
Bead::Bead(BEAD::TYPE type, bool isReverse)
{
	_type = type;
	_fReverse = isReverse;
}
Bead::~Bead()
{
}
void Bead::set_position(int idx)
{
	_positionIdx = idx;
	setup_bead_position();
}
HRESULT Bead::init_bead()
{
	string path;
	switch (_type)
	{
		// Stat
	case BEAD::BD_HEALTH:
		_img = new Image;
		path = _imgPath + "drop_health.bmp";
		_img->init(path.c_str(), (int)(15 * 1.6), (int)(15 * 1.6));
		break;
	case BEAD::BD_FOOD:
		_img = new Image;
		path = _imgPath + "drop_food.bmp";
		_img->init(path.c_str(), (int)(15 * 1.6), (int)(15 * 1.6));
		break;
	case BEAD::BD_MOOD:
		_img = new Image;
		path = _imgPath + "drop_mood.bmp";
		_img->init(path.c_str(), (int)(15 * 1.6), (int)(15 * 1.6));
		break;
	case BEAD::BD_ENERGY:
		_img = new Image;
		path = _imgPath + "drop_energy.bmp";
		_img->init(path.c_str(), (int)(15 * 1.6), (int)(15 * 1.6));
		break;
		// Fight
	case BEAD::BD_STR:
		_img = new Image;
		path = _imgPath + "drop_str.bmp";
		_img->init(path.c_str(), (int)(15 * GAME_MULTIPLE), (int)(15 * GAME_MULTIPLE));
		break;
	case BEAD::BD_AGL:
		_img = new Image;
		path = _imgPath + "drop_agl.bmp";
		_img->init(path.c_str(), (int)(15 * GAME_MULTIPLE), (int)(15 * GAME_MULTIPLE));
		break;
	case BEAD::BD_STM:
		_img = new Image;
		path = _imgPath + "drop_stm.bmp";
		_img->init(path.c_str(), (int)(15 * GAME_MULTIPLE), (int)(15 * GAME_MULTIPLE));
		break;
	}
	return S_OK;
}
void Bead::setup_bead_position()
{
	POINT center;
	int blank = 40;
	if (_fReverse)
	{
		switch (_type)
		{
		case BEAD::BD_HEALTH:
			center = HUDBACK->get_health_center();
			break;
		case BEAD::BD_FOOD:
			center = HUDBACK->get_food_center();
			break;
		case BEAD::BD_MOOD:
			center = HUDBACK->get_mood_center();
			break;
		case BEAD::BD_ENERGY:
			center = HUDBACK->get_energy_center();
			break;
		}
		_img->set_center(center);
		// Next
		_nextPos.x = center.x;
		_nextPos.y = center.y + 100;
	}
	else
	{
		switch (_positionIdx)
		{
		case 1:
			center.x = (LONG)(PLAYER->get_playerCenter().x);
			break;
		case 2:
			center.x = (LONG)(PLAYER->get_playerCenter().x - blank);
			break;
		case 3:
			center.x = (LONG)(PLAYER->get_playerCenter().x + blank);
			break;
		case 4:
			center.x = (LONG)(PLAYER->get_playerCenter().x + (blank * 2));
			break;
		}
		switch (_type)
		{
		case BEAD::BD_HEALTH:
		case BEAD::BD_FOOD:
		case BEAD::BD_MOOD:
		case BEAD::BD_ENERGY:
			center.y = (LONG)(PLAYER->get_playerCenter().y - 50);
			break;
		case BEAD::BD_STR:
		case BEAD::BD_AGL:
		case BEAD::BD_STM:
			center.y = (LONG)(PLAYER->get_playerCenter().y - 90);
			break;
		}
		_img->set_center(center);
		// Next
		_nextPos.x = center.x;
		_nextPos.y = center.y - 100;
	}
	if (_nextPos.x && (100 < _nextPos.y))
	{
		// Distance
		_distance_next = abs(
			UTIL::getDistance(
			(float)(_img->get_center().x),
				(float)(_img->get_center().y),
				(float)(_nextPos.x),
				(float)(_nextPos.y)
			)
		);
	}
	else
	{
		_fNextPos = false;
		_fDestination = true;
		setup_bead_destination();
	}
}
void Bead::setup_bead_destination()
{
	if (_fReverse)
	{
		_dest = PLAYER->get_playerCenter();
	}
	else
	{
		switch (_type)
		{
		case BEAD::BD_HEALTH:
			_dest = HUDBACK->get_health_center();
			break;
		case BEAD::BD_FOOD:
			_dest = HUDBACK->get_food_center();
			break;
		case BEAD::BD_MOOD:
			_dest = HUDBACK->get_mood_center();
			break;
		case BEAD::BD_ENERGY:
			_dest = HUDBACK->get_energy_center();
			break;
		case BEAD::BD_STR:
			_dest = HUDBACK->get_str_center();
			break;
		case BEAD::BD_AGL:
			_dest = HUDBACK->get_agl_center();
			break;
		case BEAD::BD_STM:
			_dest = HUDBACK->get_stm_center();
			break;
		}
	}
	// Distance
	_distance_dest = abs(
		UTIL::getDistance(
		(float)(_img->get_center().x),
			(float)(_img->get_center().y),
			(float)(_dest.x),
			(float)(_dest.y)
		)
	);

	_fNextPos = false;
	_fDestination = true;
}
void Bead::move_toNext()
{
	POINT center;
	if (_nextPos.x && _nextPos.y)
	{
		center = _img->get_center();
		if (is_positionOK(center.y, _nextPos.y)) {}
		else
		{
			if (center.y > _nextPos.y)
			{
				center.y -= _speed;
			}
			else if (center.y < _nextPos.y)
			{
				center.y += _speed;
			}
		}
		// OK Á¶°Ç
		if (is_positionOK(center, _nextPos))
		{
			_fNextPos = false;
		}
		_img->set_center(center);
	}
}
void Bead::move_toDestination()
{
	POINT center;
	if (_dest.x && _dest.y)
	{
		center = _img->get_center();
		// Move Y
		if (is_positionOK(center.y, _dest.y)) {}
		else
		{
			if (center.y > _dest.y)
			{
				center.y -= _speed;
			}
			else if (center.y < _dest.y)
			{
				center.y += _speed;
			}
		}
		// Move X
		if (is_positionOK(center.x, _dest.x)) {}
		else
		{
			if (center.x > _dest.x)
			{
				center.x -= _speed;
			}
			else if (center.x < _dest.x)
			{
				center.x += _speed;
			}
		}
		_img->set_center(center);
	}
	// Destination OK
	if (is_positionOK(center, _dest))
	{
		_fDelete = true;
	}
}
void Bead::change_speed(bool isDestination)
{
	float distance;
	double target;
	if (isDestination)
	{
		distance = abs(
			UTIL::getDistance(
			(float)(_img->get_center().x),
				(float)(_img->get_center().y),
				(float)(_dest.x),
				(float)(_dest.y)
			)
		);
		target = _distance_dest * (4 / 6.0);
		if (_speed < 4 && distance < target)
		{
			_speed *= 2;
		}
	}
	else
	{
		distance = abs(
			UTIL::getDistance(
			(float)(_img->get_center().x),
				(float)(_img->get_center().y),
				(float)(_nextPos.x),
				(float)(_nextPos.y)
			)
		);
		target = _distance_next * (4 / 6.0);
		if (_speed < 2 && distance < target)
		{
			_speed *= 2;
		}
	}
}

bool Bead::is_positionOK(POINT currentPos, POINT targetPos)
{
	bool xOK, yOK;
	xOK = is_positionOK(currentPos.x, targetPos.x);
	yOK = is_positionOK(currentPos.y, targetPos.y);

	if (xOK && yOK)
	{
		return true;
	}
	return false;
}
bool Bead::is_positionOK(LONG currentPos, LONG targetPos)
{
	LONG ok_band = 5;
	int temp;
	temp = (currentPos < targetPos ?
		(int)(targetPos - currentPos) : (int)(currentPos - targetPos));
	if (temp <= ok_band)
	{
		return true;
	}
	return false;
}
