#pragma once
#include "Scene.h"

class Level
{

public:

	Level();
	static Level* createLevel();
	void init();
	void update(float deltaTime);
	void render();

	void restart();

private:
	//Deberà ser un vector con un mínimo de 3 escenas
	Scene* scene;

};

