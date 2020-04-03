#pragma once
namespace MYOBJECT
{
	enum TYPE
	{
		OBJ_EMPTY,
		// Facility
		OBJ_TREADMILL,
		OBJ_BARBELL,
		OBJ_YUNGCHUN,
		OBJ_TIRE,
		OBJ_BENCH_PRESS,
		OBJ_PUNCHBUG,
		// Furniture
		OBJ_FRIGER,
		OBJ_SOFA,
		OBJ_TV,
		OBJ_AQUARIUM,
		OBJ_FAN,
		OBJ_CLOCK,
		OBJ_KITCHEN_TABLE,
		OBJ_STAND,
		OBJ_TABLE,
		OBJ_BOOKSHELF,
		OBJ_PHONE
	};
	enum RUN_TYPE
	{
		RUN_EMPTY,
		// Work
		WORK_PLAYER,
		// Facility
		TRM_NORMAL,
		TRM_ORANGE_GIRL,
		TRM_YELLOW_GIRL,
		TRM_PLAYER,
		BBL_PLAYER,
		YCN_PLAYER,
		TIR_PLAYER,
		BP_PLAYER,
		PB_PLAYER,
		// Furniture
		SOFA_PLAYER,
		TV_PLAYER,
		RUN_PLAYER = 0b10000000
	};
}
struct Collision
{
	RECT rc;
	int width, height;
	int correctionX = 0;
	int correctionY = 0;
	bool on = false;
};
class Destination
{
	POINT _dest;
	MYOBJECT::RUN_TYPE _runType;
	bool _fEmpty;
public:
	Destination::Destination()
	{
		_fEmpty = true;
	}
	Destination::~Destination() {}
	bool isEmpty() { return _fEmpty; }
	POINT get_dest() { return _dest; }
	MYOBJECT::RUN_TYPE get_runType() { return _runType; }
	void setup_destination(POINT dest, MYOBJECT::RUN_TYPE runType)
	{
		_fEmpty = false;
		_dest = dest;
		_runType = runType;
	}
};
namespace NPC
{
	enum TYPE
	{
		NPC_EMPTY,
		NPC_SHOP
	};
}
namespace PLAYER_SET
{
	enum STAT
	{
		STR = 0b0001,
		AGL = 0b0010,
		STM = 0b0100
	};
	enum ADD_STAT
	{
		AS_FIGHT = 0b0001
	};
}
struct PlayerStat
{
	double health = 800;
	double food = 600;
	double energy = 600;
	double mood = 600;
	// Stat for fight
	double str = 1250;
	double agl = 1250;
	double stm = 1250;
	double maxHp;
	double currentHp;
	double hp_correction;
	double currentNrg = 1000;
	// SP & Money
	int skillPoint = 3;
	int money = 73;
	// Work Gauge
	double workGauge = 250;
};
struct EnemyStat
{
	int level = 1;
	double str;
	double agl;
	double stm;
	double maxHp;
	double currentHp;
	double currentNrg = 1000;
};