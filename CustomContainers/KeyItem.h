#pragma once
#include <iostream>
#include <string>

class KeyItem
{
private:
    std::string mName;
    int mCount = 0;

public:
    KeyItem() = default;

    KeyItem(const std::string& name, int count = 0)
        : mName(name), mCount(count)
    {
    }

    void Add(int amount)
    {
        mCount += amount;
    }

    void Consume(int amount)
    {
        mCount -= amount;
        if (mCount < 0)
            mCount = 0;
    }

    int GetCount() const
    {
        return mCount;
    }

    const std::string& GetName() const
    {
        return mName;
    }

    void Print() const
    {
        std::cout << mName << ": " << mCount << "\n";
    }
};