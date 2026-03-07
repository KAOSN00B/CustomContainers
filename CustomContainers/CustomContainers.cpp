#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Inventory.h"
#include "Globals.h"
#include "MSTGraph.h"
#include "MSTGraphK.h"
#include "Team.h"
#include "City.h"

void Assignment()
{

    Inventory& inventory = Inventory::Get();

    Vector<std::string> mKeyNames;

    // 20 key names
    mKeyNames.PushBack("Bronze Key");
    mKeyNames.PushBack("Silver Key");
    mKeyNames.PushBack("Gold Key");
    mKeyNames.PushBack("Ruby Key");
    mKeyNames.PushBack("Emerald Key");
    mKeyNames.PushBack("Sapphire Key");
    mKeyNames.PushBack("Iron Key");
    mKeyNames.PushBack("Crystal Key");
    mKeyNames.PushBack("Ancient Key");
    mKeyNames.PushBack("Dungeon Key");
    mKeyNames.PushBack("Castle Key");
    mKeyNames.PushBack("Forest Key");
    mKeyNames.PushBack("Fire Key");
    mKeyNames.PushBack("Water Key");
    mKeyNames.PushBack("Shadow Key");
    mKeyNames.PushBack("Light Key");
    mKeyNames.PushBack("Ice Key");
    mKeyNames.PushBack("Storm Key");
    mKeyNames.PushBack("Dragon Key");
    mKeyNames.PushBack("Obsidian Key");

    // Add 100 random keys
    for (int i = 0; i < 100; ++i)
    {
        int index = rand() % mKeyNames.Size();
        inventory.PickupKey(mKeyNames[index], 1);
    }

    std::cout << "Initial Inventory:\n";
    inventory.PrintInventory();

    int doorsUnlocked = 0;
    int failedAttempts = 0;

    bool running = true;

    while (running)
    {
        std::cout << "\n1) Open Door\n2) Pick Up Key\n3) Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int index = rand() % mKeyNames.Size();
            std::string requiredKey = mKeyNames[index];

            std::cout << "You arrive at a door and need a "
                << requiredKey << "\n";

            if (inventory.UseKey(requiredKey, 1))
            {
                std::cout << "You have the " << requiredKey
                    << " and have unlocked the door!\n";
                doorsUnlocked++;
            }
            else
            {
                std::cout << "You do not have the "
                    << requiredKey
                    << ", the door will remain locked.\n";
                failedAttempts++;
            }
            break;
        }

        case 2:
        {
            int index = rand() % mKeyNames.Size();
            std::string newKey = mKeyNames[index];

            inventory.PickupKey(newKey, 1);

            std::cout << "You picked up a "
                << newKey << "\n";

            break;
        }

        case 3:
            running = false;
            break;
        }
    }

    std::cout << "\nFinal Inventory:\n";
    inventory.PrintInventory();

    std::cout << "\nDoors Unlocked: " << doorsUnlocked << "\n";
    std::cout << "Failed Attempts: " << failedAttempts << "\n";

}

void GraphTesting()
{
    std::cout << "Custom MST Graph\n";
    //a, b, c, d, e, 

    Vector<std::string> nodes;
    nodes.PushBack("A");
    nodes.PushBack("B");
    nodes.PushBack("C");
    nodes.PushBack("D");
    nodes.PushBack("E");

    // using prims algorithm
    // add all nodes to graph

    MSTGraph<std::string, int> mstGraphPA;

    for (std::size_t i = 0; i < nodes.Size(); ++i)
    {
        mstGraphPA.AddItem(&nodes[i]);
    }

    mstGraphPA.AddEdge(0, 1, 9); // A-B 9
    mstGraphPA.AddEdge(0, 2, 5); // A-C 5
    mstGraphPA.AddEdge(0, 3, 2); // A-D 2
    mstGraphPA.AddEdge(1, 3, 6); // B-D 6
    mstGraphPA.AddEdge(1, 4, 5); // B-E 5
    mstGraphPA.AddEdge(2, 3, 4); // C-D 4
    mstGraphPA.AddEdge(2, 4, 5); // C-E 5
    mstGraphPA.AddEdge(3, 4, 4); // D-E 4

    mstGraphPA.GenerateMST(0); // start at A
    // print results
    const Vector<MSTGraph<std::string, int>::Edge>& mstEdges = mstGraphPA.GetMST();
    int totalWeightPA = 0;

    for (std::size_t i = 0; i < mstEdges.Size(); ++i)
    {
        std::cout << nodes[mstEdges[i].fromIndex] << "-"
            << nodes[mstEdges[i].toIndex]
            << " (" << mstEdges[i].weight << ")\n";

        totalWeightPA += mstEdges[i].weight;
    }

    std::cout << "Total Weight (Prim): " << totalWeightPA << "\n";

    std::cout << "\nCustom MST Graph with Kruskal's Algorithm\n";

    // using kruskal's algorithm
    MSTGraphK<int> mstGraphKA;

    mstGraphKA.AddEdge(0, 1, 9); // A-B 9
    mstGraphKA.AddEdge(0, 2, 5); // A-C 5
    mstGraphKA.AddEdge(0, 3, 2); // A-D 2
    mstGraphKA.AddEdge(1, 3, 6); // B-D 6
    mstGraphKA.AddEdge(1, 4, 5); // B-E 5
    mstGraphKA.AddEdge(2, 3, 4); // C-D 4
    mstGraphKA.AddEdge(2, 4, 5); // C-E 5
    mstGraphKA.AddEdge(3, 4, 4); // D-E 4

    mstGraphKA.GenerateMST();
    // print results

    const Vector<MSTGraphK<int>::Edge>& mstEdgesK = mstGraphKA.GetMST();

    int totalWeightKA = 0;

    for (std::size_t i = 0; i < mstEdgesK.Size(); ++i)
    {
        std::cout << nodes[mstEdgesK[i].fromNode] << "-"
            << nodes[mstEdgesK[i].toNode]
            << " (" << mstEdgesK[i].weight << ")\n";

        totalWeightKA += mstEdgesK[i].weight;
    }

    std::cout << "Total Weight (Kruskal): " << totalWeightKA << "\n";


}

void Assignment6()
{
    std::cout << "Team Battle Simulation\n";

    srand((unsigned int)time(nullptr));

    Team teamA;
    Team teamB;

    teamA.Initialize(10);
    teamB.Initialize(10);

    while (teamA.GetRemainingPlayers() > 0 && teamB.GetRemainingPlayers() > 0)
    {
        teamA.StartTurn();
        teamB.StartTurn();
        while (true)
        {
            Player* playerA = teamA.GetNextBattlingPlayer();
            Player* playerB = teamB.GetNextBattlingPlayer();

            if (playerA == nullptr && playerB == nullptr)
                break;

            Player* attacker = nullptr;
            Team* targetTeam = nullptr;

            if (playerA && (!playerB || playerA->GetStats(Speed) >= playerB->GetStats(Speed)))
            {
                attacker = playerA;
                targetTeam = &teamB;
            }
            else
            {
                attacker = playerB;
                targetTeam = &teamA;
            }

            targetTeam->DamagePlayer(attacker);

            teamA.OrderPlayers();
            teamB.OrderPlayers();

            std::cout << "Team A remaining: " << teamA.GetRemainingPlayers() << "\n";
            std::cout << "Team B remaining: " << teamB.GetRemainingPlayers() << "\n\n";

            if (teamA.GetRemainingPlayers() == 0 || teamB.GetRemainingPlayers() == 0)
                break;
        }
    }

    if (teamA.GetRemainingPlayers() > 0)
    {
        std::cout << "Team A wins the fight!\n";
    }
    else if (teamB.GetRemainingPlayers() > 0)
    {
        std::cout << "Team B wins the fight!\n";
    }
    else
    {
        std::cout << "It's a draw!\n";
    }
}

//Assignment 7
//Main flow
//a.Scenario is you are playing a town sim game
//b.Create a City
//c.Populate the city with the houses laid out as in the diagram below
//d.The units are measured in meters
//e.Each meter of road costs $10
//f.What is the cheapest road that can be built to connect all the houses ?
//g.Print the MST connections for both
//h.Print the total cost for the road(both methods should be the same)
int main()
{
    City city;

    city.AddHouse("A", { 20, 40 });
    city.AddHouse("B", { 50, 20 });
    city.AddHouse("C", { 90, 40 });
    city.AddHouse("D", { 60, 80 });
    city.AddHouse("E", { 30, 120 });
    city.AddHouse("F", { 100, 110 });
    city.AddHouse("G", { 150, 130 });
    city.AddHouse("H", { 160, 90 });
    city.AddHouse("I", { 140, 60 });
    city.AddHouse("J", { 180, 30 });
    city.AddHouse("K", { 200, 120 });
    city.AddHouse("L", { 220, 70 });
    city.AddHouse("M", { 240, 50 });

	city.ConnectAllHouses();

    for (size_t i = 0; i < city.mHouses.Size(); ++i)
    {
        std::cout << "House " << city.mHouses[i].mName
            << " at position (" << city.mHouses[i].mPosition.x
            << ", " << city.mHouses[i].mPosition.y << ")\n";
    }

	float totalCostPrim = city.GetTotalRoadDistancePrim() * 10;
	float totalCostKruskal = city.GetTotalRoadDistanceKruskal() * 10;

	std::cout << "Total Road Cost (Prim's Algorithm): $" << totalCostPrim << "\n";
	std::cout << "Total Road Cost (Kruskal's Algorithm): $" << totalCostKruskal << "\n";


    return 0;
}