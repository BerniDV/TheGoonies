#include "EnemigoBasico.h"

enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT
};

void EnemigoBasico::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	setCollisioning(false);
	setPuedeCollisionar(true);
	setMoveRight(false);
	bJumping = false;

	setHealth(100.f);
	setCanRender(true);
	setEstado(ALIVE);
	velocidad = 1.f;

	spritesheet.loadFromFile("images/calavera.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));


	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void EnemigoBasico::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (!getMoveRight())
	{

		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);

		posPlayer.x -= 2;

		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			setMoveRight(true);
			posPlayer.x += 2;
			sprite->changeAnimation(MOVE_RIGHT);

		}

	}
	else
	{

		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);

		posPlayer.x += 2;

		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{

			setMoveRight(false);
			posPlayer.x -= 2;
			sprite->changeAnimation(MOVE_LEFT);

		}

	}


	if (!bJumping) {

		posPlayer.y += 4;
		posPlayer.x += 20;

		if (!map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{

			setMoveRight(!getMoveRight());
			posPlayer.y -= 4;
		}
		posPlayer.x -= 20;

		posPlayer.y += 4;
		posPlayer.x -= 20;

		if (!map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{

			setMoveRight(!getMoveRight());
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

	if (getHealth() <= 0.f && getEstado() == ALIVE)
	{

		setPuedeCollisionar(false);
		setCanRender(false);
		setEstado(DEAD);
	}
}

void EnemigoBasico::setPosTarget(glm::ivec2)
{
}

string EnemigoBasico::typeOf()
{
	return "EnemigoBasico";
}
