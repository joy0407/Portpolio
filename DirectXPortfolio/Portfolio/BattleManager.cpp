#include "pch.h"
#include "BattleManager.h"

BattleManager* BattleManager::instance = NULL;

BattleManager * BattleManager::GetInstance()
{
	if (instance == NULL)
		instance = new BattleManager();

	return instance;
}

Player * BattleManager::GetPlayer()
{
	return player;
}

vector<Monster*>& BattleManager::GetMonsterList()
{
	return monsterList;
}

void BattleManager::SetPlayer(Player * player)
{
	this->player = player;
}

void BattleManager::AddMonster(Monster * monster)
{
	monsterList.push_back(monster);
}

BattleManager::BattleManager()
{
}


BattleManager::~BattleManager()
{
}
