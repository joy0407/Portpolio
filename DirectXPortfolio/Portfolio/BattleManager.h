#pragma once
class BattleManager
{
private:
	static BattleManager * instance;

public:
	static BattleManager * GetInstance();

	class Player * GetPlayer();
	vector<class Monster*>& GetMonsterList();

	void SetPlayer(class Player * player);
	void AddMonster(class Monster * monster);

private:
	BattleManager();
	~BattleManager();

private:
	class Player * player;
	vector<class Monster*> monsterList;
};

