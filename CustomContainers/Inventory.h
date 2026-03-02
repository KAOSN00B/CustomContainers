#pragma once

#include <iostream>
#include <string>

#include "Map.h"
#include "Vector.h"
#include "KeyItem.h"
class Inventory
{
private:
    Map<std::string, KeyItem> mKeys;

    Inventory() {}  // private constructor

public:
    static Inventory& Get()
    {
        static Inventory instance; // created once
        return instance;
    }

    void PickupKey(const std::string& keyName, int amount)
    {
        KeyItem item;

        if (mKeys.Find(keyName, item))
        {
            item.Add(amount);
            mKeys.Insert(keyName, item);
        }
        else
        {
            KeyItem newItem(keyName, amount);
            mKeys.Insert(keyName, newItem);
        }
    }

    bool UseKey(const std::string& keyName, int amount)
    {
        KeyItem item;

        if (!mKeys.Find(keyName, item))
            return false;

        if (item.GetCount() < amount)
            return false;

        item.Consume(amount);

        if (item.GetCount() == 0)
            mKeys.Remove(keyName);
        else
            mKeys.Insert(keyName, item);

        return true;
    }

    void PrintInventory()
    {
        Vector<std::string> keys;
        mKeys.ObtainKeys(keys);

        for (size_t i = 0; i < keys.Size(); ++i)
        {
            KeyItem item;
            mKeys.Find(keys[i], item);
            item.Print();
        }
    }
};