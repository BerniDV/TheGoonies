#pragma once
#include "Item.h"
class HyperShoes :
    public Item
{


public:

	HyperShoes();
	
	string getTipo() override;
	float getVelocidad() override;
	
private:

	float velocidad;
	
};

