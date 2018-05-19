#include "Enemy.h"

Enemy::Enemy()
{
	equippedItem=NULL;
}

Enemy::Enemy(Item* itemEquiped)
{
	this->itemEquipped=itemEquipped;
}

Enemy::~Enemy()
{

}

Item* Enemy::getItemEquipped() const
{
	return itemEquipped;
}

void Enemy::setItemEquipped(Item* itemEquipped)
{
	this->itemEquipped=itemEquipped;
}
