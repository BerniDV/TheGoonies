#pragma once
#include "Player.h"

enum EnemyStat
{

	ALIVE, DEAD
};

class Enemigo : public Player
{

public:

	Enemigo();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) = 0;
	void free();

	void render() override;

	bool playerContact(glm::ivec2 PlayerPosition);

	virtual string typeOf() = 0;

	virtual void setPosTarget(glm::ivec2) = 0;

	void setPuedeCollisionar(bool value);
	void setCollisioning(bool value);
	bool getCollisioning();
	bool getPuedeColisionar();
	bool getMoveRight();
	void setMoveRight(bool value);
	EnemyStat getEstado();
	void setEstado(EnemyStat estado);
	void setCanRender(bool value);
	bool getCanRender();

	void setHealth(float value);
	void addHealth(float value);
	float getHealth();

private:

	bool MoveRight;
	bool puedeColisionar;
	bool collisioning;
	bool bCanRender;
	EnemyStat estado;
	float health;
};

