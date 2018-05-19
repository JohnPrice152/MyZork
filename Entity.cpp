#include "Entity.h"

Entity::Entity()
{
	equippedItem=NULL;
}

Entity::Entity(Item* equipedItem)
{
	this->equippedItem=equipedItem;
}

Entity::~Entity()
{

}
