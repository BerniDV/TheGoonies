#pragma once
#include <glm/glm.hpp>


#include "Sprite.h"
#include "TextureQuad.h"

class ShaderProgram;

enum TypePortal
{

   Previous, Posterior
};

class portal
{

public:

	portal();
	void init(TypePortal type, glm::fvec2 position, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void setSceneToTeleport(int scene);
	void setposPlayer(glm::fvec2 posPlayer);
	void teleport(glm::fvec2& posPlayer);
	bool playerContact();
	
	void render();

	void update(float deltaTime);
	
private:

	glm::fvec2 tileMapDispl, posPortal;
	int sceneToTeleport;
	glm::fvec2 posPlayerAfterTeleport, posPlayerBeforTeleport;
	TypePortal tipoPortal;

	Texture texture;
	Sprite* sprite;

	bool collisioning;
	bool puedeColisionar;
};

