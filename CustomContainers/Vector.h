#pragma once

#include <cstddef>
#include <algorithm>
#include <cassert>
#include "ContainerIterator.h"

template<typename T>
class Vector
{
public:
    Vector()
        : mValues(nullptr)
        , mCapacity(0)
        , mSize(0)
    {
    }

    ~Vector()
    {
        delete[] mValues;
        mValues = nullptr;
        mCapacity = 0;
        mSize = 0;
    }

    // Copy constructor
    Vector(const Vector& other)
        : mValues(nullptr)
        , mCapacity(0)
        , mSize(0)
    {
        if (other.mCapacity > 0)
        {
            mValues = new T[other.mCapacity];
            for (std::size_t i = 0; i < other.mCapacity; ++i)
                mValues[i] = other.mValues[i];
        }

        mSize = other.mSize;
        mCapacity = other.mCapacity;
    }

    // Move constructor
    Vector(Vector&& other)
        : mValues(other.mValues)
        , mCapacity(other.mCapacity)
        , mSize(other.mSize)
    {
        other.mValues = nullptr;
        other.mCapacity = 0;
        other.mSize = 0;
    }

    // Copy assignment
    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            delete[] mValues;
            mValues = nullptr;

            if (other.mCapacity > 0)
            {
                mValues = new T[other.mCapacity];
                for (std::size_t i = 0; i < other.mCapacity; ++i)
                    mValues[i] = other.mValues[i];
            }

            mSize = other.mSize;
            mCapacity = other.mCapacity;
        }
        return *this;
    }

    // Move assignment
    Vector& operator=(Vector&& other)
    {
        if (this != &other)
        {
            delete[] mValues;

            mValues = other.mValues;
            mSize = other.mSize;
            mCapacity = other.mCapacity;

            other.mValues = nullptr;
            other.mSize = 0;
            other.mCapacity = 0;
        }
        return *this;
    }

    // Reserve capacity
    void Reserve(std::size_t capacity)
    {
        if (capacity > mCapacity)
        {
            T* newValues = new T[capacity];

            for (std::size_t i = 0; i < mSize; ++i)
                newValues[i] = mValues[i];

            delete[] mValues;
            mValues = newValues;
            mCapacity = capacity;
        }
    }

    // Resize vector
    void Resize(std::size_t size, const T& initValue = T())
    {
        if (size == mSize)
            return;

        if (size < mSize)
        {
            for (std::size_t i = size; i < mSize; ++i)
                mValues[i].~T();
        }
        else
        {
            std::size_t newCapacity = std::max(size, mCapacity * 2);
            Reserve(newCapacity);

            for (std::size_t i = mSize; i < size; ++i)
                mValues[i] = initValue;
        }

        mSize = size;
    }

    void Clear()
    {
        Resize(0);
    }

    std::size_t Size() const { return mSize; }
    std::size_t Capacity() const { return mCapacity; }

    void PushBack(const T& value)
    {
        if (mSize >= mCapacity)
        {
            std::size_t newCapacity = (mCapacity == 0) ? 10 : mCapacity * 2;
            Reserve(newCapacity);
        }

        mValues[mSize++] = value;
    }

    void PopBack()
    {
        assert(mSize > 0);
        Resize(mSize - 1);
    }

	// just adding to have a function queue, not normally in a vector
    void PopFront()
    {
        assert(mSize > 0);

        for (std::size_t i = 0; i < mSize - 1; ++i)
        {
            mValues[i] = mValues[i + 1];
        }

        --mSize;
    }


    T& operator[](std::size_t index)
    {
        assert(index < mSize);
        return mValues[index];
    }

    const T& operator[](std::size_t index) const
    {
        assert(index < mSize);
        return mValues[index];
    }

    // Iterator section
    using Iterator = ContainerIterator<T>;
    using Const_Iterator = ContainerIterator<const T>;

    Iterator Begin() { return Iterator(mValues); }
    Iterator End() { return Iterator(mValues + mSize); }

    Const_Iterator Begin() const { return Const_Iterator(mValues); }
    Const_Iterator End() const { return Const_Iterator(mValues + mSize); }

private:
    T* mValues;
    std::size_t mCapacity;
    std::size_t mSize;
};
