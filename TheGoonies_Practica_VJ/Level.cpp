#include "Level.h"

Level::Level()
{
	for (int i = 0; i < 5; ++i)
	{

		scene[i] = Scene::createScene();
	}

	currentScene = 1;
}

void Level::restart()
{
	for (int i = 0; i < 5; ++i)
	{

		scene[i]->restart();
	}
	
}

void Level::addToCurrentScene(int numScene)
{
	currentScene += numScene;
}

void Level::setToCurrentScene(int numScene)
{

	//Contiene la escena que se renderiza y actualiza
	currentScene = numScene;
}

int Level::getCurrentScene()
{
	return currentScene;
}


void Level::init()
{
	for (int i = 0; i<5; ++i)
	{

		scene[i]->setNumScene(i);
		scene[i]->init();
	}
	
}

void Level::update(float deltaTime)
{

	
	scene[currentScene]->update(deltaTime);
}

void Level::render()
{
	scene[currentScene]->render();
}

