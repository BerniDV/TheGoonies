#include "Cerradura.h"


enum CerraduraAnims
{
	STAND_CLOSE
};

Cerradura::Cerradura()
{
	
}

void Cerradura::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	framesBtwAnimations = 0;
	visible = true;
	collisioning = false;
	puedeColisionar = true;
	cerraduraCerrada = true;

	spritesheet.loadFromFile("images/cerradura.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32,32), glm::vec2(1., 1.), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_CLOSE, 1);
	sprite->addKeyframe(STAND_CLOSE, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCerradura.x), float(tileMapDispl.y + posCerradura.y)));
}

void Cerradura::render() const
{
	if (visible)
	{
		sprite->render();
	}
	
}

void Cerradura::update(float deltaTime)
{


	sprite->update(deltaTime);

	if (!cerraduraCerrada && visible)
	{

		visible = false;
	}

}

void Cerradura::setPuedeColisionar(bool value)
{

	puedeColisionar = value;
}

bool Cerradura::getPuedeColisionar()
{
	return puedeColisionar;
}

bool Cerradura::playerContact(glm::ivec2 PlayerPosition)
{
	collisioning = false;

	//calcula para los dos extremos inferiores del cuadrado del jugador si esta en contacto con alguno de los extremos inferiores del cuadrado del enemigo
	collisioning = ((PlayerPosition.x >= posCerradura.x - 1. * 16.f) && (PlayerPosition.x <= posCerradura.x + 1. * 16.f));

	if (collisioning)
	{
		//una vez sabemos que en x estamos tocando enemigo con jugador miro si en y passa lo mismo

		float collisionJaulalAlto = posCerradura.y - 1 * 16.f;
		float collisionJaulaBajo = posCerradura.y + 3 * 16.f;

		collisioning = (PlayerPosition.y <= collisionJaulaBajo) && (PlayerPosition.y >= collisionJaulalAlto);
	}

	if (collisioning)
	{
		collisioning = true;
	}


	return puedeColisionar && collisioning;
}

void Cerradura::restart()
{

}

void Cerradura::setPosition(const glm::vec2& pos)
{

	posCerradura = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCerradura.x), float(tileMapDispl.y + posCerradura.y)));

}

void Cerradura::setTileMap(TileMap* tileMap)
{

	map = tileMap;
}

glm::ivec2 Cerradura::getPosCerradura()
{

	return posCerradura;
}

bool Cerradura::getCerraduraCerrada()
{
	return cerraduraCerrada;
}

void Cerradura::setCerraduraCerrada(bool value)
{
	cerraduraCerrada = value;
}

