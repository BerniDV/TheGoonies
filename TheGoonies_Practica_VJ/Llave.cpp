#include "Llave.h"

Llave::Llave()
{

	delayInvisible = 0;
}

string Llave::getTipo()
{
	return "llave";
}

void Llave::update(float deltaTime)
{

	sprite->update(deltaTime);

	if (puedeColisionar && delayInvisible == 5)
	{

		visible = true;
	}

	if (delayInvisible == 15)
	{
		visible = false;
		delayInvisible = 0;
	}

	if(puedeColisionar)
		++delayInvisible;
}
