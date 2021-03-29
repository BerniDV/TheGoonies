#pragma once
#include "Enemigo.h"
class EnemigoComplejo :
	public Enemigo
{


public:

	EnemigoComplejo();

	void update(int deltaTime) override;
	string typeOf() override;

	void setPosTarget(glm::ivec2 posPlayer);

private:

	glm::ivec2 posTarget;
	bool MoveRight;
	bool targetVisto;


};

