#pragma once
#include "Llave.h"
#include "Quad.h"
#include "TextManager.h"
class ShaderProgram;

class HUD
{

public:

	HUD();
	static HUD& instance()
	{
		static HUD H;

		return H;
	}
	void buildHUD();
	void updateHealth(float amount);
	void updateExperience(float amount);

	void setTexProgram(ShaderProgram& program);

	void render();
	void renderFriends();

	void update(float deltaTime);

	void setRenderKey(bool value);

private:

	TextManager* TxtManager[3];
	glm::mat4 projection;
	glm::mat4 modelview;
	ShaderProgram texProgram;
	float distanceAmongWords;
	float dispanceAmongFriendsIcon;

	float healthAmount;
	float experienceAmount;

	Quad* health;
	Quad* experience;
	Quad* friends;

	glm::fvec2 position;

	Llave llave;
	bool renderKey;
	
};

