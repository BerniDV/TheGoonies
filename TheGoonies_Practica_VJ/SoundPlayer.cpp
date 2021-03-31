#include "SoundPlayer.h"

#include "Game.h"

void SoundPlayer::init()
{

	soundEngine = createIrrKlangDevice();
	if (!soundEngine)
	{
		Game::instance().keyPressed(27);
	}

	MainTheme = soundEngine->addSoundSourceFromFile("sounds/MainTheme.mp3");
	MainTheme->setDefaultVolume(1.f);
	
	punch = soundEngine->addSoundSourceFromFile("sounds/punch.wav");
	punch->setDefaultVolume(0.8f);
	
	die = soundEngine->addSoundSourceFromFile("sounds/Die.mp3");
	punch->setDefaultVolume(1.f);
	
	friendSaved = soundEngine->addSoundSourceFromFile("sounds/FriendSaved.mp3");
	punch->setDefaultVolume(.5f);
}

void SoundPlayer::play2DSong(const char* path, bool loop)
{
	if (path == "MainTheme")
	{
		
		soundEngine->play2D(MainTheme, loop);
		
	}else if (path == "punch")
	{

		soundEngine->play2D(punch);
	}else if (path == "die")
	{
		soundEngine->play2D(die);
	}else if (path == "friendSaved")
	{
		
		soundEngine->play2D(friendSaved);
	}
	
}

void SoundPlayer::stopAllSongs()
{
	soundEngine->stopAllSounds();
}