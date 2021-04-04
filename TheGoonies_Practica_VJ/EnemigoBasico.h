#pragma once
#include "Enemigo.h"
class EnemigoBasico :
	public Enemigo
{

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;

	void update(int deltaTime) override;

	void setPosTarget(glm::ivec2) override;
	string typeOf() override;
	string getTipo() override;
};

