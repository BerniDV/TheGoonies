#pragma once
#include "TileMap.h"

class TileMap;

class Cerradura
{

public:

	Cerradura();

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void render() const;
	void update(float deltaTime);

	void setPuedeColisionar(bool value);
	bool getPuedeColisionar();

	bool playerContact(glm::ivec2 PlayerPosition);

	void restart();

	void setPosition(const glm::vec2& pos);
	void setTileMap(TileMap* tileMap);
	glm::ivec2 getPosCerradura();

	bool getCerraduraCerrada();
	void setCerraduraCerrada(bool value);


private:
	
	glm::ivec2 tileMapDispl, posCerradura;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;

	TileMap* map;

	bool visible;

	bool collisioning;
	bool puedeColisionar;
	bool cerraduraCerrada;

	float framesBtwAnimations;
};

