#pragma once
#include "Entity.h"

class Enemy: public Entity
{
private:
	Item* itemEquipped;
public:
	Enemy();
	Enemy(Item* itemEquipped);
	~Enemy();

	Item* getItemEquipped() const;
	void setItemEquipped(Item* itemEquipped);
};

