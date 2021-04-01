#include "HUD.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"


HUD::HUD()
{

}

void HUD::buildHUD()
{
	healthAmount = 100.f;
	experienceAmount = 0.f;

	dispanceAmongFriendsIcon = 20.f;
	distanceAmongWords = 60.f;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	TxtManager[0] = TextManager::CreateTextManager(texProgram, "HEALTH", glm::vec2((SCREEN_WIDTH - 850.f) * 0.5f, -500.f));
	TxtManager[1] = TextManager::CreateTextManager(texProgram, "EXPERIENCE", glm::vec2((SCREEN_WIDTH + 700.f) * 0.5f, -500.f));
	TxtManager[2] = TextManager::CreateTextManager(texProgram, "FRIENDS", glm::vec2((SCREEN_WIDTH + 700.f) * 0.5f, -500.f));
	position = { glm::vec2((SCREEN_WIDTH + 700.f) * 0.5f + 70, 1440.f) };

	health = Quad::createQuad(0, 0, healthAmount * 4.f, 50.f, texProgram);
	experience = Quad::createQuad(0, 0, experienceAmount * 4.f, 50.f, texProgram);
	friends = Quad::createQuad(0, 0, 50.f, 50.f, texProgram);
}

void HUD::updateHealth(float amount)
{
	if (amount < 0) amount = 0;

	healthAmount = amount;
	health->free();
	health = Quad::createQuad(0, 0, (amount) * 4.f, 50.f, texProgram);

}

void HUD::updateExperience(float amount)
{

	if (amount < 0) amount = 0;

	experienceAmount = amount;
	experience->free();
	experience = Quad::createQuad(0, 0, (amount) * 4.f, 50.f, texProgram);
}

void HUD::setTexProgram(ShaderProgram& program)
{
	texProgram = program;
}

void HUD::render()
{

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Configurar el shader por defecto para que las otras texturas que usan el shader no afecten a este
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//Declarar modelview para mover el cuadrado con la textura por el mapa

	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(-50.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));


	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[0]->print();
	TxtManager[1]->print();

	//dibujo el rectangulo que representa la vida

	texProgram.setUniform4f("color", 1.0f, .0f, .0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(-50.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(((SCREEN_WIDTH - 200.f) * 0.5f) + 50, SCREEN_HEIGHT - 392, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);

	health->render();


	//dibujo el rectangulo que representa la experiencia
	texProgram.setUniform4f("color", .0f, .0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(-50.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(((SCREEN_WIDTH - 200.f) * 0.5f) + 50, SCREEN_HEIGHT - 392, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3((SCREEN_WIDTH + 800.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);

	experience->render();

	//dibujo los rectangulos que representan los amigos

	renderFriends();

}

void HUD::renderFriends()
{

	
	texProgram.setUniform4f("color", 1.f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(25.f, 430.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));


	texProgram.setUniformMatrix4f("modelview", modelview);
	TxtManager[2]->print();

	int friendsSafed = Game::instance().getFriendsSafed();

	if (friendsSafed > 0)
		texProgram.setUniform4f("color", .0f, 1.0f, .0f, 1.0f);
	else
		texProgram.setUniform4f("color", 1.0f, .0f, .0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(20.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(((SCREEN_WIDTH) * 0.5f) + 200 + dispanceAmongFriendsIcon * 0, (SCREEN_HEIGHT * 0.5f) + 280, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	friends->render();

	if (friendsSafed > 1)
		texProgram.setUniform4f("color", .0f, 1.0f, .0f, 1.0f);
	else
		texProgram.setUniform4f("color", 1.0f, .0f, .0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(20.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(((SCREEN_WIDTH) * 0.5f) + 200 + dispanceAmongFriendsIcon * 1, (SCREEN_HEIGHT * 0.5f) + 280, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	friends->render();

	if (friendsSafed > 2)
		texProgram.setUniform4f("color", .0f, 1.0f, .0f, 1.0f);
	else
		texProgram.setUniform4f("color", 1.0f, .0f, .0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(20.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(((SCREEN_WIDTH) * 0.5f) + 200 + dispanceAmongFriendsIcon * 2, (SCREEN_HEIGHT * 0.5f) + 280, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	friends->render();

	if (friendsSafed > 3)
		texProgram.setUniform4f("color", .0f, 1.0f, .0f, 1.0f);
	else
		texProgram.setUniform4f("color", 1.0f, .0f, .0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(20.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(((SCREEN_WIDTH) * 0.5f) + 200 + dispanceAmongFriendsIcon * 3, (SCREEN_HEIGHT * 0.5f) + 280, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	friends->render();

	if (friendsSafed > 4)
		texProgram.setUniform4f("color", .0f, 1.0f, .0f, 1.0f);
	else
		texProgram.setUniform4f("color", 1.0f, .0f, .0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(20.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(((SCREEN_WIDTH) * 0.5f) + 200 + dispanceAmongFriendsIcon * 4, (SCREEN_HEIGHT * 0.5f) + 280, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	friends->render();

	if (friendsSafed > 5)
		texProgram.setUniform4f("color", .0f, 1.0f, .0f, 1.0f);
	else
		texProgram.setUniform4f("color", 1.0f, .0f, .0f, 1.0f);
	modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, glm::vec3(20.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(((SCREEN_WIDTH) * 0.5f) + 200 + dispanceAmongFriendsIcon * 5, (SCREEN_HEIGHT * 0.5f) + 280, 0.f));
	modelview = glm::scale(modelview, glm::vec3(0.3f, 0.3f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	friends->render();

}

void HUD::update(float deltaTime)
{

	updateHealth(healthAmount);
	updateExperience(experienceAmount);
}

