#pragma once
#include <string>
using namespace std;

class Item
{
private:
	string name;
	string message;

	bool canBeTaken;
	bool canBeOpened;
	bool opened;
	bool needCode;
	string code;

	bool thereIsAnItemInside;
	Item* itemInside;
	bool insideTheItem;
	Item* outsideTheItem;

public:
	Item();
	Item(string name, string message, bool canBeTaken);
	Item(string name, string message, bool canBeTaken, bool insideTheItem, Item* outsideTheItem);
	Item(string name, string message, bool canBeTaken, bool canBeOpened, bool opened, bool theresAnItemInside, Item* itemInside, bool needCode, string code);
	~Item();

	//Consultants

	string getName() const;
	bool youCanTakeIt() const;
	bool youCanOpenIt() const;
	bool needCodeToOpen() const;
	Item* getItemInside() const;
	Item* getItemOutside() const;
	string readIt() const;
	string getMessage() const;
	bool haveAnItemInside() const;
	bool isOpened() const;
	bool isInsideTheItem() const;

	//Modifiers

	Item* takeItem();
	Item* takeOutsideItem();
	void putItem(Item* newItemInside);
	void putInsideOfTheItem(Item* newOutSideItem);
	void open();
	void close();

	bool checkCode(string code) const;
};

