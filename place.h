#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Enemy.h"
using namespace std;

class Place
{
private:
	struct Door
	{
		string dir;
		string def;
		Place* nextRoom;
		bool opened;
		string itemToOpen;
	};
	string name;
	string story;
	vector<Door> dirs;
	list<Item*> listOfItemsInPlace;
	bool enemyPresent;
	Enemy* enemyInThePlace;

public:

	//Creators

	Place();
	Place(string name);
	Place(string name, string story);
	Place(string name, string story, bool enemyPresent, Enemy* enemyInThePlace);
	~Place();

	//Consultants

	string getName() const;
	bool isItemPresent(string itemName) const;
	bool isEnemyPresent() const;
	Enemy* getEnemy() const;
	void readPlace() const;
	Item* getItemByName(string itemName) const;

	//Modifiers

	void enemyDies();
	void setDir(string dir, string def, Place* nextRoom, bool opened, string itemToOpen);
	void addItem(Item* item);
	void addEnemy(Enemy* enemy);
	void removeItem(Item* item);
	Place* goTo(string dir);
};

