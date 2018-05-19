#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::Init()
{
	//Create new player
	player=Player();

	//Create new enemies
	enemy1=Enemy();
	enemy2=Enemy();

	//Create rooms
	cell=Place("The Cell", "You are a prisoner of the militia and you woke up in the middle of the night in your cell.");
	corridor=Place("The Corridor", "You are in a corridor with a lot of cells and prisoners sleeping in them. You'd better escape in silence.");
	controlRoom=Place("The Control Room", "You are in the control room, the place where the guards control the prisoners and spend their free time.");
	armory=Place("The Armory", "You are in the armory, which has a lot of guns. Unfortunately, you can't find any ammunition here.");
	corridorUp=Place("The Upper Corridor", "You are in the last corridor of the prison, you have the escape route right in front of you.");
	exit=Place("Outside", "Congratulations, you escaped the prison! A woman is waiting for you with a car, enjoy your life.");

	//Create items
	note=Item("note", "You should open your cell, run and get out of here before they discover your plan!", true);
	paper=Item("piece of paper", "The exit is upstairs but there is an armed guy there. You'd better go to the west and arm yourself properly. Take care, there is also another guy there but he only has a knife.", true);
	knife=Item("knife", "Be fast or die. You can throw me to the enemy but you can't miss.", true);
	gun=Item("gun", "Be fast or die.", true);
	vault=Item("vault", "Input your code (XX-XX-XX) to open the vault. Clue: 01-01-02-03-05-08-...", false, true, false, true, &paper, true, "13-21-34");
	vault2=Item("vault", "Input your code (XXXX) to open the vault. Clue: 3.1415...", false, true, false, true, &gun, true, "9265");
	knifeEnemy=Item("knife", "Be fast or die. You can throw me to the enemy but you can't miss.", true);
	gunEnemy=Item("gun", "Be fast or die.", true);

	gun.putInsideOfTheItem(&vault2);
	paper.putInsideOfTheItem(&vault);

	//Filling rooms

	cell.setDir("north", "a door", &corridor, true, "");
	corridor.setDir("south", "a door", &cell, true, "");

	corridor.setDir("north", "a door", &controlRoom, true, "");
	controlRoom.setDir("south", "a door", &corridor, true, "");

	controlRoom.setDir("up", "stairs", &corridorUp, true, "");
	corridorUp.setDir("down", "stairs", &controlRoom, true, "");

	controlRoom.setDir("west", "a door", &armory, true, "");
	armory.setDir("east", "a door", &controlRoom, true, "");

	corridorUp.setDir("up", "stairs", &exit, true, "");

	enemy1.setItemEquipped(&knifeEnemy);
	enemy2.setItemEquipped(&gunEnemy);

	cell.addItem(&note);
	controlRoom.addItem(&knife);
	controlRoom.addItem(&vault);
	armory.addItem(&vault2);

	armory.addEnemy(&enemy1);
	corridorUp.addEnemy(&enemy2);

	player.setActualPlace(&cell);

	timeWhenYouEnter=0;
	enemyPresentInTheRoom=false;

	player.getActualPlace()->readPlace();
}

int World::Iteration(InputOrder io)
{
	string input;

	switch (io)
	{
	case InputOrder::EXIT:
		return 2;
		break;

	case InputOrder::GO:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << ">>> You can't do that, there is an enemy in the room!" << endl;
		}
		else if (player.getActualPlace()->goTo(input)!=NULL)
		{
			player.setActualPlace(player.getActualPlace()->goTo(input));
			player.getActualPlace()->readPlace();

			if (player.getActualPlace()->getName()=="outside")
			{
				cout << ">>> What do you wanna do now? Type 'restart' to play again or 'end' to close the game." << endl;
				while (1)
				{
					cin >> input;
					if (input=="restart")
						return 1;
					else if (input=="end")
						return 2;
				}
			}
			if (player.getActualPlace()->isEnemyPresent())
			{
				enemyPresentInTheRoom=true;
				timeWhenYouEnter=clock();
			}
			else
			{
				enemyPresentInTheRoom=false;
			}
		}
		else {
			cout << ">>> You can't go in that direction." << endl;
		}
		cout << endl;
		break;

	case InputOrder::TAKE:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << ">>> You can't do that, there is an enemy in the room!" << endl;
		}
		else if (player.getActualPlace()->isItemPresent(input))
		{
			Item* itemYouWantToTake=player.getActualPlace()->getItemByName(input);

			if (itemYouWantToTake->youCanTakeIt())
			{
				if (player.checkInventory(itemYouWantToTake->getName()))
					cout << ">>> You already have the same item in your inventory." << endl;
				else
				{
					if (itemYouWantToTake->isInsideTheItem())
                    {
						itemYouWantToTake->getItemOutside()->takeItem();
						itemYouWantToTake->takeOutsideItem();
					}
					player.getActualPlace()->removeItem(itemYouWantToTake);
					player.addItem(itemYouWantToTake);
					cout << ">>> " << input << " taken." << endl;
				}
			}
			else
			{
				cout << ">>> This item can't be removed." << endl;
			}
		}
		else
		{
			cout << ">>> This item can't be found in this place." << endl;
		}
		cout << endl;
		break;

	case InputOrder::DROP:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << ">>> You can't do that, there is an enemy in the room!" << endl;
		}
		else if ((player.checkInventory(input) &player.getItemEquipped()==NULL)||(player.checkInventory(input)&&player.getItemEquipped()->getName()!=input))
		{
			Item* itemYouWantToTake=player.getItemByName(input);

			player.removeItem(itemYouWantToTake);
			player.getActualPlace()->addItem(itemYouWantToTake);
			cout << ">>> " << input << " dropped." << endl;
		}
		else if (player.getItemEquipped()==NULL||player.getItemEquipped()->getName()!=input)
        {
            cout << ">>> You don't have this item." << endl;
        }
		else
		{
			cout << ">>> You can't drop an item if it is equipped." << endl;
		}
		cout << endl;
		break;

	case InputOrder::INVENTORY:
		player.readInventory();
		cout << endl;
		break;

	case InputOrder::WATCH:
		player.getActualPlace()->readPlace();
		break;

	case InputOrder::READ:
		cin >> input;
		player.readItem(input);
		cout << endl;
		break;

	case InputOrder::OPEN:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << ">>> You can't do that, there is an enemy in the room!" << endl;
		}
		else if (player.getActualPlace()->isItemPresent(input))
		{
			Item* itemYouWantToOpen=player.getActualPlace()->getItemByName(input);

			if (itemYouWantToOpen->isOpened())
				cout << ">>> The item is already opened" << endl;
			else
			{
				bool opened=false;
				if (itemYouWantToOpen->needCodeToOpen())
				{
					cout << itemYouWantToOpen->getMessage() << endl;
					string codeByUser;
					cin >> codeByUser;
					if (itemYouWantToOpen->checkCode(codeByUser))
						opened=true;
				}
				else
					opened=true;
				if (opened)
				{
					itemYouWantToOpen->open();
					if (itemYouWantToOpen->haveAnItemInside())
					{
						player.getActualPlace()->addItem(itemYouWantToOpen->getItemInside());
						cout << ">>> " << input << " opened. Inside it you can see a " << itemYouWantToOpen->getItemInside()->getName() << "." << endl;
					}
					else
					{
						cout << ">>> " << input << " opened. There's nothing inside." << endl;
					}
				}
				else
					cout << ">>> Wrong code." << endl;
			}
		}
		else
			cout << ">>> You can't open an item that isn't in this place." << endl;
		cout << endl;
		break;

	case InputOrder::CLOSE:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << ">>> You can't do that, there is an enemy in the room!" << endl;
		}
		else if (player.getActualPlace()->isItemPresent(input))
		{
			Item* itemYouWantToClose=player.getActualPlace()->getItemByName(input);

			if (!itemYouWantToClose->youCanOpenIt())
            {
                cout << ">>> You can't open/close that item" << endl;
            }
			else if (!itemYouWantToClose->isOpened())
            {
                cout << ">>> The item is already closed" << endl;
            }
			else
			{
				if (itemYouWantToClose->haveAnItemInside())
				{
					player.getActualPlace()->removeItem(itemYouWantToClose->getItemInside());
				}
				itemYouWantToClose->close();
				cout << ">>> " << itemYouWantToClose->getName() << " closed." << endl;
			}
		}
		else
			cout << ">>> You can't close an item that isn't in this place." << endl;
		cout << endl;
		break;

	case InputOrder::EQUIP:
		cin >> input;
		player.equipItem(input);
		cout << endl;
		break;

	case InputOrder::UNEQUIP:
		player.unequipItem();
		cout << endl;
		break;

	case InputOrder::ATTACK:
		if (enemyPresentInTheRoom)
		{
			if (utils.winOrLose("attack", player.getItemEquipped(), player.getActualPlace()->getEnemy()->getItemEquipped(), clock()-timeWhenYouEnter))
            {
				Item* dropItem=player.getActualPlace()->getEnemy()->getItemEquipped();
				enemyPresentInTheRoom=false;
				player.getActualPlace()->enemyDies();
				cout << ">>> Congratulations, you killed the enemy!" << endl;
				cout << ">>> Enemy is dead, he dropped a " << dropItem->getName() << "." << endl;
			}
			else
			{
				cout << ">>> You are dead, type 'restart' if you wanna play again or 'end' if you wanna close the game." << endl;
				while (1)
				{
					cin >> input;
					if (input=="restart")
						return 1;
					else if (input=="end")
						return 2;
				}
			}
		}
		else
		{
			cout << ">>> You can't attack if there is no one in the room" << endl;
		}
		cout << endl;
		break;

	case InputOrder::THROW:
		if (enemyPresentInTheRoom)
		{
			if (utils.winOrLose("throw", player.getItemEquipped(), player.getActualPlace()->getEnemy()->getItemEquipped(), clock()-timeWhenYouEnter)) {
				Item* dropItem=player.getActualPlace()->getEnemy()->getItemEquipped();
				enemyPresentInTheRoom=false;
				player.getActualPlace()->enemyDies();
				cout << ">>> Congratulations, you killed the enemy!" << endl;
				cout << ">>> Enemy dead, he dropped a " << dropItem->getName() << "." << endl;
			}
			else
			{
				cout << ">>> You are dead, type 'restart' if you wanna play again or 'end' if you wanna close the game." << endl;
				while (1)
				{
					cin >> input;
					if (input=="restart")
						return 1;
					else if (input=="end")
						return 2;
				}
			}
		}
		else
		{
			cout << ">>> You can't attack if there is no one in the room." << endl;
		}
		cout << endl;
		break;

	case InputOrder::LEAVE:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cin >> input;
			cin >> input;
			cout << ">>> You can't do that, there is an enemy in the room!" << endl;
		}
		else if ((player.checkInventory(input) && player.getItemEquipped()==NULL)||(player.checkInventory(input)&&player.getItemEquipped()->getName()!=input))
		{
			Item* itemToLeave=player.getItemByName(input);
			cin >> input;
			if (input=="inside")
			{
				cin >> input;
				Item* itemWhereLeave=player.getActualPlace()->getItemByName(input);

				if (!itemWhereLeave->youCanOpenIt())
                {
                    cout << ">>> You can't leave the item inside the " << itemWhereLeave->getName() << "." << endl;
                }
				else if (!itemWhereLeave->isOpened())
                {
                    cout << ">>> The " << itemWhereLeave->getName() << " is closed." << endl;
                }
				else if (itemWhereLeave->haveAnItemInside())
                {
                    cout << ">>> The " << itemWhereLeave->getName() << " already have an item inside!" << endl;
                }
				else
				{
					itemToLeave->putInsideOfTheItem(itemWhereLeave);
					itemWhereLeave->putItem(itemToLeave);
					player.getActualPlace()->addItem(itemToLeave);
					player.removeItem(itemToLeave);
					cout << ">>> You left the " << itemToLeave->getName() << " inside the " << itemWhereLeave->getName() << endl;
				}
			}
		}
		else if (player.getItemEquipped()==NULL||player.getItemEquipped()->getName()!=input)
		{
			cin >> input;
			cin >> input;
			cout << ">>> You don't have this item." << endl;
		}
		else
		{
			cin >> input;
			cin >> input;
			cout << ">>> You can't drop the item if it is equipped." << endl;
		}
		cout << endl;
		break;

	default:
		cin >> input;
		cout << ">>> I don't understand your command." << endl;
		cout << endl;
		break;
	}
	return 0;
}
