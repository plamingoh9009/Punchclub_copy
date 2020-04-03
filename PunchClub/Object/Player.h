#pragma once
#include "Unit.h"
#include "Base/SingletonBase.h"
#include "UI/uiEnum.h"
#include "UI/Icons/Icon.h"
#include "UI/Hint.h"
#include "UI/Bead.h"
class Player : public Unit, public SingletonBase<Player>
{
private:
	typedef map<SLOT::ITEM, int> ItemList;	// Item list => Inventory
	typedef vector<Bead *> Beads;			// InGameUI에 넘겨줄 비드 벡터
	typedef queue<Destination> Destinations;	// 플레이어가 이동할 좌표들
	const double STAT_EXP = 100;	// Gain exp when player training
private:
	// Idle Images
	Image * _player_idle[4];
	Image * _player_idle_shdw[4];
	// Walk Images
	Image * _player_move[6];
	Image * _player_move_shdw[6];
	POINT _player_center;
	// 이미지 바꿀 때 쓰는 변수
	bool _fIdle = true;
	int _idleIndex = 0;
	// 플레이어가 걸을 때 쓰는 변수
	Destinations _dest;
	bool _fMoving = false;
	int _moveIndex = 0;
	int _speed = 2;
	// 플레이어 충돌처리에 쓰는 변수
	Collision _collision;
	// 플레이어 능력치
	PlayerStat _myStat;		// 플레이어 능력치
	ItemList _inven;		// 플레이어의 인벤토리
	Beads _beads;			// 플레이어의 스탯 구슬
	MAPICON::TYPE _location = MAPICON::ICN_HOME;	// 플레이어의 첫 위치는 집이다.
	Icon * _hunger;			// 배고플 때 쓰는 아이콘
	// 플레이어의 타이머
	double _time = 0;
	// 플레이어가 무엇을 할지 결정하는 변수다.
	int _actionType = MYOBJECT::RUN_EMPTY;
	bool _fAction = false;
	bool _fActionInit = false;
	bool _fClickReady = false;
	bool _fTired = false;
	bool _fVisible = true;
protected:
	void change_idle_img();
	void update_move_img();
	void follow_icon_player();
	// Player functions
	void init_player();
	HRESULT init_player_moves();
	void draw_player();
	void update_player();
	void delete_player();
	void hide_player();
	void move_player();
	// Collision
	void setup_collision_rect();
	// Bead
	void make_bead(BEAD::TYPE type, int plusCnt, bool isReverse = false);
	// Limit
	double limit_stat(double stat, bool fZeroSet = false);
	bool is_positionOK(LONG currentPos, LONG targetPos);
	bool is_positionOK(POINT currentPos, POINT targetPos);
	bool is_move_dest_left(LONG currentPos, LONG targetPos);
protected:
	void action();
	void use(SLOT::ITEM itemType);
	void add_stat(double health, double food, double mood, double energy);
	void add_stat(int effectsStat);
	void add_stat_forFight(int effectsStat, bool isLostExp = false);
public:
	inline void action_start() { _fAction = true; }
	inline void action_pause() { _fAction = false; }
	inline void action_init() { _fActionInit = true; }
	void Tired();
public:
	inline void add_money(int money) { _myStat.money += money; }
	void buy_item(SLOT::ITEM itemType);
	void use_item(SLOT::ITEM itemType);
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
public:
	Player();
	~Player();
public:
	void update_idle_img(bool isResetPos = false);
	inline PlayerStat get_stat() { return _myStat; }
	inline int get_str() { return (int)(_myStat.str / 1000.0); }
	inline int get_agl() { return (int)(_myStat.agl / 1000.0); }
	inline int get_stm() { return (int)(_myStat.stm / 1000.0); }
	inline MAPICON::TYPE get_playerLocation() { return _location; }
	inline POINT get_playerCenter() { return _player_center; }
	inline int get_playerHeight()
	{
		return (int)(_player_idle[_idleIndex]->get_height());
	}
	inline int get_playerWidth()
	{
		return (int)(_player_idle[_idleIndex]->get_width());
	}
	inline Collision get_collision() { return _collision; }
	
	int get_actionType() { return _actionType; }
	Beads get_beads() { return _beads; }
	void set_playerCenter(POINT center);
	void set_playerLocation(MAPICON::TYPE type) { _location = type; }
	void set_playerAction(int type) { _actionType = type; }
	// Hp
	void init_playerHp();
	void add_playerHp(double add_hp);
	void init_playerNrg();
	void add_playerNrg();
	inline void init_workGauge() { _myStat.workGauge = 0; }
	int how_many_items(SLOT::ITEM itemType);
	inline bool is_running_action() { return _fAction; }
	inline bool is_tired() { return _fTired; }
	inline bool is_click_ready() { return _fClickReady; }
public:
	Destination get_destination();
	void fix_destination(Destination dest);
	void push_destination(POINT dest,
		bool isUseReservation = false,
		MYOBJECT::RUN_TYPE runType = MYOBJECT::RUN_EMPTY);
	void pop_destinaiton();
};
#define PLAYER	Player::get_singleton()