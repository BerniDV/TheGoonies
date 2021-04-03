#include "Trampa.h"

#include "Game.h"


enum TrampaAnims
{
	Creation, Ready_Fall, Falling, In_Floor
};

Trampa::Trampa()
{

}

void Trampa::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, string path)
{

	DelayBtwAnimations = 0;
	framesBtwAnimations = 0;
	visible = true;
	collisioning = false;
	puedeColisionar = true;

	spritesheet.loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(.5, .5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(Creation, 1);
	sprite->addKeyframe(Creation, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(Ready_Fall, 8);
	sprite->addKeyframe(Ready_Fall, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(Falling, 1);
	sprite->addKeyframe(Falling, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(In_Floor, 1);
	sprite->addKeyframe(In_Floor, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTrampa.x), float(tileMapDispl.y + posTrampa.y)));

	
}

void Trampa::render() const
{
	if (visible)
	{
		sprite->render();
	}

}

void Trampa::update(float deltaTime)
{

	sprite->update(deltaTime);

	if (sprite->animation() == Falling) {
		
		posTrampa.y += 2;
		setPosition(posTrampa);
	}

	if (map->collisionMoveDown(posTrampa, glm::ivec2(32, 32), &posTrampa.y))
	{
		DelayBtwAnimations = 0;
		sprite->changeAnimation(In_Floor);
	}

	if ((sprite->animation() == In_Floor && DelayBtwAnimations == 5) || (sprite->animation() == In_Floor && DelayBtwAnimations == 60))
	{

		visible = false;
		puedeColisionar = false;
		
		if (DelayBtwAnimations == 60)
		{
			
			sprite->changeAnimation(Creation);
			posTrampa.y = initialSpritePosY;
			visible = true;
			puedeColisionar = true;
			setPosition(posTrampa);
			DelayBtwAnimations = 0;
		}
		
	}

	if (DelayBtwAnimations == 40 && sprite->animation() == Creation)
	{

		sprite->changeAnimation(Ready_Fall);
	}

	if (DelayBtwAnimations == 60 && sprite->animation() == Ready_Fall)
	{

		sprite->changeAnimation(Falling);
	}

	++DelayBtwAnimations;
}

void Trampa::setPuedeColisionar(bool value)
{

	puedeColisionar = value;
}

bool Trampa::getPuedeColisionar()
{
	return puedeColisionar;
}

void Trampa::setVisible(bool value)
{
	visible = value;
}

bool Trampa::getVisible()
{
	return visible;
}

bool Trampa::playerContact(glm::ivec2 PlayerPosition)
{
	collisioning = false;

	//calcula para los dos extremos inferiores del cuadrado del jugador si esta en contacto con alguno de los extremos inferiores del cuadrado del enemigo
	collisioning = ((PlayerPosition.x >= posTrampa.x - 1. * 16.f) && (PlayerPosition.x <= (posTrampa.x + 1. * 16.f)-10));

	if (collisioning)
	{
		//una vez sabemos que en x estamos tocando enemigo con jugador miro si en y passa lo mismo

		float collisionJaulalAlto = posTrampa.y - 1 * 16.f;
		float collisionJaulaBajo = posTrampa.y + 3 * 16.f;

		collisioning = (PlayerPosition.y <= collisionJaulaBajo) && (PlayerPosition.y >= collisionJaulalAlto);
	}

	if (collisioning)
	{
		collisioning = true;
	}


	return puedeColisionar && collisioning && !Game::instance().getGodMode();
}

void Trampa::restart()
{

}

void Trampa::setPosition(const glm::vec2& pos)
{

	posTrampa = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTrampa.x), float(tileMapDispl.y + posTrampa.y)));

	
}

void Trampa::initPosition(const glm::vec2& pos)
{
	posTrampa = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTrampa.x), float(tileMapDispl.y + posTrampa.y)));
	initialSpritePosY = float(tileMapDispl.y + posTrampa.y) - 1 * 16;
}

void Trampa::setTileMap(TileMap* tileMap)
{

	map = tileMap;
}

glm::ivec2 Trampa::getPosTrampa()
{

	return posTrampa;
}

void Trampa::setpriteSheet(string Path)
{

	spritesheet.loadFromFile(Path, TEXTURE_PIXEL_FORMAT_RGBA);
}


