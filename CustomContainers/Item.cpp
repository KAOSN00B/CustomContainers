#include "Item.h"

Item::Item(ItemType itemType, int value) //Constructor 
	: mType(itemType), mValue(value), mCount(0)
{
	switch (mType)
	{
	case SmallHealth: mName = "Small Health"; break;
	case MedHealth: mName = "Med Health"; break;
	case LightningSpell:  mName = "Lightning Spell"; break;
	case Grenade:  mName = "Grenade"; break;
	case Bomb:  mName = "Bomb"; break;
	case Shield:  mName = "Shield"; break;
	}
}

void Item::AddItem()
{
	mCount++;
	std::cout << "Added " << mName << " (x" << mCount << ")\n";
}

void Item::ConsumeItem()
{

	if (mCount > 0)
	{
		mCount--;
		std::cout << "Used " << mName << " (" << mValue << ")\n";
	}
	else
	{
		std::cout << "No " << mName << " left!\n";
	}

}
