#include "portal.h"

#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>


portal::portal()
{
	
}

void portal::init(TypePortal type, glm::fvec2 position, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	texture.loadFromFile("images/portal.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tipoPortal = type;
	posPortal = position;
	tileMapDispl = tileMapPos;
	sprite = Sprite::createSprite(glm::ivec2(96, 96), glm::vec2(1, 1.f), &texture, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 1);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPortal.x), float(tileMapDispl.y + posPortal.y)));

	collisioning = false;
	puedeColisionar = true;
}


void portal::setSceneToTeleport(int scene)
{

	sceneToTeleport = scene;
}

void portal::setposPlayer(glm::fvec2 posPlayer)
{
	posPlayerBeforTeleport = posPlayer;
}

void portal::teleport(glm::fvec2& posPlayer)
{

	posPlayer = posPlayerAfterTeleport;

	if (tipoPortal == Previous)
	{

		Game::instance().goPreviousScene();
	}else if(tipoPortal == Posterior)
	{

		Game::instance().goNextScene();
	}
}

bool portal::playerContact()
{

	collisioning = false;

	//calcula para los dos extremos inferiores del cuadrado del jugador si esta en contacto con alguno de los extremos inferiores del cuadrado del enemigo
	collisioning = ((posPlayerBeforTeleport.x >= posPortal.x + 1.3*16.f) && (posPlayerBeforTeleport.x <= posPortal.x + 3. * 16.f));

	if (collisioning)
	{
		//una vez sabemos que en x estamos tocando enemigo con jugador miro si en y passa lo mismo

		float collisionPortalAlto = posPortal.y + 2 * 16.f;
		float collisionPortalBajo = posPortal.y + 5 * 16.f;

		collisioning = (posPlayerBeforTeleport.y <= collisionPortalBajo) && (posPlayerBeforTeleport.y >= collisionPortalAlto);
	}

	if (collisioning)
	{
   		collisioning = true;
	}


	return puedeColisionar && collisioning;
}

glm::fvec2 portal::getPosPortal()
{

	return posPortal;
}

glm::fvec2 portal::getPosPlayerAfterTeleport()
{
	return posPlayerAfterTeleport;
}

TypePortal portal::getType()
{

	return tipoPortal;
}


void portal::render()
{
	
	//glm::mat4 modelview(1.0f);
	//modelview = glm::translate(modelview, glm::vec3(posPortal, 0.f));

	sprite->render();
}

void portal::update(float deltaTime)
{
	sprite->update(deltaTime);

	
}

