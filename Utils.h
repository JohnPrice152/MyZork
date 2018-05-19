#pragma once
#include <iostream>
#include "Item.h"
#include <time.h>
#include <stdlib.h>

enum class InputOrder
{
    GO,
    TAKE,
    DROP,
    INVENTORY,
    EXIT,
    WATCH,
    READ,
    OPEN,
    CLOSE,
    EQUIP,
    UNEQUIP,
    ATTACK,
    THROW,
    LEAVE,
    UNKNOWN
};

class Utils
{
public:
	Utils();
	~Utils();
	bool winOrLose(string action, Item* playersItem, Item* enemysItem, clock_t timeSinceEnterRoom) const;
	InputOrder selectEnum(string s) const;
};

