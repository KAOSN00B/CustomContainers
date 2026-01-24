#pragma once
#include "Item.h"
#include "Vector.h"

class Inventory
{
public:
	Vector<Item> items;

	void Initialize();
	void AddItem(ItemType itemType);
	void DisplayItems();
};