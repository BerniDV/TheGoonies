#pragma once
#include "Sprite.h"

class TileMap;

class Item
{

public:

	Item();

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, string path);
	void render() const;
	virtual void update(float deltaTime);

	void setPuedeColisionar(bool value);
	bool getPuedeColisionar();

	void setVisible(bool value);
	bool getVisible();

	bool playerContact(glm::ivec2 PlayerPosition);

	void restart();

	void setPosition(const glm::vec2& pos);
	void setTileMap(TileMap* tileMap);
	glm::ivec2 getPosItem();

	void setpriteSheet(string Path);

	virtual string getTipo() = 0;

protected:
	
	int delayInvisible;


	glm::ivec2 tileMapDispl, posItem;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;

	TileMap* map;

	bool visible;

	bool collisioning;
	bool puedeColisionar;

	float framesBtwAnimations;

	
	
};

