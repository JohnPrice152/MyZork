#pragma once
#include "Item.h"

class Entity
{
protected:
	Item* equippedItem;

public:
	Entity();
	Entity(Item* equippedItem);
	virtual ~Entity();
};

