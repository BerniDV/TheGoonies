#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();
	void restart();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	glm::ivec2 getPosPlayer();
	TileMap* getMap();

	float getHealth();
	void setHealth(float life);
	void addHealth(float amountHealth);

	float getExperiencie();

	bool enemyContact(glm::fvec2 enemyPos);
	void punchIfPossible(Enemigo& enemy, float amount);

protected:

	bool bhitting;
	bool bCanHit;
	bool bJumping;
	bool bClimbing;
	glm::ivec2 tileMapDispl;
	glm::fvec2 posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	float health;
	float experience;
	float velocidad;

	int timeHitting;
	int delayToHitAgain;

};


#endif // _PLAYER_INCLUDE


