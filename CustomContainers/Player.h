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
//Create a class Player
//a.Player should have a name(std::string is fine)
//b.Player should have an int Array that contains all of the stats in the enum
//c.There should be a function to Initialize the player with default values
//i.Health = 100
//ii.The rest of the stats are random from 5 - 20
//iii.AttackCount is 1, each attack reduces it by 1 (at 0, can’t attack)
//d.Int GetStat(Stats stat)
//i.Returns the value for the stated stat
//e.Void SetStat(Stats stat, int value)
//i.Update a stat
//f.Bool IsAlive() const
//i.Returns true if health > 0
class Player
{
public:
	Player()
	{
		stats[Health] = 100;
		stats[Attack] = 5;
		stats[Speed] = 100;
		stats[AttackCount] = 1;
	}

	std::string name;
	int stats[Count];

	int GetStats()
	{
		return stats[Count];
	}

	void SetStats(Stats stat, int value)
	{

	}

	bool IsAlive()
	{
		if (Health <= 0)
			return false;
		else
			return true
	}
};