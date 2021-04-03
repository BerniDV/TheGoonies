#pragma once
#include "Item.h"

class Item;

class Llave : public Item
{
public:

	Llave();

	string getTipo() override;
	void update(float deltaTime) override;

private:

	
};

