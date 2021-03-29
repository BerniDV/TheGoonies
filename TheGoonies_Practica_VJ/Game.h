#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Credits.h"
#include "Level.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}


	static Game& instance()
	{
		static Game G;

		return G;
	}

	void init();
	void setbWin(bool bWin);
	bool update(int deltaTime);
	void render();

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	bool getGodMode();
	void setGodMode(bool GodMode);

	void setBLose(bool b);
	bool getBLose();
	void setNeedToRestart(bool value);

	int getFriendsSafed();
	void setFriendsSafed(int amount);
	void addFriendSafed();

private:
	bool bPlay;                       // Continue to play game?
	Level level;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that
									  // we can have access at any time
	//Poner esta variable a true desde donde sea hace que se gane la partida
	bool bWin;
	bool bLose;
	bool bNeedToRestart;
	bool godMode;

	int friendsSafed;
};


#endif // _GAME_INCLUDE


