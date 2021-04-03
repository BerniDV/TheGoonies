#pragma once
#include "Friend.h"

class ShaderProgram;
class TileMap;
class Friend;

class Jaula
{


public:

	Jaula();

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void render() const;
	void update(float deltaTime);

	void setPuedeColisionar(bool value);
	bool getPuedeColisionar();

	bool playerContact(glm::ivec2 PlayerPosition);

	void restart();

	void setPosition(const glm::vec2& pos);
	void setTileMap(TileMap* tileMap);
	glm::ivec2 getPosJaula();

	bool getJaulaCerrada();
	void setJaulaCerrada(bool value);

	Friend* getAmigo();

private:
	
	Friend* amigo;
	glm::ivec2 tileMapDispl, posJaula;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;

	TileMap* map;

	bool visible;

	bool collisioning;
	bool puedeColisionar;
	bool jaulaCerrada;

	float framesBtwAnimations;

	//glm::fvec2 posJaula;
	
};

