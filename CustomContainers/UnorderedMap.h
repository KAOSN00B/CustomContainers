#pragma once
#include <vector>
#include <functional>
#include <algorithm>

template<typename KeyType, typename ValueType>
class UnorderedMap
{
private:
    struct KeyValuePair
    {
        KeyType key;
        ValueType value;
    };

public:

    UnorderedMap(std::size_t initialBucketSize = 8, double loadFactor = .8)
        : _bucketCount(std::max(initialBucketSize, static_cast<std::size_t>(1))),
        _loadFactorThreshold(loadFactor),
        _count(0)
    {
        _table.resize(_bucketCount);
    }

    // No copying (owning raw pointers)
    UnorderedMap(const UnorderedMap&) = delete;
    UnorderedMap& operator=(const UnorderedMap&) = delete;
    UnorderedMap(UnorderedMap&&) = delete;
    UnorderedMap& operator=(UnorderedMap&&) = delete;

    ~UnorderedMap()
    {
        Clear();
    }

    void Insert(const KeyType& key, const ValueType& value)
    {
        std::size_t index = GetTableIndex(key);

        for (KeyValuePair* kv : _table[index])
        {
            if (kv->key == key)
            {
                kv->value = value;
                return;
            }
        }

        KeyValuePair* kv = new KeyValuePair{ key, value };
        _table[index].push_back(kv);
        ++_count;

        if ((double)_count / (double)_bucketCount > _loadFactorThreshold)
        {
            Rehash();
        }
    }

    bool Find(const KeyType& key, ValueType& outValue) const
    {
        std::size_t index = GetTableIndex(key);

        for (const KeyValuePair* kv : _table[index])
        {
            if (kv->key == key)
            {
                outValue = kv->value;
                return true;
            }
        }

        return false;
    }

    bool Has(const KeyType& key) const
    {
        std::size_t index = GetTableIndex(key);

        for (const KeyValuePair* kv : _table[index])
        {
            if (kv->key == key)
            {
                return true;
            }
        }

        return false;
    }

    bool Remove(const KeyType& key)
    {
        std::size_t index = GetTableIndex(key);
        auto& bucket = _table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if ((*it)->key == key)
            {
                delete* it;
                bucket.erase(it);
                --_count;
                return true;
            }
        }

        return false;
    }

    std::size_t GetCount() const
    {
        return _count;
    }

    void Clear()
    {
        for (auto& bucket : _table)
        {
            for (KeyValuePair* kv : bucket)
            {
                delete kv;
            }
            bucket.clear();
        }

        _count = 0;
    }

    ValueType& operator[](const KeyType& key)
    {
        std::size_t index = GetTableIndex(key);

        for (KeyValuePair* kv : _table[index])
        {
            if (kv->key == key)
            {
                return kv->value;
            }
        }

        KeyValuePair* kv = new KeyValuePair{ key, _default };
        _table[index].push_back(kv);
        ++_count;

        if ((double)_count / (double)_bucketCount > _loadFactorThreshold)
        {
            Rehash();
        }

        return kv->value;
    }

    const ValueType& operator[](const KeyType& key) const
    {
        std::size_t index = GetTableIndex(key);

        for (const KeyValuePair* kv : _table[index])
        {
            if (kv->key == key)
            {
                return kv->value;
            }
        }

        return _default;
    }

private:

	ValueType _default;
	// Table is main Vector, "Bucket" is vector of objects using same index
	std::vector<std::vector<KeyValuePair*>> _table;
	// max indices the table can use to store individual values
	std::size_t _bucketCount = 0;
	// total number of items in the table
	std::size_t _count = 0;
	// how many items in a buck before we need to resize table
	double _loadFactorThreshold = 1.0;
	// using this one because it is dynamic. gives a hash value from whatever we use as a key
	std::hash<KeyType> _hashFunction;

	// gives the index in the table that the item will be placed
	// due to the hash value obtained with the key
	std::size_t GetTableIndex(const KeyType& key) const
	{
		return _hashFunction(key) % _bucketCount;
	}

	void Rehash()
	{
		std::size_t newBucketCount = _bucketCount * 2;
		std::vector<std::vector<KeyValuePair*>> newTable(newBucketCount);

		for (auto& bucket : _table)
		{
			for (KeyValuePair* kv : bucket)
			{
				std::size_t newIndex = _hashFunction(kv->key) % newBucketCount;
				newTable[newIndex].push_back(kv);
			}
		}

		_table.swap(newTable);
		_bucketCount = newBucketCount;
	}

};