#pragma once
#include "Sprite.h"
#include "TileMap.h"


class Trampa
{

public:

	Trampa();

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
	void initPosition(const glm::vec2& pos);
	
	void setTileMap(TileMap* tileMap);
	glm::ivec2 getPosTrampa();
	

	void setpriteSheet(string Path);


protected:


	glm::ivec2 tileMapDispl;
	glm::fvec2 posTrampa;
	float initialSpritePosY;
	Texture spritesheet;
	Sprite* sprite;

	TileMap* map;

	bool visible;

	bool collisioning;
	bool puedeColisionar;

	float framesBtwAnimations;
	int DelayBtwAnimations;
};

