#pragma once
#include "Entity.h"
#include "Place.h"

class Player: public Entity
{
private:
	list<Item*> inventoryList;
	Place* actualPlace;

public:

	//Creators
	Player();
	Player(Place* actualPlace);
	~Player();

	//Consultants

	Place* getActualPlace() const;
	bool checkInventory(string itemName) const;
	Item* getItemEquipped() const;
	Item* getItemByName(string itemName) const;
	void readItem(string itemName) const;
	void readInventory() const;

	//Modifiers
	void setActualPlace(Place* actualPlace);
	void addItem(Item* item);
	void removeItem(Item* item);
	void equipItem(string itemName);
	void unequipItem();
};

