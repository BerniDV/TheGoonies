#include "Enemigo.h"

#include "Game.h"

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

Enemigo::Enemigo()
{

}


void Enemigo::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	collisioning = false;
	puedeColisionar = true;
	MoveRight = false;
	bJumping = false;
	health = 100.f;
	estado = ALIVE;
	bCanRender = true;

	velocidad = 1.f;

	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}


void Enemigo::free()
{

	delete this;

}

void Enemigo::render()
{
	if (bCanRender)
	{

		sprite->render();
	}
}

bool Enemigo::playerContact(glm::ivec2 PlayerPosition)
{

	collisioning = false;

	//calcula para los dos extremos inferiores del cuadrado del jugador si esta en contacto con alguno de los extremos inferiores del cuadrado del enemigo
	collisioning = ((PlayerPosition.x >= posPlayer.x) && (PlayerPosition.x <= posPlayer.x + 1 * map->getTileSize())) || ((PlayerPosition.x + (1 * map->getTileSize()) >= posPlayer.x) && ((PlayerPosition.x + +(1 * map->getTileSize()) <= posPlayer.x + 1 * map->getTileSize())));

	if (collisioning)
	{
		//una vez sabemos que en x estamos tocando enemigo con jugador miro si en y passa lo mismo
		collisioning = (PlayerPosition.y <= posPlayer.y) && (PlayerPosition.y >= posPlayer.y - 2 * map->getTileSize());
	}
	// en el momento que deja de colisionar con el jugador puede volver a colisionar
	if (!collisioning)
	{
		puedeColisionar = true;
	}

	return puedeColisionar && collisioning && !Game::instance().getGodMode() && estado == ALIVE;
}

void Enemigo::setPuedeCollisionar(bool value)
{

	puedeColisionar = value;
}

void Enemigo::setCollisioning(bool value)
{

	collisioning = value;
}

bool Enemigo::getCollisioning()
{

	return collisioning;
}

bool Enemigo::getPuedeColisionar()
{

	return puedeColisionar;
}

bool Enemigo::getMoveRight()
{

	return MoveRight;
}

void Enemigo::setMoveRight(bool value)
{

	MoveRight = value;
}

EnemyStat Enemigo::getEstado()
{

	return estado;
}

void Enemigo::setEstado(EnemyStat estado)
{

	this->estado = estado;
}

void Enemigo::setCanRender(bool value)
{
	bCanRender = value;
}

bool Enemigo::getCanRender()
{

	return bCanRender;
}

void Enemigo::setbCanRender(bool value)
{

	bCanRender = value;
}

void Enemigo::setHealth(float value)
{

	health = value;
}

void Enemigo::addHealth(float value)
{

	health += value;
}

float Enemigo::getHealth()
{

	return health;
}
