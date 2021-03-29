#include "SoundPlayer.h"

#include "Game.h"

void SoundPlayer::init()
{

	soundEngine = createIrrKlangDevice();
	if (!soundEngine)
	{
		Game::instance().keyPressed(27);
	}
}

void SoundPlayer::play2DSong(const char* path, bool loop)
{

	soundEngine->play2D(path, loop);
}
