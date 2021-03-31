#include "portal.h"

#include "Game.h"


void portal::init(TypePortal type, glm::fvec2 position)
{
	texture.loadFromFile("images/portal.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tipoPortal = type;
	posPortal = position;
}


void portal::setSceneToTeleport(int scene)
{

	sceneToTeleport = scene;
}

void portal::teleport(glm::fvec2& posPlayer)
{

	posPlayer = posPlayerAfterTeleport;

	if (tipoPortal == Previous)
	{

		Game::instance().goPreviousScene();
	}else
	{

		Game::instance().goNextScene();
	}
}

void portal::prepareTile(const glm::vec2& minCoords, ShaderProgram& program, int i, int j, int tileSize)
{

	
}

void portal::render()
{

	textQuad.render(texture);
}

