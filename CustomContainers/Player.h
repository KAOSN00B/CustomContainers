#pragma once
#include <iostream>
#include <string>

enum Stats
{
	Health, 
	Attack, 
	Speed, 
	AttackCount,
	Count

};

class Player
{
public:
	Player()
	{
		stats[Health] = 100;
		stats[Attack] = 5 + rand() % 16;
		stats[Speed] = 5 + rand() % 16;
		stats[AttackCount] = 1;
	}

	std::string name;
	int stats[Count];

	int GetStats(Stats stat) const
	{
		if (stat == Speed && stats[Speed] < 0)
			return 0;

		return stats[stat];
	}

	void SetStat(Stats stat, int value)
	{
		if (value < 0)
			value = 0;

		stats[stat] = value;
	}


	bool IsAlive() const
	{
		if (stats[Health] <= 0)
			return false;
		else
			return true;
	}
};