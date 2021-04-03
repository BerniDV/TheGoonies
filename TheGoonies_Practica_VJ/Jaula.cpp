#include "Jaula.h"


enum JaulaAnims
{
	STAND_CLOSE, STAND_OPEN
};

Jaula::Jaula()
{
	amigo = new Friend;
}

void Jaula::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	
	amigo->init(glm::ivec2(32, 32), shaderProgram);
	
	framesBtwAnimations = 0;
	visible = true;
	collisioning = false;
	puedeColisionar = true;
	jaulaCerrada = true;

	spritesheet.loadFromFile("images/jaula.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(.5, 1.), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(STAND_CLOSE, 1);
	sprite->addKeyframe(STAND_CLOSE, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(STAND_OPEN, 1);
	sprite->addKeyframe(STAND_OPEN, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posJaula.x), float(tileMapDispl.y + posJaula.y)));
}

void Jaula::render() const
{

	amigo->render();

	sprite->render();
}

void Jaula::update(float deltaTime)
{
	
	amigo->update(deltaTime);

	sprite->update(deltaTime);

	if (jaulaCerrada && sprite->animation() == STAND_OPEN)
	{

		sprite->changeAnimation(STAND_CLOSE);
	}

	if (!jaulaCerrada && sprite->animation() == STAND_CLOSE)
	{

		sprite->changeAnimation(STAND_OPEN);
	}
}

void Jaula::setPuedeColisionar(bool value)
{

	puedeColisionar = value;
}

bool Jaula::getPuedeColisionar()
{
	return puedeColisionar;
}

bool Jaula::playerContact(glm::ivec2 PlayerPosition)
{
	collisioning = false;

	//calcula para los dos extremos inferiores del cuadrado del jugador si esta en contacto con alguno de los extremos inferiores del cuadrado del enemigo
	collisioning = ((PlayerPosition.x >= posJaula.x - 2. * 16.f ) && (PlayerPosition.x <= posJaula.x + 3. * 16.f));

	if (collisioning)
	{
		//una vez sabemos que en x estamos tocando enemigo con jugador miro si en y passa lo mismo

		float collisionJaulalAlto = posJaula.y - 2 * 16.f;
		float collisionJaulaBajo = posJaula.y + 5 * 16.f;

		collisioning = (PlayerPosition.y <= collisionJaulaBajo) && (PlayerPosition.y >= collisionJaulalAlto);
	}

	if (collisioning)
	{
		collisioning = true;
	}


	return puedeColisionar && collisioning;
}

void Jaula::restart()
{
	
}

void Jaula::setPosition(const glm::vec2& pos)
{

	posJaula = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posJaula.x), float(tileMapDispl.y + posJaula.y)));

	amigo->setPosition(glm::vec2(glm::vec2(pos.x + 1 * 16, pos.y + (1 * 16))));
}

void Jaula::setTileMap(TileMap* tileMap)
{

	map = tileMap;
	amigo->setTileMap(tileMap);
}

glm::ivec2 Jaula::getPosJaula()
{

	return posJaula;
}

bool Jaula::getJaulaCerrada()
{
	return jaulaCerrada;
}

void Jaula::setJaulaCerrada(bool value)
{
	jaulaCerrada = value;
}

Friend* Jaula::getAmigo()
{
	if (amigo!=NULL)
	{
		return amigo;
	}
	
}
