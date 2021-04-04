#include "HyperShoes.h"


HyperShoes::HyperShoes()
{
	velocidad = 3.f;
}

string HyperShoes::getTipo()
{

	return "HyperShoes";
}

float HyperShoes::getVelocidad()
{
	return velocidad;
}
