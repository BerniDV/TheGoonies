#include "Item.h"



enum CerraduraAnims
{
	STAND_CLOSE
};

Item::Item()
{

}

void Item::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, string path)
{

	framesBtwAnimations = 0;
	visible = true;
	collisioning = false;
	puedeColisionar = true;

	spritesheet.loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1., 1.), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_CLOSE, 1);
	sprite->addKeyframe(STAND_CLOSE, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posItem.x), float(tileMapDispl.y + posItem.y)));
}

void Item::render() const
{
	if (visible)
	{
		sprite->render();
	}

}

void Item::update(float deltaTime)
{

	sprite->update(deltaTime);


}

void Item::setPuedeColisionar(bool value)
{

	puedeColisionar = value;
}

bool Item::getPuedeColisionar()
{
	return puedeColisionar;
}

void Item::setVisible(bool value)
{
	visible = value;
}

bool Item::getVisible()
{
	return visible;
}

bool Item::playerContact(glm::ivec2 PlayerPosition)
{
	collisioning = false;

	//calcula para los dos extremos inferiores del cuadrado del jugador si esta en contacto con alguno de los extremos inferiores del cuadrado del enemigo
	collisioning = ((PlayerPosition.x >= posItem.x - 1. * 16.f) && (PlayerPosition.x <= posItem.x + 1. * 16.f));

	if (collisioning)
	{
		//una vez sabemos que en x estamos tocando enemigo con jugador miro si en y passa lo mismo

		float collisionJaulalAlto = posItem.y - 1 * 16.f;
		float collisionJaulaBajo = posItem.y + 3 * 16.f;

		collisioning = (PlayerPosition.y <= collisionJaulaBajo) && (PlayerPosition.y >= collisionJaulalAlto);
	}

	if (collisioning)
	{
		collisioning = true;
	}


	return puedeColisionar && collisioning;
}

void Item::restart()
{

}

void Item::setPosition(const glm::vec2& pos)
{

	posItem = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posItem.x), float(tileMapDispl.y + posItem.y)));

}

void Item::setTileMap(TileMap* tileMap)
{

	map = tileMap;
}

glm::ivec2 Item::getPosItem()
{

	return posItem;
}

void Item::setpriteSheet(string Path)
{

	spritesheet.loadFromFile(Path, TEXTURE_PIXEL_FORMAT_RGBA);
}




