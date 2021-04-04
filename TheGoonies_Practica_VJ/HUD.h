#pragma once
#include "BlueBook.h"
#include "Chubasquero.h"
#include "GreenBook.h"
#include "HyperShoes.h"
#include "Llave.h"
#include "Quad.h"
#include "TextManager.h"
#include "YellowBook.h"
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
	
	void setRenderHyperShoes(bool value);
	
	void setRenderChubasquero(bool value);

	void setRenderBlueBook(bool value);

	void setRenderYellowBook(bool value);

	void setRenderGreenBook(bool value);

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

	HyperShoes hypershoes;
	bool renderHyperShoes;

	Chubasquero chubasquero;
	bool renderChubasquero;

	BlueBook bluebook;
	bool renderBlueBook;

	YellowBook yellowbook;
	bool renderYellowBook;;

	GreenBook greenbook;
	bool renderGreenBook;;

	
};

