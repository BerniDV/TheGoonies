#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

#include "Menu.h"
#include "SoundPlayer.h"


void Game::init()
{
	friendsSafed = 0;
	bNeedToRestart = false;
	bPlay = true;
	bLose = false;
	bWin = false;
	godMode = false;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	level.init();
	HUD::instance().buildHUD();
	SoundPlayer::instance().init();
}

bool Game::update(int deltaTime)
{

	HUD::instance().update(deltaTime);

	if (level.playerHaveKey())
	{
		HUD::instance().setRenderKey(true);
	}else
	{
		HUD::instance().setRenderKey(false);
	}

	if (level.playerHaveHyperShoes())
	{
		HUD::instance().setRenderHyperShoes(true);
	}
	else
	{
		HUD::instance().setRenderHyperShoes(false);
	}

	if (level.playerHaveChubasquero())
	{
		HUD::instance().setRenderChubasquero(true);
	}
	else
	{
		HUD::instance().setRenderChubasquero(false);
	}

	if (level.playerHaveBlueBook())
	{
		HUD::instance().setRenderBlueBook(true);
	}
	else
	{
		HUD::instance().setRenderBlueBook(false);
	}

	if (level.playerHaveYellowBook())
	{
		HUD::instance().setRenderYellowBook(true);
	}
	else
	{
		HUD::instance().setRenderYellowBook(false);
	}

	if (level.playerHaveGreenBook())
	{
		HUD::instance().setRenderGreenBook(true);
	}
	else
	{
		HUD::instance().setRenderGreenBook(false);
	}
	
	//esta misma accion hay que hacerla solo cuando entramos en contacto con un amigo en escena
	//asi no habrà que comprovarlo cada frame
	if (friendsSafed == 6)
	{
		bWin = true;
		bNeedToRestart = true;
		Credits::instance().setOpenCredits(true);
	}

	if (!Menu::instance().getOpenMenu())
	{
		level.update(deltaTime);
	}
	else
	{

		//Menu::instance().update(deltaTime);
	}

	if (bWin)
	{

		SoundPlayer::instance().stopAllSongs();
		Menu::instance().openMenuFunc();

		bWin = false;

		if (bNeedToRestart)
		{
			level.restart();
			bNeedToRestart = false;
			friendsSafed = 0;
		}
	}

	if (bLose)
	{

		Menu::instance().openMenuFunc();

		if (bNeedToRestart)
		{
			level.restart();
			bNeedToRestart = false;
		}

	}



	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	level.render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	/* Este fragmento comentado da la posibilidad de abrir y cerrar el menu con el espacio en cualquier momento
	if (key == 32)
		if (!Menu::instance().getOpenMenu()) {
			Menu::instance().setOpenMenu(true);
			keyReleased(key);
		}
		else
			Menu::instance().setOpenMenu(false);
	*/

	if (Credits::instance().getOpenCredits() && key == 13)
	{

		Credits::instance().setOpenCredits(false);
	}
	else if (Menu::instance().getOpenMenu() && key == 13)//13 es el ascii de enter
	{

		Menu::instance().pressEnter();

	}
	else if (key == 49)
	{

		level.setToCurrentScene(0);
	}
	else if (key == 50)
	{
		level.setToCurrentScene(1);
	}
	else if (key == 51)
	{
		level.setToCurrentScene(2);
	}
	else if (key == 52)
	{
		level.setToCurrentScene(3);
	}
	else if (key == 53)
	{
		level.setToCurrentScene(4);
	}

	//al darle a la W se añade un amigo salvado
	if (key == 87)
	{

		++friendsSafed;
	}
	else if (key == 81)
	{

		godMode = !godMode;
	}

	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;

	if (!Credits::instance().getOpenCredits()) {

		if (Menu::instance().getOpenMenu() && key == GLUT_KEY_UP)
		{
			Menu::instance().addOptionMenu(-1);
		}
		if (Menu::instance().getOpenMenu() && key == GLUT_KEY_DOWN)
		{
			Menu::instance().addOptionMenu(1);
		}
	}

}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::getGodMode()
{
	return godMode;
}

void Game::setGodMode(bool bGodMode)
{
	godMode = bGodMode;
}

void Game::setBLose(bool b)
{
	bLose = b;
}

bool Game::getBLose()
{
	return bLose;
}

void Game::setNeedToRestart(bool value)
{
	bNeedToRestart = value;
}

int Game::getFriendsSafed()
{

	return friendsSafed;
}

void Game::setFriendsSafed(int amount)
{

	friendsSafed = amount;
}

void Game::addFriendSafed()
{
	++friendsSafed;
	SoundPlayer::instance().play2DSong("friendSaved", false);
}

void Game::goNextScene()
{

	level.addToCurrentScene(1);
}

void Game::goPreviousScene()
{
	level.addToCurrentScene(-1);
}

void Game::goToScene(int scene)
{
	level.setToCurrentScene(scene);
}

void Game::setbWin(bool bWin)
{
	this->bWin = bWin;
}




