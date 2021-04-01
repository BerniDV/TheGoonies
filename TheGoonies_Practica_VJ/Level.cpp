#include "Level.h"

#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define SCREEN_X 32
#define SCREEN_Y 16


Level::Level()
{

	player = new Player();
	initShaders();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	
	for (int i = 0; i < 5; ++i)
	{

		scene[i] = Scene::createScene(*player);
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
	
	projection = glm::ortho(-50.f, float(SCREEN_WIDTH + 51), float(SCREEN_HEIGHT + 51), -50.f);

	
	for (int i = 0; i<5; ++i)
	{

		scene[i]->setNumScene(i);
		scene[i]->init(texProgram);
	}
	
}

void Level::update(float deltaTime)
{

	scene[currentScene]->update(deltaTime);

	vector<portal*> portals = scene[currentScene]->getMaps()[scene[currentScene]->getCurrentPantalla()]->getPortals();

	for (auto p : portals)
	{

		if (p != NULL) {

			p->setposPlayer(player->getPosPlayer());

			if (p->playerContact()) {

				if (Game::instance().getKey(13))
				{
					if (p->getType() == Previous)
					{

						vector<TileMap*> maps = scene[currentScene - 1]->getMaps();
						
						for (int i = 0; i < 3; i++) {

							vector<portal*> portalsOfPortal = maps[i]->getPortals();

							for (auto p2 : portalsOfPortal)
							{
								if (p2 != NULL && p2->getType() == Posterior)
								{

									glm::fvec2 pos = p2->getPosPortal();
									pos.x = pos.x + 2 * 16.f;
									pos.y = pos.y + 1 * 16.f;
									player->setPosition(pos);

									p->teleport(pos);
									
									
								}
							}

						}
					}
					else
					{

						vector<TileMap*> maps = scene[currentScene + 1]->getMaps();
						
						for (int i = 0; i < 3; i++) {

							vector<portal*> portalsOfPortal = maps[i]->getPortals();

							for (auto p2 : portalsOfPortal)
							{

								TypePortal a = p2->getType();
								if (p2 != NULL && p2->getType() == Previous)
								{

									glm::fvec2 pos = p2->getPosPortal();
									pos.x = pos.x + 2 * 16.f;
									pos.y = pos.y + 1 * 16.f;
									player->setPosition(pos);
									
									p->teleport(pos);
									
									
								}
							}

						}
					}

					Game::instance().keyReleased(13);

				}
			}

		}
	}
}

void Level::initShaders()
{

	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Level::render()
{
	
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	scene[currentScene]->render();
}

