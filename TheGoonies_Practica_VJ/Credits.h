#pragma once
#include "TextManager.h"
#include "TextureQuad.h"

class ShaderProgram;

class Credits
{
public:

	Credits();
	void buildCredits(ShaderProgram& program);

	static Credits& instance()
	{
		static Credits credits;

		return credits;
	}

	void render();

	bool getOpenCredits();
	void setOpenCredits(bool);

	bool getIsBuild();

private:

	TextManager* TxtManager[6];
	glm::mat4 projection;
	glm::mat4 modelview;
	ShaderProgram texProgram;
	bool openCredits;
	int optionSelected;
	float distanceAmongWords;

	bool isBuild;

	TexturedQuad* logoUPC;
	Texture textLogo;

};

