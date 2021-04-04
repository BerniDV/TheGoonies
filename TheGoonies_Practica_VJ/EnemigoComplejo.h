#pragma once
#include "Enemigo.h"
class EnemigoComplejo :
	public Enemigo
{


public:

	EnemigoComplejo();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;

	void update(int deltaTime) override;
	string typeOf() override;

	void setPosTarget(glm::ivec2 posPlayer);

	string getTipo() override;

private:

	glm::ivec2 posTarget;
	bool MoveRight;
	bool targetVisto;
	int maxHuntTime;

};

