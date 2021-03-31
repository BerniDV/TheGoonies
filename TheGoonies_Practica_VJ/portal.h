#pragma once
#include <glm/glm.hpp>

#include "TextureQuad.h"

class ShaderProgram;

enum TypePortal
{

   Previous, Posterior
};

class portal
{

public:

	
	void init(TypePortal type, glm::fvec2 position);
	void setSceneToTeleport(int scene);
	void teleport(glm::fvec2& posPlayer);
	void prepareTile(const glm::vec2& minCoords, ShaderProgram& program, int i, int j, int tileSize);
	
	void render();
	
private:

	int sceneToTeleport;
	glm::fvec2 posPlayerAfterTeleport;
	glm::fvec2 posPortal;
	TypePortal tipoPortal;

	TexturedQuad textQuad;
	Texture texture;

};

