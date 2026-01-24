#include "Inventory.h"
#include "PriorityQueue.h"

/*3) Create a class Inventory
a. Contains a Vector of Items
b. void Initialize()
i. Add several items to the Vector with some (min10)
c. void AddItem(ItemType itemType)
d. void DisplayInventory()
i. Create a PriorityQueue
ii. Add everything from the inventory Vector to the PriorityQueue
iii. Print the PriorityQueue in order of highest count
*/

void Inventory::Initialize()
{
    items.PushBack(Item(SmallHealth, +10));
    items.PushBack(Item(MedHealth, +25));
    items.PushBack(Item(LightningSpell, -30));
    items.PushBack(Item(Grenade, -40));
    items.PushBack(Item(Bomb, -60));
    items.PushBack(Item(Shield, +15));

    // Give at least 10 starting items
    for (int i = 0; i < 10; ++i)
    {
        items[i % items.Size()].AddItem();
    }
}

void Inventory::AddItem(ItemType itemType)
{
    for (std::size_t i = 0; i < items.Size(); ++i)
    {
        if (items[i].mType == itemType)
        {
            items[i].AddItem();
            return;
        }
    }
}

void Inventory::DisplayItems()
{
    PriorityQueue<Item> pq;

    if (items.Size() == 0)
    {
        std::cout << "Queue empty";
        return;
    }
    // ii) Add everything from vector to PQ
    for (std::size_t i = 0; i < items.Size(); ++i)
    {
        pq.Push(items[i]);
    }

    // iii) Print in order of highest count
    std::cout << "\n--- Inventory (Highest Count First) ---\n";

    while (!pq.Empty())
    {
        Item top = pq.Top();
        pq.Pop();

        std::cout << top.mName << " x" << top.mCount << "\n";
    }
}