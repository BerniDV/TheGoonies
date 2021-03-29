#include "OptionsMenu.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

OptionsMenu::OptionsMenu()
{
}

void OptionsMenu::buildMenu(ShaderProgram& program)
{

	distanceAmongWords = 60.f;
	optionSelected = optionsMenu::GODMODE;
	openOptionsMenu = false;
	openOptionsMenu = false;
	texProgram = program;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	TxtManager[0] = TextManager::CreateTextManager(program, "GODMODE", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f));
	TxtManager[1] = TextManager::CreateTextManager(program, "BACK", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f + distanceAmongWords * optionsMenu::BACK));
	TxtManager[2] = TextManager::CreateTextManager(program, "O", glm::vec2((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f));
}

void OptionsMenu::render()
{
	//limpiar la pantalla de color negro
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	renderOptionsMenu();


}

void OptionsMenu::renderOptionsMenu()
{


	//Configurar el shader por defecto para que las otras texturas que usan el shader no afecten a este
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	//Declarar modelview para mover el cuadrado con la textura por el mapa
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);

	switch (optionSelected)
	{
	case optionsMenu::GODMODE:

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

		if (Game::instance().getGodMode())
		{


			modelview = glm::mat4(1.0f);
			modelview = glm::translate(modelview, glm::vec3(-120.f, 0.f, 0.f));
			modelview = glm::translate(modelview, glm::vec3((SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f));
			modelview = glm::scale(modelview, glm::vec3(1.15f, 1.15f, 1.f));
			modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -SCREEN_HEIGHT * 0.5f, 0.f));

			texProgram.setUniformMatrix4f("modelview", modelview);
			TxtManager[2]->print();
		}

		break;

	case optionsMenu::BACK:

		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[0]->print();

		modelview = glm::mat4(1.0f);
		modelview = glm::translate(modelview, glm::vec3(-50.f, 0.f, 0.f));
		modelview = glm::translate(modelview, glm::vec3((SCREEN_WIDTH - 200.f) * 0.5f, (SCREEN_HEIGHT * 0.5f + distanceAmongWords * optionsMenu::BACK), 0.f));
		modelview = glm::scale(modelview, glm::vec3(1.15f, 1.15f, 1.f));
		modelview = glm::translate(modelview, glm::vec3(-(SCREEN_WIDTH - 200.f) * 0.5f, -(SCREEN_HEIGHT * 0.5f + distanceAmongWords * optionsMenu::BACK), 0.f));

		texProgram.setUniformMatrix4f("modelview", modelview);
		TxtManager[1]->print();

		if (Game::instance().getGodMode())
		{

			modelview = glm::mat4(1.0f);
			modelview = glm::translate(modelview, glm::vec3(-60.f, 0.f, 0.f));

			texProgram.setUniformMatrix4f("modelview", modelview);
			TxtManager[2]->print();
		}

		break;

	}

}

void OptionsMenu::addOptionMenu(int addition)
{
	if ((addition > 0 && optionSelected != optionsMenu::BACK) || (addition < 0 && optionSelected != optionsMenu::GODMODE))
	{
		optionSelected = optionSelected + addition;
	}
}

void OptionsMenu::pressEnter()
{

	switch (optionSelected)
	{

	case optionsMenu::GODMODE:

		functionGODMODE();
		break;
	case optionsMenu::BACK:

		functionBACK();
		break;

	}
}

void OptionsMenu::functionGODMODE()
{
	if (Game::instance().getGodMode())
	{
		Game::instance().setGodMode(false);
	}
	else
	{
		Game::instance().setGodMode(true);
	}

}

void OptionsMenu::functionBACK()
{

	openOptionsMenu = false;
}

bool OptionsMenu::getOpenOptionsMenu()
{
	return openOptionsMenu;
}

void OptionsMenu::setOpenOptionsMenu(bool open)
{
	openOptionsMenu = open;
}
