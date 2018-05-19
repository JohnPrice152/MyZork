#include "Player.h"

Player::Player()
{
	equippedItem=NULL;
}

Player::Player(Place* actualPlace)
{
	this->actualPlace=actualPlace;
	equippedItem=NULL;
}

Player::~Player()
{
}


Place* Player::getActualPlace() const
{
	return actualPlace;
}

void Player::setActualPlace(Place* actualPlace)
{
	this->actualPlace=actualPlace;
}

void Player::addItem(Item* item)
{
	inventoryList.push_back(item);
}

void Player::removeItem(Item* item)
{
	inventoryList.remove(item);
}

void Player::readInventory() const
{
	if (inventoryList.size() == 0)
    {
        cout << ">>> You don't have any item in your inventory" << endl;
    }
	else
	{
		cout << ">>> The items you have in your inventory: " << endl;
		for (std::list<Item*>::const_iterator it=inventoryList.begin(); it!=inventoryList.end(); it++)
		{
			cout << ">>> " << (*it)->getName() << endl;
		}
	}
}

bool Player::checkInventory(string itemName) const
{
	for (std::list<Item*>::const_iterator it=inventoryList.begin(); it!=inventoryList.end(); it++)
	{
		if ((*it)->getName()==itemName)
        {
            return true;
        }
	}
	return false;
}

void Player::readItem(string itemName) const
{
	for (std::list<Item*>::const_iterator it=inventoryList.begin(); it!=inventoryList.end(); it++)
	{
		if ((*it)->getName()==itemName)
		{
			cout << ">>> " << (*it)->readIt() << endl;
			return;
		}
	}
	cout << ">>> You don't have this item in your inventory!" << endl;
}


void Player::equipItem(const string itemName)
{
	if (itemName != "gun" && itemName != "knife") cout << "<-- This item can't be equiped" << endl;
	else {
		for (std::list<Item*>::iterator it = inventoryList.begin(); it != inventoryList.end(); ++it)
		{
			if ((*it)->getName() == itemName)
			{
				equippedItem = (*it);
				cout << "<-- You have equiped a " << itemName << "." << endl;
				return;
			}
		}
		cout << "<-- You don't have this item in the inventory." << endl;
	}
}

void Player::unequipItem()
{
	if (equippedItem==NULL)
		cout << ">>> You don't equip anything!" << endl;
	else
	{
		cout << ">>> " << equippedItem->getName() << " unequipped." << endl;
		equippedItem=NULL;
	}
}

Item* Player::getItemEquipped() const
{
	return equippedItem;
}

Item* Player::getItemByName(string itemName) const
{
	for (std::list<Item*>::const_iterator it=inventoryList.begin(); it!=inventoryList.end(); it++)
	{
		if ((*it)->getName()==itemName)
        {
            return (*it);
        }
	}
	return NULL;
}
