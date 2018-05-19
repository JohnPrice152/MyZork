#include "Item.h"

Item::Item()
{
	name="",
	message="";
	canBeTaken=false;
	canBeOpened=false;
	needCode=false;
	code="";
	thereIsAnItemInside=false;
	itemInside=NULL;
	insideTheItem=false;
	outsideTheItem=NULL;
	opened=false;
}

Item::Item(string name, string message, bool canBeTaken)
{
	this->name=name,
	this->message=message;
	this->canBeTaken=canBeTaken;
	canBeOpened=false;
	needCode=false;
	code="";
	thereIsAnItemInside=false;
	itemInside=NULL;
	insideTheItem=false;
	outsideTheItem=NULL;
	opened=false;
}

Item::Item(string name, string message, bool canBeTaken, bool canBeOpened, bool opened, bool theresAnItemInside, Item* itemInside, bool needCode, string code)
{
	this->name=name,
	this->message=message;
	this->canBeTaken=canBeTaken;
	this->canBeOpened=canBeOpened;
	this->opened=opened;
	this->thereIsAnItemInside=thereIsAnItemInside;
	this->itemInside=itemInside;
	this->needCode=needCode;
	this->code=code;
	insideTheItem=false;
	outsideTheItem=NULL;
}

Item::Item(string name, string message, bool canBeTaken, bool insideTheItem, Item* outsideTheItem)
{
	this->name=name,
	this->message=message;
	this->canBeTaken=canBeTaken;
	this->insideTheItem=insideTheItem;
	this->outsideTheItem=outsideTheItem;
	code="";
	canBeOpened=false;
	needCode=false;
	itemInside=NULL;
	thereIsAnItemInside=true;
	opened=false;
}

Item::~Item()
{

}

string Item::getName() const
{
	return name;
}

bool Item::youCanTakeIt() const
{
	return canBeTaken;
}

string Item::readIt() const
{
	return message;
}

bool Item::youCanOpenIt() const
{
	return canBeOpened;
}

Item* Item::getItemInside() const
{
	return itemInside;
}

bool Item::needCodeToOpen() const
{
	return needCode;
}

bool Item::checkCode(string code) const
{
	return this->code==code;
}

string Item::getMessage() const
{
	return message;
}

Item* Item::takeItem()
{
	Item* aux=itemInside;
	itemInside=NULL;
	thereIsAnItemInside=false;
	return aux;
}

bool Item::haveAnItemInside() const
{
	return thereIsAnItemInside;
}

void Item::putItem(Item* newItemInside)
{
	thereIsAnItemInside = true;
	itemInside=newItemInside;
}

void Item::putInsideOfTheItem(Item* newOutSideTheItem)
{
	insideTheItem=true;
	outsideTheItem=newOutSideTheItem;
}

bool Item::isInsideTheItem() const
{
	return insideTheItem;
}

Item* Item::takeOutsideItem()
{
	Item* aux=outsideTheItem;
	outsideTheItem=NULL;
	insideTheItem=false;
	return aux;
}

Item* Item::getItemOutside() const
{
	return outsideTheItem;
}

bool Item::isOpened() const
{
	return opened;
}

void Item::open()
{
	opened=true;
}

void Item::close()
{
	opened=false;
}
