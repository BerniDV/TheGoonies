#pragma once
#include "Scene.h"

class Level
{

public:

	Level();
	static Level* createLevel();
	void init();
	void update(float deltaTime);
	void initShaders();
	void render();

	void restart();

	void addToCurrentScene(int numScene);
	void setToCurrentScene(int numScene);
	int getCurrentScene();

	bool playerHaveKey();

private:
	//Deber� ser un vector con un m�nimo de 3 escenas
	Scene* scene[5];
	int currentScene;
	ShaderProgram texProgram;

	glm::mat4 projection;
	Player* player;

};

