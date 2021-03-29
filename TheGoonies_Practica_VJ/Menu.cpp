#include "Menu.h"


#include <iostream>
#include <GL/freeglut_std.h>
#include <glm/gtc/matrix_transform.hpp>


#include "Game.h"
#include "SoundPlayer.h"


Menu::Menu()
{
	isBuild = false;
}

void Menu::buildMenu(ShaderProgram& program)
{
	distanceAmongWords = 60.f;
	optionSelected = options::Play;
	openMenu = false;
	texProgram = program;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	TxtManager[0] = TextManager::CreateTextManager(program, "PLAY", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f));
	TxtManager[1] = TextManager::CreateTextManager(program, "CONTROLS", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords * options::CONTROLS));
	TxtManager[2] = TextManager::CreateTextManager(program, "EXIT", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords * options::Exit));
	TxtManager[3] = TextManager::CreateTextManager(program, "GAME", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords * options::Exit));
	TxtManager[4] = TextManager::CreateTextManager(program, "OVER", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords * options::Exit));

	optionsMenu.buildMenu(program);
	isBuild = true;
}

void Menu::render()
{
	renderMenu();

	if (optionsMenu.getOpenOptionsMenu())
		optionsMenu.render();
}

void Menu::openMenuFunc()
{

	openMenu = true;
	render();

}

bool Menu::getOpenMenu()
{
	return openMenu;
}

void Menu::update(float deltaTime)
{


}

void Menu::setOptionMenu(options o)
{
	optionSelected = o;
}

void Menu::addOptionMenu(int addition)
{
	if (!optionsMenu.getOpenOptionsMenu())
	{
		if ((addition > 0 && optionSelected != options::Exit) || (addition < 0 && optionSelected != options::Play))
		{
			optionSelected = optionSelected + addition;
		}
	}
	else {

		optionsMenu.addOptionMenu(addition);
	}

}

void Menu::pressEnter()
{
	if (!optionsMenu.getOpenOptionsMenu()) {

		switch (optionSelected)
		{

		case options::Play:

			functionPLAY();
			break;
		case options::CONTROLS:

			functionOPTIONS();
			break;
		case options::Exit:

			functionEXIT();
			break;
		}

	}
	else
	{

		optionsMenu.pressEnter();
	}
}

void Menu::functionPLAY()
{
	openMenu = false;
	Game::instance().setBLose(false);
	Game::instance().setbWin(false);
	Game::instance().setFriendsSafed(0);
	SoundPlayer::instance().play2DSong("sounds/MainTheme.mp3", true);
}

void Menu::functionOPTIONS()
{

	optionsMenu.setOpenOptionsMenu(true);

}

void Menu::functionEXIT()
{

	Game::instance().keyPressed(27);
}

bool Menu::getIsBuild()
{
	return isBuild;
}

void Menu::renderMenu()
{

	//limpiar la pantalla de color negro
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Configurar el shader por defecto para que las otras texturas que usan el shader no afecten a este
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	//Declarar modelview para mover el cuadrado con la textura por el mapa
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);

	//Pintar las opciones guardadas en textManager

	if (Game::instance().getBLose())
	{
		modelview = glm::mat4(1.0f);
		modelview = glm::translate(modelview, glm::vec3(-100.f, -250.f, 0.f));

		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[3]->print();

		modelview = glm::mat4(1.0f);
		modelview = glm::translate(modelview, glm::vec3(100.f, -250.f, 0.f));

		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[4]->print();
	}

	switch (optionSelected)
	{
	case options::Play:

		modelview = glm::mat4(1.0f);
		modelview = glm::translate(modelview, glm::vec3(-50.f, 0.f, 0.f));
		modelview = glm::translate(modelview, glm::vec3((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f));
		modelview = glm::scale(modelview, glm::vec3(1.15f, 1.15f, 1.f));
		modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));


		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[0]->print();

		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[1]->print();

		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[2]->print();
		break;
	case options::CONTROLS:

		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[0]->print();

		modelview = glm::mat4(1.0f);
		modelview = glm::translate(modelview, glm::vec3(-50.f, 0.f, 0.f));
		modelview = glm::translate(modelview, glm::vec3((SCREEN_WIDTH - 200.f) * 0.5f, (SCREEN_HEIGHT * 0.5f + distanceAmongWords * options::CONTROLS), 0.f));
		modelview = glm::scale(modelview, glm::vec3(1.15f, 1.15f, 1.f));
		modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -(SCREEN_HEIGHT * 0.5f + distanceAmongWords * options::CONTROLS), 0.f));

		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[1]->print();

		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[2]->print();
		break;


	case options::Exit:

		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[0]->print();

		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[1]->print();

		modelview = glm::mat4(1.0f);
		modelview = glm::translate(modelview, glm::vec3(-50.f, 0.f, 0.f));
		modelview = glm::translate(modelview, glm::vec3((SCREEN_WIDTH - 200.f) * 0.5f, (SCREEN_HEIGHT * 0.5f + distanceAmongWords * options::Exit), 0.f));
		modelview = glm::scale(modelview, glm::vec3(1.15f, 1.15f, 1.f));
		modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -(SCREEN_HEIGHT * 0.5f + distanceAmongWords * options::Exit), 0.f));

		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[2]->print();
		break;
	}

}




