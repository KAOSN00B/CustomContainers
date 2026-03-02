#pragma once
//Create a class Team
//a.Std::string mName;
//b.Vector<Player> mPlayers;
//c.Initialize(int numPlayers)
//d.Player* GetNextBattlingPlayer()
//i.Returns the player with the fastest speed that hasnt attacked
//e.Void DamagePlayer(Player* player)
//i.Pass in the player from another team
//ii.Use that player’s damage to attack a random living player in the team
//iii. 25 % chance that the player attacked will slow down by 10
//iv. 10 % chance the attacking player will speed up by 5
//v.Attacking player’s AttackCount is set to 0
//f.Int GetRemainingPlayers()
//i.Returns the count of the number of players that have health > 0
//g.Void OrderPlayers()
//i.Sorts players by fastest speed(use IntroSort)
//ii.If they have already attacked this turn
//With the sort callback, if the AttackCount or Health is 0, act as
//if the speed is 0 (dont set the speed to 0, just treat it as 0 in the
//	callback)
//	h.Void StartTurn()
//	i.Goes through and set all active player’s AttackCount to 1
//	ii.Call OrderPlayers to start the turn

class Team
{

};