#include "EnemigoComplejo.h"

#include "Game.h"

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

EnemigoComplejo::EnemigoComplejo()
{
	targetVisto = false;
}

void EnemigoComplejo::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	setCollisioning(false);
	setPuedeCollisionar(true);
	setMoveRight(false);
	bJumping = false;
	setHealth(100.f);
	setEstado(ALIVE);
	setbCanRender(true);

	velocidad = .5f;

	spritesheet.loadFromFile("images/esqueleto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_RIGHT, 3);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 3);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_LEFT, 3);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 3);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0., 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void EnemigoComplejo::update(int deltaTime)
{

	sprite->update(deltaTime);

	if (targetVisto)
	{
		velocidad = 7.f;
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
	}
	else
	{
		velocidad = 1.f;
		sprite->setAnimationSpeed(MOVE_LEFT, 3);
		sprite->setAnimationSpeed(MOVE_LEFT, 3);
	}

	if (posTarget.y == getPosPlayer().y)
	{
		if (posTarget.x > getPosPlayer().x && (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT))
		{
			targetVisto = true;

		}
		else if (posTarget.x < getPosPlayer().x && (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT))
		{

			targetVisto = true;

		}

	}


	if (!MoveRight)
	{

		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);

		posPlayer.x -= 1 * velocidad;

		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			targetVisto = false;
			MoveRight = true;
			posPlayer.x += 1 * velocidad;
			sprite->changeAnimation(MOVE_RIGHT);

		}

	}
	else if (MoveRight)
	{

		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);

		posPlayer.x += 1 * velocidad;

		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			targetVisto = false;
			MoveRight = false;
			posPlayer.x -= 1 * velocidad;
			sprite->changeAnimation(MOVE_LEFT);

		}

	}


	if (!bJumping) {

		posPlayer.y += 4;
		posPlayer.x += 20;

		if (!map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{

			MoveRight = !MoveRight;
			posPlayer.y -= 4;
		}
		posPlayer.x -= 20;

		posPlayer.y += 4;
		posPlayer.x -= 20;

		if (!map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{

			MoveRight = !MoveRight;
			posPlayer.y -= 4;
		}
		posPlayer.x += 20;

		posPlayer.y += 4;
		if (!map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			bJumping = true;
			posPlayer.y -= 4;
		}


	}
	else
	{

		posPlayer.y += 4;
		bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
	}


	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	//Este condicional permite que el enemigo no pueda colisionar con el jugador hasta que deje la colision actual
	if (getCollisioning() && getPuedeColisionar())
	{

		setPuedeCollisionar(false);
	}

}

string EnemigoComplejo::typeOf()
{
	return "EnemigoComplejo";
}

void EnemigoComplejo::setPosTarget(glm::ivec2 posPlayer)
{

	posTarget = posPlayer;
}
