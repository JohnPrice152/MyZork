#include "place.h"

Place::Place()
{
	name="unknown";
	story="";
	enemyPresent=false;
	enemyInThePlace=NULL;
}

Place::Place(string name)
{
	this->name=name;
	story="";
	enemyPresent=false;
	enemyInThePlace=NULL;
}

Place::Place(string name, string story)
{
	this->name=name;
	this->story=story;
	enemyPresent=false;
	enemyInThePlace=NULL;
}

Place::Place(string name, string story, bool enemyPresent, Enemy* enemyInThePlace)
{
	this->name=name;
	this->story=story;
	this->enemyPresent=enemyPresent;
	this->enemyInThePlace=enemyInThePlace;
}

Place::~Place()
{
}

string Place::getName() const
{
	return name;
}

void Place::setDir(string dir, string def, Place* nextRoom, bool opened, string itemToOpen)
{
	Door door={dir, def, nextRoom, opened, itemToOpen};
	dirs.push_back(door);
}

Place* Place::goTo(string dir)
{
	for (int i=0; i<dirs.size(); i++)
	{
		if (dir==dirs[i].dir)
		{
			return dirs[i].nextRoom;
		}
	}
	return NULL;
}

void Place::readPlace() const
{
	cout << ">>> " << story << endl;
	for (int i=0; i<dirs.size(); i++)
	{
		if (dirs[i].dir=="up"||dirs[i].dir=="down")
        {
            cout << ">>> You can see " << dirs[i].def << " going " << dirs[i].dir << ". ";
        }
		else
        {
            cout << ">>> At the " << dirs[i].dir << " you can see " << dirs[i].def << ". ";
        }
		if (!dirs[i].opened)
        {
            cout << ">>> It seems that the door is closed.";
        }
		cout << endl;
	}
	if (!listOfItemsInPlace.empty())
	{
		cout << ">>> You can see: " << endl;
		for (std::list<Item*>::const_iterator it=listOfItemsInPlace.begin(); it!=listOfItemsInPlace.end(); it++)
		{
			if ((*it)->isInsideTheItem())
            {
                cout << ">>> A " << (*it)->getName() << " is inside a " << (*it)->getItemOutside()->getName() << endl;
            }
			else if ((*it)->youCanOpenIt() &(*it)->isOpened())
            {
                cout << ">>> An open " << (*it)->getName() << endl;
            }
			else if ((*it)->youCanOpenIt()&&!(*it)->isOpened())
            {
                cout << ">>> A closed " << (*it)->getName() << endl;
            }
			else
            {
                cout << ">>> A " << (*it)->getName() << endl;
            }
		}
		cout << endl;
	}
	if (enemyPresent)
	{
		cout << ">>> CAUTION: There is also an enemy in the room!" << endl;
		if (enemyInThePlace->getItemEquipped()->getName()=="knife")
		{
			cout << ">>> Careful, he has a knife!" << endl;
		}
		if (enemyInThePlace->getItemEquipped()->getName()=="gun")
		{
			cout << ">>> He has a gun, and he is pointing it to you! Do something, QUICK!" << endl;
		}
	}
}

void Place::addItem(Item* item)
{
	listOfItemsInPlace.push_back(item);
}

void Place::removeItem(Item* item)
{
	listOfItemsInPlace.remove(item);
}

bool Place::isItemPresent(string itemName) const
{
	for (std::list<Item*>::const_iterator it=listOfItemsInPlace.begin(); it!=listOfItemsInPlace.end(); it++)
	{
		if ((*it)->getName()==itemName)
        {
            return true;
        }
	}
	return false;
}

void Place::addEnemy(Enemy* enemy)
{
	enemyPresent=true;
	enemyInThePlace=enemy;
}

void Place::enemyDies()
{
	listOfItemsInPlace.push_back(enemyInThePlace->getItemEquipped());
	enemyPresent=false;
	enemyInThePlace=NULL;
}

bool Place::isEnemyPresent() const
{
	return enemyPresent;
}

Enemy* Place::getEnemy() const
{
	return enemyInThePlace;
}

Item* Place::getItemByName(string itemName) const
{
	for (std::list<Item*>::const_iterator it=listOfItemsInPlace.begin(); it!=listOfItemsInPlace.end(); it++)
	{
		if ((*it)->getName()==itemName)
        {
            return (*it);
        }
	}
	return NULL;
}
