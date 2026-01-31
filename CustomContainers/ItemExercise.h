#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Vector.h"
#include "LinkedList.h"
#include "KDTree.h"
#include "Vector2.h"


enum ItemType
{
    IT_HEALTH,
    IT_WELLNESS,
    IT_COUNT,
};

struct Item
{
    std::string name;
    ItemType itemType;
    Vector2 position;
};

struct FilterByType
{
    ItemType itemType;

    bool operator()(const void* data)
    {
        const Item* item = static_cast<const Item*>(data);
        return item->itemType == itemType;
    }
};

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    Vector<Item> items;
    KDTree<float, 2> itemLocations;

    int maxItems = 100;
    items.Resize(maxItems);

    for (int i = 0; i < maxItems; ++i)
    {
        items[i].name = "Item Name " + std::to_string(i);
        items[i].itemType = static_cast<ItemType>(i % IT_COUNT);

        switch (items[i].itemType)
        {
        case IT_HEALTH:   items[i].name += "HEALTH"; break;
        case IT_WELLNESS: items[i].name += " WELLNESS"; break;
        default: break;
        }

        items[i].position = Vector2(
            static_cast<float>(rand() % 501),
            static_cast<float>(rand() % 501)
        );

        // Pass pointer to first float (x)
        itemLocations.AddItem(&items[i].position.x, &items[i]);
    }

    itemLocations.BuildTree();

    FilterByType filterCallBack;
    filterCallBack.itemType = IT_HEALTH;

    Vector2 minRange(200.0f, 200.0f);
    Vector2 maxRange(300.0f, 300.0f);

    Vector<const void*> itemsInRange;
    itemLocations.FindInRange(itemsInRange, &minRange.x, &maxRange.x, filterCallBack);

    for (auto it = itemsInRange.Begin(); it != itemsInRange.End(); ++it)
    {
        const Item* item = static_cast<const Item*>(*it);
        std::cout << "Item in range: "
            << item->name << " ("
            << item->position.x << ", "
            << item->position.y << ")\n";
    }

    std::cout << "\n";

    Vector2 targetPos(450.0f, 210.0f);
    const Item* nearest =
        static_cast<const Item*>(itemLocations.FindNearest(&targetPos.x));

    if (nearest)
    {
        std::cout << "Nearest item: "
            << nearest->name << " ("
            << nearest->position.x << ", "
            << nearest->position.y << ")\n";
    }