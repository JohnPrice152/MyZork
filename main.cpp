#include <iostream>
#include <string>
#include "World.h"

using namespace std;

int main()
{
	//Presentation
	cout << "*     *   *     *     *******    *****     *****    *     *" << endl
         << "**   **    *   *           *    *     *   *     *   *   *  " << endl
         << "* * * *     * *           *     *     *   *     *   * *    " << endl
         << "*  *  *      *           *      *     *   ******    *      " << endl
         << "*     *      *          *       *     *   * *       * *    " << endl
         << "*     *      *         *        *     *   *   *     *   *  " << endl
         << "*     *      *        *******    *****    *     *   *     *" << endl;
	cout << "Welcome to my Zork!" << endl;
	cout << "__________________" << endl;
	cout << endl;

	//Init the world where we are going to play
	Utils utils;
	World world;
	world.Init();

	string input;

	while (1) {
		cin >> input;
		//Execute a iteration of the game loop
		int instruction = world.Iteration(utils.selectEnum(input));
		//End game
		if (instruction==2)
			return 0;
		//Restart game because the player is dead
		else if (instruction == 1)
		{
			cout << endl;
			cout << endl;
			cout << endl;
			world.Init();
		}
	}
}
