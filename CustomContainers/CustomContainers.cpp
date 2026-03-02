#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Inventory.h"
#include "Globals.h"

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


int main()
{

    
    return 0;
}