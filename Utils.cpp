#include "Utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

bool Utils::winOrLose(string action, Item* playersItem, Item* enemysItem, clock_t timeSinceEnterRoom) const
{
	if (timeSinceEnterRoom>=10000)
	{
		if (enemysItem->getName()=="gun")
			cout << ">>> Shush! You are too slow, the enemy shot you." << endl;
		else
			cout << ">>> Shush! You are too slow, the enemy threw a knife at you." << endl;
		return false;
	}

	else if (playersItem==NULL)
	{
		cout << ">>> Do you really think that you can kill an armed enemy with your bare hands?" << endl;
		if (enemysItem->getName()=="gun")
        {
            cout << ">>> Of course you can't, the enemy shot you." << endl;
        }
		else
        {
            cout << ">>> Of course you can't, the enemy stabbed you." << endl;
        }
		return false;
	}

	else if (playersItem->getName()=="knife")
	{
		if (action=="throw")
		{
			cout << ">>> You threw the knife to the enemy and..." << endl;
			srand(time(NULL));
			if ((rand()%10+1)<=5)
			{
				cout << ">>> Perfect, you hit him in the heart." << endl;
				return true;
			}
			else
			{
				cout << ">>> Too bad, you missed him." << endl;
				return false;
			}
		}
		else
		{
			if (enemysItem->getName()=="gun")
			{
				cout << ">>> You tried to stab the enemy but he has a gun and shot you." << endl;
				return false;
			}
			else
			{
				cout << ">>> You ran to the enemy and stabbed him with the knife." << endl;
				return true;
			}
		}
	}
	else
	{
		if (action=="throw")
		{
			cout << ">>> Why on earth did you throw a gun to the enemy instead of shooting him???" << endl;
			if (enemysItem->getName()=="gun")
				cout << ">>> The enemy shot you." << endl;
			else
				cout << ">>> The enemy ran towards you and stabbed you." << endl;
			return false;
		}
		else
		{
			cout << ">>> You took the shot and hit him." << endl;
			return true;
		}
	}
}

InputOrder Utils::selectEnum(string s) const
{
	if (s=="go")
    {
        return InputOrder::GO;
    }
	else if (s=="take")
    {
        return InputOrder::TAKE;
    }
	else if (s=="drop")
    {
        return InputOrder::DROP;
    }
	else if (s=="inventory")
    {
        return InputOrder::INVENTORY;
    }
	else if (s=="exit")
    {
        return InputOrder::EXIT;
    }
	else if (s=="watch")
    {
        return InputOrder::WATCH;
    }
	else if (s=="read"||s=="examine")
    {
        return InputOrder::READ;
    }
	else if (s=="open")
    {
        return InputOrder::OPEN;
    }
	else if (s=="close")
    {
        return InputOrder::CLOSE;
    }
	else if (s=="equip")
    {
        return InputOrder::EQUIP;
    }
	else if (s=="unequip")
    {
        return InputOrder::UNEQUIP;
    }
	else if (s=="attack")
    {
        return InputOrder::ATTACK;
    }
	else if (s=="throw")
    {
        return InputOrder::THROW;
    }
	else if (s=="leave")
    {
        return InputOrder::LEAVE;
    }
	else
    {
        return InputOrder::UNKNOWN;
    }
}
