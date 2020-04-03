#include "stdafx.h"
#include "Player.h"
#include "UI/InGameUI.h"
// ========================================
// ***		Idle 이미지 업데이트			***
// ========================================
void Player::update_idle_img(bool isResetPos)
{
	if (isResetPos)
	{
		// 이미지 변경하고
		change_idle_img();
		_player_idle[_idleIndex]->set_frameX(0);
		_player_idle[_idleIndex]->set_frameY(0);
		_player_idle_shdw[_idleIndex]->set_frameX(0);
		_player_idle_shdw[_idleIndex]->set_frameY(0);
		// 위치 다시 잡아주고
		_player_idle[_idleIndex]->set_center(_player_center);
		_player_idle_shdw[_idleIndex]->set_center(_player_center);
	}
	else
	{
		_player_idle[_idleIndex]->frameUpdate(false);
		_player_idle_shdw[_idleIndex]->frameUpdate(false);
		if (_player_idle[_idleIndex]->is_end_thirdSection())
		{
			change_idle_img();	// 이미지 변경하고

			// 위치 다시 잡아주고
			_player_idle[_idleIndex]->set_center(_player_center);
			_player_idle_shdw[_idleIndex]->set_center(_player_center);
		}
	}
}
void Player::change_idle_img()
{
	// 확률은		고개돌리기 오른쪽 2, 왼쪽 2 
	//			근육자랑 오른쪽 2, 왼쪽 2
	int result;
	result = RAND->get_fromIntTo(1, 100);
	int max;
	max = 8;
	if (0 < result && result <= (100 * 2 / max)) { _idleIndex = 0; }
	else if ((100 * 2 / max) < result && result <= (100 * 4 / max)) { _idleIndex = 1; }
	else if ((100 * 4 / max) < result && result <= (100 * 6 / max)) { _idleIndex = 2; }
	else { _idleIndex = 3; }
}
void Player::update_move_img()
{
	_player_move[_moveIndex]->frameUpdate(false);
	_player_move_shdw[_moveIndex]->frameUpdate(false);

	// 위치 다시 잡아주고
	_player_move[_moveIndex]->set_center(_player_center);
	_player_move_shdw[_moveIndex]->set_center(_player_center);
}
void Player::follow_icon_player()
{
	POINT center;
	center.x = (LONG)(_player_idle[_idleIndex]->get_rect().right + _hunger->get_width());
	center.y = (LONG)(_player_idle[+_idleIndex]->get_rect().top - _hunger->get_height());
	_hunger->set_center(center);
	_hunger->update();
}
void Player::move_player()
{
	Destination myDest;
	if (!_dest.empty())
	{
		myDest = _dest.front();
		// 4방향을 먼저 정한다.
		if (is_positionOK(_player_center.y, myDest.get_dest().y))
		{
			if (is_positionOK(_player_center.x, myDest.get_dest().x)) {}
			else
			{
				if (is_move_dest_left(_player_center.x, myDest.get_dest().x))
				{
					_player_center.x -= (LONG)(_speed);
					_moveIndex = 4;

				}// if: Move left
				else
				{
					_player_center.x += (LONG)(_speed);
					_moveIndex = 5;
				}// else: Move right
			}

		}// if: y 축이  맞다면 좌, 우로 움직인다.
		else
		{
			if (is_positionOK(_player_center.x, myDest.get_dest().x))
			{
				if (myDest.get_dest().y < _player_center.y)
				{
					_player_center.y -= (LONG)(_speed * 0.5);
					_moveIndex = 0;
				}
				else
				{
					_player_center.y += (LONG)(_speed * 0.5);
					_moveIndex = 3;
				}
			}// if: x 축이 맞다면 그냥 위, 아래로만 움직인다.
			else
			{
				if (myDest.get_dest().y < _player_center.y)
				{
					if (is_move_dest_left(_player_center.x, myDest.get_dest().x))
					{
						_player_center.y -= (LONG)(_speed * 0.5);
						_player_center.x -= (LONG)(_speed);
						_moveIndex = 0;
					}
					else
					{
						_player_center.y -= (LONG)(_speed * 0.5);
						_player_center.x += (LONG)(_speed);
						_moveIndex = 1;
					}
				}// if: Move up
				else
				{
					if (is_move_dest_left(_player_center.x, myDest.get_dest().x))
					{
						_player_center.y += (LONG)(_speed * 0.5);
						_player_center.x -= (LONG)(_speed);
						_moveIndex = 2;
					}
					else
					{
						_player_center.y += (LONG)(_speed * 0.5);
						_player_center.x += (LONG)(_speed);
						_moveIndex = 3;
					}
				}// else: Move down
			}

		}// else: y축이 맞지 않다면 위, 아래로 움직인다.

		// 여기서 콜리전 렉트를 다시 잡아준다.
		setup_collision_rect();
		
		if (is_positionOK(_player_center, myDest.get_dest()))
		{
			update_idle_img(true);
			_dest.pop();
		}
	}// if: 목적지가 잡혀 있으면 움직인다.
	else
	{
		_fIdle = true;
		_fMoving = false;
	}// else: 목적지가 없다면 Idle 상태가 된다 

	// 플레이어 위치를 다시 잡아준다.
	update_move_img();
}
void Player::setup_collision_rect()
{
	_collision.rc = RectMakeCenter(
		_player_center.x + _collision.correctionX,
		_player_center.y + _collision.correctionY,
		_collision.width, _collision.height);
}
void Player::init_player()
{
	string path;
	// Idle 01
	path = _imgPath + "player_idle_01.bmp";
	_player_idle[0] = new Image;
	_player_idle[0]->init(path.c_str(),
		(int)(114 * GAME_MULTIPLE), (int)(76 * GAME_MULTIPLE), 3, 1);
	_player_idle[0]->set_frameSection(3, 0, 0, 1.0f, 1, 2, 0.7f, 2, 2, 1.0f);
	path = _imgPath + "player_idle_shdw_01.bmp";
	_player_idle_shdw[0] = new Image;
	_player_idle_shdw[0]->init(path.c_str(),
		(int)(114 * GAME_MULTIPLE), (int)(76 * GAME_MULTIPLE), 3, 1);
	_player_idle_shdw[0]->set_frameSection(3, 0, 0, 1.0f, 1, 2, 0.7f, 2, 2, 1.0f);
	// Idle 02
	path = _imgPath + "player_idle_02.bmp";
	_player_idle[1] = new Image;
	_player_idle[1]->init(path.c_str(),
		(int)(114 * GAME_MULTIPLE), (int)(76 * GAME_MULTIPLE), 3, 1);
	_player_idle[1]->set_frameSection(3, 0, 0, 1.0f, 1, 2, 0.7f, 2, 2, 1.0f);
	path = _imgPath + "player_idle_shdw_02.bmp";
	_player_idle_shdw[1] = new Image;
	_player_idle_shdw[1]->init(path.c_str(),
		(int)(114 * GAME_MULTIPLE), (int)(76 * GAME_MULTIPLE), 3, 1);
	_player_idle_shdw[1]->set_frameSection(3, 0, 0, 1.0f, 1, 2, 0.7f, 2, 2, 1.0f);
	// Idle 03
	path = _imgPath + "player_idle_03.bmp";
	_player_idle[2] = new Image;
	_player_idle[2]->init(path.c_str(),
		(int)(250 * GAME_MULTIPLE), (int)(76 * GAME_MULTIPLE), 5, 1);
	_player_idle[2]->set_frameSection(3, 0, 0, 1.0f, 1, 4, 0.5f, 4, 4, 1.0f);
	path = _imgPath + "player_idle_shdw_03.bmp";
	_player_idle_shdw[2] = new Image;
	_player_idle_shdw[2]->init(path.c_str(),
		(int)(250 * GAME_MULTIPLE), (int)(76 * GAME_MULTIPLE), 5, 1);
	_player_idle_shdw[2]->set_frameSection(3, 0, 0, 1.0f, 1, 4, 0.5f, 4, 4, 1.0f);
	// Idle 04
	path = _imgPath + "player_idle_04.bmp";
	_player_idle[3] = new Image;
	_player_idle[3]->init(path.c_str(),
		(int)(250 * GAME_MULTIPLE), (int)(76 * GAME_MULTIPLE), 5, 1);
	_player_idle[3]->set_frameSection(3, 0, 0, 1.0f, 1, 4, 0.5f, 4, 4, 1.0f);
	path = _imgPath + "player_idle_shdw_04.bmp";
	_player_idle_shdw[3] = new Image;
	_player_idle_shdw[3]->init(path.c_str(),
		(int)(250 * GAME_MULTIPLE), (int)(76 * GAME_MULTIPLE), 5, 1);
	_player_idle_shdw[3]->set_frameSection(3, 0, 0, 1.0f, 1, 4, 0.5f, 4, 4, 1.0f);
	// Walking
	init_player_moves();
	// 초기 위치 잡기
	_player_center.x = (LONG)(WIN_HALF_W - WIN_HALF_W * 0.4);
	_player_center.y = (LONG)(WIN_HALF_H +
		_player_idle[_idleIndex]->get_height() * 0.5);
	_player_idle[_idleIndex]->set_center(_player_center);
	_player_idle_shdw[_idleIndex]->set_center(_player_center);
	// 위치 잡은 후 콜리전 렉트 만들기
	POINT center;
	_collision.width = (int)(40 * GAME_MULTIPLE);
	_collision.height = (int)(10 * GAME_MULTIPLE);
	_collision.correctionY = 50;
	center.x = (LONG)(_player_center.x);
	center.y = (LONG)(_player_center.y + _collision.correctionY);
	_collision.rc = RectMakeCenter(center.x, center.y,
		_collision.width, _collision.height);
}
HRESULT Player::init_player_moves()
{
	string path;
	// Up	0
	_player_move[0] = new Image;
	path = _imgPath + "player_walk_upL.bmp";
	_player_move[0]->init(path.c_str(),
		(int)(280 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 8, 1);
	_player_move[0]->set_frameSection(1, 0, 7, 0.3f);
	_player_move_shdw[0] = new Image;
	path = _imgPath + "player_walk_upL_shdw.bmp";
	_player_move_shdw[0]->init(path.c_str(),
		(int)(280 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 8, 1);
	_player_move_shdw[0]->set_frameSection(1, 0, 7, 0.3f);
	// Up	1
	_player_move[1] = new Image;
	path = _imgPath + "player_walk_upR.bmp";
	_player_move[1]->init(path.c_str(),
		(int)(280 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 8, 1);
	_player_move[1]->set_frameSection(1, 0, 7, 0.3f);
	_player_move_shdw[1] = new Image;
	path = _imgPath + "player_walk_upR_shdw.bmp";
	_player_move_shdw[1]->init(path.c_str(),
		(int)(280 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 8, 1);
	_player_move_shdw[1]->set_frameSection(1, 0, 7, 0.3f);
	// Down		2
	_player_move[2] = new Image;
	path = _imgPath + "player_downL.bmp";
	_player_move[2]->init(path.c_str(),
		(int)(272 * GAME_MULTIPLE), (int)(77 * GAME_MULTIPLE), 8, 1);
	_player_move[2]->set_frameSection(1, 0, 7, 0.3f);
	_player_move_shdw[2] = new Image;
	path = _imgPath + "player_downL_shdw.bmp";
	_player_move_shdw[2]->init(path.c_str(),
		(int)(272 * GAME_MULTIPLE), (int)(77 * GAME_MULTIPLE), 8, 1);
	_player_move_shdw[2]->set_frameSection(1, 0, 7, 0.3f);
	// Down		3
	_player_move[3] = new Image;
	path = _imgPath + "player_downR.bmp";
	_player_move[3]->init(path.c_str(),
		(int)(272 * GAME_MULTIPLE), (int)(77 * GAME_MULTIPLE), 8, 1);
	_player_move[3]->set_frameSection(1, 0, 7, 0.3f);
	_player_move_shdw[3] = new Image;
	path = _imgPath + "player_downR_shdw.bmp";
	_player_move_shdw[3]->init(path.c_str(),
		(int)(272 * GAME_MULTIPLE), (int)(77 * GAME_MULTIPLE), 8, 1);
	_player_move_shdw[3]->set_frameSection(1, 0, 7, 0.3f);
	// Left		4
	_player_move[4] = new Image;
	path = _imgPath + "player_walkL.bmp";
	_player_move[4]->init(path.c_str(),
		(int)(540 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 12, 1);
	_player_move[4]->set_frameSection(3, 0, 3, 0.1f, 4, 6, 0.1f, 7, 11, 0.1f);
	_player_move_shdw[4] = new Image;
	path = _imgPath + "player_walkL_shdw.bmp";
	_player_move_shdw[4]->init(path.c_str(),
		(int)(540 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 12, 1);
	_player_move_shdw[4]->set_frameSection(3, 0, 3, 0.1f, 4, 6, 0.1f, 7, 11, 0.1f);
	// Right	5
	_player_move[5] = new Image;
	path = _imgPath + "player_walkR.bmp";
	_player_move[5]->init(path.c_str(),
		(int)(540 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 12, 1);
	_player_move[5]->set_frameSection(3, 0, 3, 0.1f, 4, 6, 0.1f, 7, 11, 0.1f);
	_player_move_shdw[5] = new Image;
	path = _imgPath + "player_walkR_shdw.bmp";
	_player_move_shdw[5]->init(path.c_str(),
		(int)(540 * GAME_MULTIPLE), (int)(80 * GAME_MULTIPLE), 12, 1);
	_player_move_shdw[5]->set_frameSection(3, 0, 3, 0.1f, 4, 6, 0.1f, 7, 11, 0.1f);
	return S_OK;
}
void Player::draw_player()
{
	if (_fIdle)
	{
		_player_idle[_idleIndex]->frameRender(get_memDC());
		_player_idle_shdw[_idleIndex]->frameAlphaRender(get_memDC(), 128);
	}
	if (_fMoving)
	{
		_player_move[_moveIndex]->frameRender(get_memDC());
		_player_move_shdw[_moveIndex]->frameAlphaRender(get_memDC(), 128);
	}
}
void Player::update_player()
{
	POINT myDest;
	if (_fIdle) { update_idle_img(); }

	if (_fClick && _fObjMove)
	{
		if (m_ptMouse.y < (LONG)(WIN_HALF_H * 0.5)) {}
		else
		{
			if (_fObjMove)
			{
				myDest = m_ptMouse;
				myDest.y -= (LONG)(_player_idle[_idleIndex]->get_frameHeight() * 0.5);
				push_destination(myDest);
				_fMoving = true;
				_fIdle = false;
				INGAME_UI->reset_ingame_wnd();
			}
		}
	}
	else if (_fRClick && _fObjMove)
	{
		if (m_ptMouse.y < (LONG)(WIN_HALF_H * 0.5)) {}
		else
		{
			if (_fObjMove)
			{
				myDest = m_ptMouse;
				myDest.y -= (LONG)(_player_idle[_idleIndex]->get_frameHeight() * 0.5);
				push_destination(myDest, true);
				_fMoving = true;
				_fIdle = false;
				INGAME_UI->reset_ingame_wnd();
			}
		}
	}
	move_player();
}
void Player::delete_player()
{
	for (int i = 0; i < 6; i++)
	{
		Release(_player_move[i]);
		Release(_player_move_shdw[i]);
		if (4 <= i)
		{
			break;
		}
		else
		{
			Release(_player_idle[i]);
			Release(_player_idle_shdw[i]);
		}
	}
}
double Player::limit_stat(double stat, bool fZeroSet)
{
	if (stat < 0.0)
	{
		return 0.0;
	}
	else if (stat > 1000.0)
	{
		if (fZeroSet)
		{
			return 0.0;
		}
		else
		{
			return 1000.0;
		}
	}
	return stat;
}
bool Player::is_positionOK(LONG currentPos, LONG targetPos)
{
	LONG ok_band = 3;
	int temp;
	temp = (currentPos < targetPos ?
		(int)(targetPos - currentPos) : (int)(currentPos - targetPos));
	if (temp <= ok_band)
	{
		return true;
	}
	return false;
}
bool Player::is_positionOK(POINT currentPos, POINT targetPos)
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
bool Player::is_move_dest_left(LONG currentPos, LONG targetPos)
{
	if (targetPos < currentPos)
	{
		return true;
	}
	return false;
}
void Player::hide_player()
{
	switch (_actionType ^ MYOBJECT::RUN_PLAYER)
	{
	case MYOBJECT::SOFA_PLAYER:
	case MYOBJECT::TV_PLAYER:
		// Training
	case MYOBJECT::TRM_PLAYER:
	case MYOBJECT::BBL_PLAYER:
	case MYOBJECT::TIR_PLAYER:
	case MYOBJECT::BP_PLAYER:
	case MYOBJECT::PB_PLAYER:
	case MYOBJECT::YCN_PLAYER:
		_fVisible = false;
		break;
	}
}
// ========================================
// ***		스탯 구슬 함수					***
// ========================================
void Player::make_bead(BEAD::TYPE type, int plusCnt, bool isReverse)
{
	Bead * bead = new Bead(type, isReverse);
	bead->init();
	bead->set_position(plusCnt);
	_beads.push_back(bead);
}
// ========================================
// ***			플레이어 행동				***
// ========================================
void Player::action()
{
	if (_actionType != MYOBJECT::RUN_EMPTY)
	{
		if (_fAction)
		{
			hide_player();
			// 일정 시간을 주고, 행동을 한다.
			_time += TIMEMANAGER->get_elapsedTime();
			// #Time 2.6f
			if (2.6f <= _time)
			{
				switch (_actionType ^ MYOBJECT::RUN_PLAYER)
				{
				case MYOBJECT::WORK_PLAYER:
					Tired();
					_myStat.workGauge += 80;
					// 일하면 모든 상태가 전부 떨어지지만 스탯이 오른다.
					add_stat(10, -20, -10, -25);
					add_stat_forFight(PLAYER_SET::STR | PLAYER_SET::AGL | PLAYER_SET::STM);
					break;
				case MYOBJECT::SOFA_PLAYER:
					Tired();
					add_stat(10, -30, 2, 40);
					break;
				case MYOBJECT::TV_PLAYER:
					Tired();
					add_stat(10, -10, 30, 10);
					break;
					// Trainig
				case MYOBJECT::TRM_PLAYER:
					Tired();
					add_stat(PLAYER_SET::AS_FIGHT);
					add_stat_forFight(PLAYER_SET::STM);
					break;
				case MYOBJECT::BBL_PLAYER:
					Tired();
					add_stat(PLAYER_SET::AS_FIGHT);
					add_stat_forFight(PLAYER_SET::STR | PLAYER_SET::STM);
					break;
				case MYOBJECT::TIR_PLAYER:
					Tired();
					add_stat(PLAYER_SET::AS_FIGHT);
					add_stat_forFight(PLAYER_SET::STR | PLAYER_SET::AGL | PLAYER_SET::STM);
					break;
				case MYOBJECT::BP_PLAYER:
					Tired();
					add_stat(PLAYER_SET::AS_FIGHT);
					add_stat_forFight(PLAYER_SET::STR);
					break;
				case MYOBJECT::PB_PLAYER:
					Tired();
					add_stat(PLAYER_SET::AS_FIGHT);
					add_stat_forFight(PLAYER_SET::STR | PLAYER_SET::AGL | PLAYER_SET::STM);
					break;
				case MYOBJECT::YCN_PLAYER:
					Tired();
					add_stat(PLAYER_SET::AS_FIGHT);
					add_stat_forFight(PLAYER_SET::AGL | PLAYER_SET::STM);
					break;
				}
				_time = 0;
				_fClickReady = true;
			}
			// 여기서 액션을 초기화한다.
			if (_fActionInit)
			{
				switch (_actionType)
				{
				case MYOBJECT::WORK_PLAYER:
					_myStat.workGauge = limit_stat(_myStat.workGauge, true);
					break;
				default:
					_myStat.health = limit_stat(_myStat.health);
					_myStat.food = limit_stat(_myStat.food);
					_myStat.mood = limit_stat(_myStat.mood);
					_myStat.energy = limit_stat(_myStat.energy);
					break;
				}
				_fActionInit = false;
			}
		}//if: fAction이 True 라면 플레이어가 행동한다.
	}//if: actionType이 정의되어 있을 때
	if (_fAction == false)
	{
		_actionType = _actionType & MYOBJECT::RUN_PLAYER;
		_fVisible = true;
		_fObjClickLock = false;
	}//else: 액션을 멈추면 플레이어를 볼 수 있다.
}
//==========================================
//##			아이템 사용				  ##
//==========================================
void Player::use(SLOT::ITEM type)
{
	switch (type)
	{
	case SLOT::ITM_MEAT:
		add_stat(100, 400, 10, 0);
		break;
	case SLOT::ITM_SODA:
		add_stat(0, 90, 10, 0);
		break;
	case SLOT::ITM_PIZZA_BOX:
		add_stat(100, 170, 10, 0);
		break;
	}
}

void Player::add_stat(double health, double food, double mood, double energy)
{
	_myStat.health += health;
	_myStat.food += food;
	_myStat.mood += mood;
	_myStat.energy += energy;

	int plusCnt = 0;
	// Make status beads
	if (health < 0) { make_bead(BEAD::BD_HEALTH, 0, true); }
	else
	{
		plusCnt++;
		make_bead(BEAD::BD_HEALTH, plusCnt);
	}
	if (food < 0) { make_bead(BEAD::BD_FOOD, 0, true); }
	else
	{
		plusCnt++;
		make_bead(BEAD::BD_FOOD, plusCnt);
	}
	if (mood < 0) { make_bead(BEAD::BD_MOOD, 0, true); }
	else
	{
		plusCnt++;
		make_bead(BEAD::BD_MOOD, plusCnt);
	}
	if (energy < 0) { make_bead(BEAD::BD_ENERGY, 0, true); }
	else
	{
		plusCnt++;
		make_bead(BEAD::BD_ENERGY, plusCnt);
	}
}
void Player::add_stat(int effectsStat)
{
	if (effectsStat & PLAYER_SET::AS_FIGHT)
	{
		add_stat(10, -22.5, -5, -33.75);
	}
}
void Player::add_stat_forFight(int effectsStat, bool isLostExp)
{
	int str_percent, agl_percent, stm_percent;
	int str = (int)(_myStat.str / 1000 - 1);
	int agl = (int)(_myStat.agl / 1000 - 1);
	int stm = (int)(_myStat.stm / 1000 - 1);
	int correction = 30;
	// Make percentage
	int percent = 75;
	str_percent = RAND->get_fromIntTo(1, 100);
	agl_percent = RAND->get_fromIntTo(1, 100);
	stm_percent = RAND->get_fromIntTo(1, 100);
	// Make bead counter
	int plusCnt = 0;
	if (isLostExp)
	{
		// Empty yet..
	}//if: subtraction
	else
	{
		if (str_percent <= percent &&
			effectsStat & PLAYER_SET::STR)
		{
			_myStat.str += (STAT_EXP - str * correction);
			plusCnt++;
			make_bead(BEAD::BD_STR, plusCnt);
		}
		if (agl_percent <= percent &&
			effectsStat & PLAYER_SET::AGL)
		{
			_myStat.agl += (STAT_EXP - str * correction);
			plusCnt++;
			make_bead(BEAD::BD_AGL, plusCnt);
		}
		if (stm_percent <= percent &&
			effectsStat & PLAYER_SET::STM)
		{
			_myStat.stm += (STAT_EXP - str * correction);
			plusCnt++;
			make_bead(BEAD::BD_STM, plusCnt);
		}
	}//else: add
}

void Player::Tired()
{
	if (_myStat.food < 120 || _myStat.energy < 120)
	{
		action_pause();
		_fTired = true;
		//_fClick = false;
		_hunger->Visible();
	}
}

void Player::buy_item(SLOT::ITEM itemType)
{
	int price = 0;
	switch (itemType)
	{
	case SLOT::ITM_MEAT:
		price = PRICE_MEAT;
		break;
	case SLOT::ITM_PIZZA_BOX:
		price = PRICE_PIZZA_BOX;
		break;
	case SLOT::ITM_SODA:
		price = PRICE_SODA;
		break;
	}//switch: Define item's price;
	auto iter = _inven.find(itemType);
	if (_myStat.money >= price)
	{
		if (iter == _inven.end())
		{
			_inven.insert(make_pair(itemType, 1));
			_myStat.money -= price;
		}
		else
		{
			if (iter->second < 7)
			{
				iter->second++;
				_myStat.money -= price;
			}
		}
	}//if: Enough money, could buy goods
}
void Player::use_item(SLOT::ITEM itemType)
{
	auto iter = _inven.find(itemType);
	if (iter != _inven.end())
	{
		if (iter->second > 0)
		{
			iter->second--;
			use(itemType);
		}
	}
}

HRESULT Player::init()
{
	set_imgPath("Object/Player/");
	init_player();
	// 배고플 때 쓰는 아이콘
	_hunger = new Icon(ICON::ICN_HUNGER);
	_hunger->init();
	_fObjMove = true;
	return S_OK;
}
void Player::release()
{
	delete_player();
	Release(_hunger);
}
void Player::update()
{
	update_player();
	follow_icon_player();
	action();
}
void Player::render()
{
	if (_fVisible)
	{
		Draw(_hunger);
		draw_player();
	}
	if (_fDebug)
	{
		ColorRect(get_memDC(), _collision.rc);
		if (!_dest.empty())
		{
			ColorRect(get_memDC(),
				RectMakeCenter(_dest.front().get_dest().x, _dest.front().get_dest().y, 10, 10),
				RGB(10, 10, 130));
		}
	}
}
Player::Player()
{
	// 처음에 피자 2판 주고 시작
	buy_item(SLOT::ITM_PIZZA_BOX);
	buy_item(SLOT::ITM_PIZZA_BOX);
}
Player::~Player()
{
}

void Player::set_playerCenter(POINT center)
{
	_player_center = center;
	_player_idle[_idleIndex]->set_center(_player_center);
	_player_idle_shdw[_idleIndex]->set_center(_player_center);
	setup_collision_rect();
	follow_icon_player();
}
Destination Player::get_destination()
{
	if (!_dest.empty())
	{
		return _dest.front();
	}
	return Destination();
}
void Player::fix_destination(Destination dest)
{
	_dest.front().setup_destination(dest.get_dest(), dest.get_runType());
}
void Player::push_destination(
	POINT dest, 
	bool isUseReservation,
	MYOBJECT::RUN_TYPE runType)
{
	Destination myDest;
	if (isUseReservation) 
	{
		myDest.setup_destination(dest, runType);
		_dest.push(myDest);
	}
	else
	{
		myDest.setup_destination(dest, runType);
		pop_destinaiton();
		_dest.push(myDest);
	}
}
void Player::pop_destinaiton()
{
	if (!_dest.empty())
	{
		_dest.pop();
	}
}
void Player::init_playerHp()
{
	// Hp의 기본 값은 Stm과 연동한다.
	double maxHp = 60 + get_stm() * 17;
	// 실제 사용하는 Hp는 health gauge 와 연동한다.
	double correction = _myStat.health / 1000.0;
	_myStat.hp_correction = correction;
	maxHp *= correction;
	_myStat.maxHp = maxHp;
	_myStat.currentHp = maxHp;
}
void Player::add_playerHp(double add_hp)
{
	_myStat.currentHp += add_hp;
}
void Player::init_playerNrg()
{
}
void Player::add_playerNrg()
{
}
int Player::how_many_items(SLOT::ITEM itemType)
{
	auto iter = _inven.find(itemType);
	if (iter != _inven.end())
	{
		return iter->second;
	}
	return 0;
}
