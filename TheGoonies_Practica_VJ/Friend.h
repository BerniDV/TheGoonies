#pragma once
#include <glm/vec2.hpp>


#include "Sprite.h"
#include "Texture.h"
#include "TileMap.h"

class ShaderProgram;
class TileMap;

class Friend
{

public:

	Friend();
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	void render();
	void restart();

	void setPosition(const glm::vec2& pos);
	void setTileMap(TileMap* tileMap);
	glm::ivec2 getPosFriend();
	void setVisible(bool visible);

	void setPuedeColisionar(bool value);
	bool getPuedeColisionar();

	bool playerContact(glm::ivec2 PlayerPosition);


protected:

	glm::ivec2 tileMapDispl, posFriend;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;

	TileMap* map;

	bool visible;

	bool collisioning;
	bool puedeColisionar;

	float framesBtwAnimations;

};

