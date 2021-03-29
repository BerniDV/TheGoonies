#include "Credits.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"

Credits::Credits()
{

	isBuild = false;
}

void Credits::buildCredits(ShaderProgram& program)
{

	distanceAmongWords = 60.f;
	openCredits = false;
	texProgram = program;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	TxtManager[0] = TextManager::CreateTextManager(program, "YOU", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords));
	TxtManager[1] = TextManager::CreateTextManager(program, "WIN", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords));
	TxtManager[2] = TextManager::CreateTextManager(program, "CREATED", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords));
	TxtManager[3] = TextManager::CreateTextManager(program, "BY", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords));
	TxtManager[4] = TextManager::CreateTextManager(program, "BERNAT", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords));
	TxtManager[5] = TextManager::CreateTextManager(program, "DELGADO", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords));

	glm::vec2 geom[2] = { glm::vec2(-250.f, 500.f), glm::vec2(750.f, 700.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	logoUPC = TexturedQuad::createTexturedQuad(geom, texCoords, program);
	textLogo.loadFromFile("images/logoupc.png", TEXTURE_PIXEL_FORMAT_RGBA);

	isBuild = true;
}

void Credits::render()
{
	//limpiar la pantalla de color negro
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Configurar el shader por defecto para que las otras texturas que usan el shader no afecten a este
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(-50.f, -250.f, 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[0]->print();

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(100.f, -250.f, 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[1]->print();

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(-50.f, -250.f + 100, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.8, 0.8, 1.f));
	modelview = glm::translate(modelview, glm::vec3(35.f, 0.f + 100, 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[2]->print();

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(100.f, -250.f + 100, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.8, 0.8, 1.f));
	modelview = glm::translate(modelview, glm::vec3(150.f, 0.f + 100, 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[3]->print();

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(-50.f, -250.f + 100, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.8, 0.8, 1.f));
	modelview = glm::translate(modelview, glm::vec3(35.f, 0.f + 100, 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[2]->print();

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(100.f, -250.f + 100, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.8, 0.8, 1.f));
	modelview = glm::translate(modelview, glm::vec3(150.f, 0.f + 100, 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[3]->print();

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(-50.f, -250.f + 100, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.5, 0.5, 1.f));
	modelview = glm::translate(modelview, glm::vec3(50.f + 150, 0.f + 500, 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[4]->print();

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(100.f, -250.f + 100, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.5, 0.5, 1.f));
	modelview = glm::translate(modelview, glm::vec3(30.f + 150, 0.f + 500, 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[5]->print();

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(0.f, -250.f + 100, 0.f));


	logoUPC->render(textLogo);

}


bool Credits::getOpenCredits()
{
	return openCredits;
}

void Credits::setOpenCredits(bool b)
{
	openCredits = b;
}

bool Credits::getIsBuild()
{
	return isBuild;
}
