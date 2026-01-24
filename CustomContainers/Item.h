#pragma once
#include <iostream>
#include "ItemType.h"


class Item
{
public:
    ItemType mType;
    std::string mName;
    int mValue;
    int mCount;

    Item()
        : mType(SmallHealth), mName(""), mValue(0), mCount(0) {}

    Item(ItemType itemType, int value);

    void AddItem();
    void ConsumeItem();

    bool operator>(const Item& other) const
    {
        return mCount > other.mCount;
    }
};

