#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>

#include "Enemigo.h"
#include "HUD.h"
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "TextManager.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

enum numPantalla
{

	primer = 0, segon, tercer, cuart, cinque
};

class Scene
{

public:

	static Scene* createScene();
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void reloadMap();
	void restart();

	void setNumScene(int numEscene);

	void calculateCorrectPantalla();

private:
	void initShaders();

private:
	vector<TileMap*> maps;
	Player* player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int pantalla;
	int numScene;


};


#endif // _SCENE_INCLUDE

