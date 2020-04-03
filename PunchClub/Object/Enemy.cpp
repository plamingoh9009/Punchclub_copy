#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
HRESULT Enemy::init_stat()
{
	if (_myStat.level) {}
	else
	{
		double str = PLAYER->get_stat().str;
		double agl = PLAYER->get_stat().agl;
		double stm = PLAYER->get_stat().stm;
		_myStat.level = (int)((str + agl + stm) / 6.0);
	}
	double lowStat = _myStat.level + ((_myStat.level - 1) * 1);
	double maxStat = (_myStat.level + 1) + ((_myStat.level - 1) * 2);
	_myStat.str = RAND->get_fromIntTo((int)lowStat, (int)maxStat);
	_myStat.agl = RAND->get_fromIntTo((int)lowStat, (int)maxStat);
	_myStat.stm = RAND->get_fromIntTo((int)lowStat, (int)maxStat);
	// Hp
	_myStat.maxHp = 60 + _myStat.stm * 17;
	_myStat.currentHp = _myStat.maxHp;
	return S_OK;
}

HRESULT Enemy::init()
{
	init_stat();
	return S_OK;
}
void Enemy::release()
{
}
void Enemy::update()
{
}
void Enemy::render()
{
}
Enemy::Enemy()
{
}
Enemy::Enemy(int enemyLevel)
{
	_myStat.level = enemyLevel;
}
Enemy::~Enemy()
{
}
