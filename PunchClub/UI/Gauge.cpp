#include "stdafx.h"
#include "Gauge.h"
#include "Object/Player.h"

void Gauge::init_fight_stat()
{
	string path;
	switch (_statType)
	{
	case GAUGE::ST_STR:
		_fg = new Image;
		path = _imgPath + "bar_str.bmp";
		_fg->init(path.c_str(), (int)(53 * GAME_MULTIPLE), (int)(14 * GAME_MULTIPLE));
		break;
	case GAUGE::ST_AGL:
		_fg = new Image;
		path = _imgPath + "bar_agl.bmp";
		_fg->init(path.c_str(), (int)(53 * GAME_MULTIPLE), (int)(14 * GAME_MULTIPLE));
		break;
	case GAUGE::ST_STM:
		_fg = new Image;
		path = _imgPath + "bar_stm.bmp";
		_fg->init(path.c_str(), (int)(53 * GAME_MULTIPLE), (int)(14 * GAME_MULTIPLE));
		break;
	}
}

void Gauge::action()
{
	switch (_type)
	{
	case GAUGE::GG_WORK:
		PLAYER->add_money(50);
		PLAYER->action_init();
		break;
	case GAUGE::GG_STAT_SMALL:
		PLAYER->action_init();
		break;
	}
}
void Gauge::run_gauge(bool isSyncValue)
{
	// 일정 시간을 주고, 게이지를 올린다.
	_time += TIMEMANAGER->get_elapsedTime();
	if (1.0f <= _time)
	{
		if (_currentGauge < _maxGauge)
		{
			_currentGauge += _gaugeSpeed;
		}
		// 게이지 value로 width 값을 정의한다.
		sync_gauge_fromValue();

		_time = 0;	// 시간을 초기화
	}

	if (_currentGauge >= _maxGauge)
	{
		_currentGauge = 0;
		action();
	}//if: 현 게이지가 꽉차면 되돌린다.
}

double Gauge::limit_value(double value, bool fZeroSet)
{
	if (value < 0)
	{
		return 0.0;
	}
	else if (value > 1000)
	{
		switch (_type)
		{
		case GAUGE::GG_WORK:
			PLAYER->init_workGauge();
			return 0.0;
		default:
			if (fZeroSet)
			{
				return 0.0;
			}
			else
			{
				return 1000.0;
			}
		}
	}
	return value;
}

void Gauge::sync_gauge_fromValue()
{
	sync_gauge_fromValue(_currentGauge);
}
POINT Gauge::correct_fg_position(POINT position)
{
	POINT result = position;
	switch (_type)
	{
	case GAUGE::GG_PLAYER_HP:
		result.x = (LONG)(position.x);
		result.y = (LONG)(position.y - 14);
		break;
	case GAUGE::GG_ENEMY_HP:
		result.x = (LONG)(position.x);
		result.y = (LONG)(position.y - 14);
		break;
	}
	return result;
}
void Gauge::sync_gauge_fromValue(double value)
{
	double temp;
	double gaugeWidth;

	if (value > _maxGauge)
	{
		action();
	}
	value = limit_value(value);
	gaugeWidth = _fg->get_width();
	temp = (value / _maxGauge) * gaugeWidth;
	// 출력할 게이지 값을 정의
	_currentWidth = temp;
}

void Gauge::set_text_toGauge(double currentValue, double maxValue, GAUGE::TYPE type)
{
	POINT center;
	int size;
	string text = "";
	text.append(to_string((int)(currentValue)));
	text.append(" / ");
	text.append(to_string((int)(maxValue)));
	switch (type)
	{
	case GAUGE::GG_PLAYER_HP:
	case GAUGE::GG_ENEMY_HP:
		_text = MyText(MYTEXT::TXT_TITLE, text, RGB(222, 255, 0));
		size = 28;
		center.x = _fg->get_center().x - (text.length() * 6);
		center.y = _fg->get_center().y - (LONG)(size * 0.3);
		_text.set_pos(center);
		_text.set_size(size);
		break;
	case GAUGE::GG_ENERGY:
		_text = MyText(MYTEXT::TXT_TITLE, text, RGB(255, 198, 0));
		size = 20;
		center.x = _fg->get_center().x - (text.length() * 5);
		center.y = _fg->get_center().y - (LONG)(size * 0.3);
		_text.set_pos(center);
		_text.set_size(size);
		break;
	}
	_fText = true;
}

HRESULT Gauge::init()
{
	set_imgPath("UI/Gauge/");
	string path;
	switch (_type)
	{
	case GAUGE::GG_WORK:
		_bg = new Image;
		path = _imgPath + "work_pb_back.bmp";
		_bg->init(path.c_str(), (int)(223 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
		_fg = new Image;
		path = _imgPath + "work_pb.bmp";
		_fg->init(path.c_str(), (int)(223 * GAME_MULTIPLE), (int)(20 * GAME_MULTIPLE));
		sync_gauge_fromValue(PLAYER->get_stat().workGauge);
		PLAYER->set_playerAction(MYOBJECT::WORK_PLAYER);
		break;
	case GAUGE::GG_STAT_SMALL:
		_fg = new Image;
		path = _imgPath + "hud_bar_small.bmp";
		_fg->init(path.c_str(), (int)(51 * GAME_MULTIPLE), (int)(6 * GAME_MULTIPLE));
		break;
	case GAUGE::GG_PLAYER_HP:
		_bg = new Image;
		path = _imgPath + "Player_bars.bmp";
		_bg->init(path.c_str(), (int)(253 * GAME_MULTIPLE), (int)(33 * GAME_MULTIPLE));
		_fg = new Image;
		path = _imgPath + "hp_bar.bmp";
		_fg->init(path.c_str(), (int)(251 * GAME_MULTIPLE), (int)(18 * GAME_MULTIPLE));
		break;
	case GAUGE::GG_ENEMY_HP:
		_bg = new Image;
		path = _imgPath + "Enemy_bars.bmp";
		_bg->init(path.c_str(), (int)(253 * GAME_MULTIPLE), (int)(33 * GAME_MULTIPLE));
		_fg = new Image;
		path = _imgPath + "hp_bar.bmp";
		_fg->init(path.c_str(), (int)(251 * GAME_MULTIPLE), (int)(18 * GAME_MULTIPLE));
		break;
	case GAUGE::GG_ENERGY:
		_fg = new Image;
		path = _imgPath + "energy_bar.bmp";
		_fg->init(path.c_str(), (int)(139 * GAME_MULTIPLE), (int)(9 * GAME_MULTIPLE));
		break;
	case GAUGE::GG_STAT_FIGHT:
		init_fight_stat();
		break;
	}
	return S_OK;
}
void Gauge::release()
{
	Release(_bg);
	Release(_fg);
}
void Gauge::update()
{
	switch (_type)
	{
	case GAUGE::GG_WORK:
		sync_gauge_fromValue(PLAYER->get_stat().workGauge);
		break;
	default:
		sync_gauge_fromValue();
		break;
	}
}
void Gauge::render()
{
	Draw(_bg, get_memDC());
	if (_fg != nullptr)
	{
		_fg->render(get_memDC(), _fg->get_rect().left, _fg->get_rect().top,
			0, 0, (int)(_currentWidth), _fg->get_height());
	}
	if (_fText)
	{
		_text.render(get_memDC());
	}
}
Gauge::Gauge(GAUGE::TYPE type)
{
	_type = type;
}
Gauge::Gauge(GAUGE::STAT statType)
{
	_type = GAUGE::GG_STAT_FIGHT;
	_statType = statType;
}
Gauge::~Gauge()
{
}

void Gauge::set_center(POINT center)
{
	if (_bg != nullptr)
	{
		_bg->set_center(center);
		center = correct_fg_position(center);
	}
	if (_fg != nullptr)
	{
		_fg->set_center(center);
	}
}

void Gauge::set_pos(POINT pos)
{
	if (_bg != nullptr)
	{
		_bg->set_pos(pos);
		pos = correct_fg_position(pos);
	}
	if (_fg != nullptr)
	{
		_fg->set_pos(pos);
	}
}
POINT Gauge::get_center()
{
	if (_fg != nullptr)
	{
		return _fg->get_center();
	}
	return POINT();
}

void Gauge::start()
{
	_fGaugeRun = true;
	PLAYER->action_start();
}

void Gauge::pause()
{
	_fGaugeRun = false;
	PLAYER->action_pause();
}
