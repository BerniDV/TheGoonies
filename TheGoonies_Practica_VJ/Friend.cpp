#include "Friend.h"


#include "Game.h"

enum FriendAnims
{
	STAND_FRONT, CROUCH_FRONT
};


Friend::Friend()
{

}

void Friend::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Friend::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	framesBtwAnimations = 0;
	visible = true;
	collisioning = false;
	puedeColisionar = true;

	spritesheet.loadFromFile("images/amic.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(.5, 1.), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(STAND_FRONT, 1);
	sprite->addKeyframe(STAND_FRONT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(CROUCH_FRONT, 1);
	sprite->addKeyframe(CROUCH_FRONT, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFriend.x), float(tileMapDispl.y + posFriend.y)));
}


bool Friend::playerContact(glm::ivec2 PlayerPosition)
{

	collisioning = false;

	//calcula para los dos extremos inferiores del cuadrado del jugador si esta en contacto con alguno de los extremos inferiores del cuadrado del enemigo
	collisioning = ((PlayerPosition.x >= posFriend.x) && (PlayerPosition.x <= posFriend.x + 1 * map->getTileSize())) || ((PlayerPosition.x + (1 * map->getTileSize()) >= posFriend.x) && ((PlayerPosition.x + +(1 * map->getTileSize()) <= posFriend.x + 1 * map->getTileSize())));

	if (collisioning)
	{
		//una vez sabemos que en x estamos tocando enemigo con jugador miro si en y passa lo mismo
		collisioning = (PlayerPosition.y <= posFriend.y) && (PlayerPosition.y >= posFriend.y - 2 * map->getTileSize());
	}


	return puedeColisionar && collisioning;
}

void Friend::update(int deltaTime)
{

	sprite->update(deltaTime);

	if (framesBtwAnimations == 25)
	{

		if (sprite->animation() == STAND_FRONT)
		{

			sprite->changeAnimation(CROUCH_FRONT);
		}
		else
		{

			sprite->changeAnimation(STAND_FRONT);
		}

		framesBtwAnimations = 0;
	}

	++framesBtwAnimations;

	if (collisioning && puedeColisionar)
	{

		puedeColisionar = false;
	}
}

void Friend::render()
{
	if (visible)
	{

		sprite->render();

	}
}

void Friend::restart()
{
	visible = false;
}

void Friend::setPosition(const glm::vec2& pos)
{
	posFriend = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFriend.x), float(tileMapDispl.y + posFriend.y)));
}

glm::ivec2 Friend::getPosFriend()
{
	return posFriend;
}

void Friend::setVisible(bool visible)
{

	this->visible = visible;
}

void Friend::setPuedeColisionar(bool value)
{
	puedeColisionar = value;
}

bool Friend::getPuedeColisionar()
{

	return puedeColisionar;
}
