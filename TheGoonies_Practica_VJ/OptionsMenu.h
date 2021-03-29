#pragma once
#include "Game.h"
#include "TextManager.h"

enum optionsMenu
{
	GODMODE = 0,
	BACK
};

class OptionsMenu
{

public:

	OptionsMenu();
	void buildMenu(ShaderProgram& program);

	void render();
	void renderOptionsMenu();

	void addOptionMenu(int addition);
	void pressEnter();

	void functionGODMODE();
	void functionBACK();

	bool getOpenOptionsMenu();
	void setOpenOptionsMenu(bool);

private:

	TextManager* TxtManager[3];
	glm::mat4 projection;
	glm::mat4 modelview;
	ShaderProgram texProgram;
	bool openOptionsMenu;
	int optionSelected;
	float distanceAmongWords;


};

