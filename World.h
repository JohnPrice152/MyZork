#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include <time.h>
#include "Utils.h"

class World
{
private:
	Player player;
	clock_t timeWhenYouEnter;
	bool enemyPresentInTheRoom;
	Utils utils;
	Enemy enemy1, enemy2;
	Place cell, corridor, controlRoom, armory, corridorUp, exit;
	Item note, paper, knife, gun, vault, vault2, knifeEnemy, gunEnemy;

public:
	World();
	~World();

	void Init();
	//0 if normal, 1 if restart, 2 if end
	int Iteration(InputOrder io);

};

