#pragma once
namespace BEAD
{
	enum TYPE
	{
		BD_EMPTY,
		// Stat
		BD_HEALTH,
		BD_FOOD,
		BD_MOOD,
		BD_ENERGY,
		// Fight
		BD_STR,
		BD_AGL,
		BD_STM,
	};
}
namespace HINT
{
	enum TYPE
	{
		HINT_EMPTY,
		HINT_NORMAL,
		HINT_THINK
	};
}
namespace GAUGE
{
	enum TYPE
	{
		GG_EMPTY,
		GG_WORK,
		GG_STAT_SMALL,
		GG_STAT_FIGHT,
		GG_PLAYER_HP,
		GG_ENEMY_HP,
		GG_ENERGY
	};
	enum STAT
	{
		ST_EMPTY,
		ST_STR,
		ST_AGL,
		ST_STM
	};
}
namespace SLOT
{
	enum TYPE
	{
		SLT_EMPTY,
		SLT_ACTIVE_SKILL,
		SLT_ITEM_SHOP,
		SLT_ITEM_FRIGER
	};
	enum SKILL
	{
		SKL_EMPTY,
		SKL_BLOCK,
		SKL_DODGE,
		SKL_PUNCH
	};
	enum ITEM
	{
		ITM_EMPTY,
		ITM_MEAT,
		ITM_PIZZA_BOX,
		ITM_SODA
	};
#define PRICE_MEAT	20
#define PRICE_PIZZA_BOX	9
#define	PRICE_SODA	6
}
namespace ICON
{
	enum TYPE
	{
		ICN_EMPTY,
		ICN_HUD_MAP,
		ICN_LEAGUE,
		ICN_SKILLTREE,
		// 스탯 아이콘
		ICN_ENERGY,
		ICN_MOOD,
		ICN_FOOD,
		ICN_HEALTH,
		// 스탯(전투) 아이콘
		ICN_STR,
		ICN_AGL,
		ICN_STM,
		// 냉장고 아이콘
		ICN_FRIGER,
		// 배고픈 아이콘
		ICN_HUNGER
	};
}
namespace MAPICON
{
	enum TYPE
	{
		ICN_EMPTY,
		ICN_HOME,
		ICN_SHOP,
		ICN_GYM,
		ICN_BUILD,
		ICN_PLAYER
	};
}
namespace WINDOW
{
	enum TYPE
	{
		WND_NONE,
		WND_FRIGER,
		WND_SHOP,
		WND_LEAGUE,
		WND_BUS,
		WND_BUILD,
		WND_SETTING
	};
}
namespace MYTEXT
{
	enum TYPE
	{
		TXT_NONE,
		TXT_TITLE,
		TXT_DESCR
	};
}
namespace BUTTON
{
	enum TYPE
	{
		BTN_NONE,
		BTN_RED,
		BTN_RED_LONG,
		BTN_DELETE_RED,
		BTN_BLUE_LONG,
		BTN_GREEN,
		BTN_GREEN_LONG,
		BTN_GREEN_INVEN,
		BTN_BUS_GREEN,
		BTN_WORK_GREEN
	};
	enum ICON
	{
		ICN_DOLLAR,
		ICN_TIME_DAYS,
		ICN_DELETE
	};
}
