#pragma once

#include <string>
#include <iostream>
#include "Vector.h"
#include "Player.h"
#include "Globals.h"


class Team
{
private:
	std::string mName;
	Vector<Player> mPlayers;

public:
	void Initialize(int numPlayers)
	{
		mPlayers.Clear();
		for (int i = 0; i < numPlayers; ++i)
		{
			mPlayers.PushBack(Player());
		}
	}
	Player* GetNextBattlingPlayer()
	{
		Player* player = nullptr;
		for (std::size_t i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].IsAlive() && mPlayers[i].GetStats(AttackCount) > 0)
			{
				if (player == nullptr || mPlayers[i].GetStats(Speed) > player->GetStats(Speed))
				{
					player = &mPlayers[i];
				}
			}
		}
		return player;
	}

	void DamagePlayer(Player* player)
	{
		//e.Void DamagePlayer(Player* player)
		//i.Pass in the player from another team
		//ii.Use that player’s damage to attack a random living player in the team
		//iii. 25 % chance that the player attacked will slow down by 10
		//iv. 10 % chance the attacking player will speed up by 5

		if (player == nullptr) return;
		int damage = player->GetStats(Attack);
		int targetIndex = rand() % mPlayers.Size();
		while (!mPlayers[targetIndex].IsAlive())
		{
			targetIndex = rand() % mPlayers.Size();
		}
		mPlayers[targetIndex].SetStat(Health, mPlayers[targetIndex].GetStats(Health) - damage);
		if (rand() % 100 < 25)
		{
			mPlayers[targetIndex].SetStat(Speed, mPlayers[targetIndex].GetStats(Speed) - 10);
		}
		if (rand() % 100 < 10)
		{
			player->SetStat(Speed, player->GetStats(Speed) + 5);
		}
		player->SetStat(AttackCount, 0);
	}

	int GetRemainingPlayers()
	{
		//f.Int GetRemainingPlayers()
		//i.Returns the count of the number of players that have health > 0
		int remainingPlayers = 0;
		for (std::size_t i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].IsAlive())
			{
				remainingPlayers++;
			}
		}
		return remainingPlayers;
	}

	void OrderPlayers()
	{
		Globals::IntroSort(mPlayers.Begin(), mPlayers.End(),
			[](const Player& a, const Player& b)
			{
				int speedA = a.GetStats(Speed);
				int speedB = b.GetStats(Speed);

				if (a.GetStats(AttackCount) == 0 || a.GetStats(Health) <= 0)
				{
					speedA = 0;
				}

				if (b.GetStats(AttackCount) == 0 || b.GetStats(Health) <= 0)
				{
					speedB = 0;
				}

				return speedA > speedB;
			});
	}

	void StartTurn()
	{
		for (std::size_t i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].IsAlive())
			{
				mPlayers[i].SetStat(AttackCount, 1);
			}
		}
		OrderPlayers();
	}

};