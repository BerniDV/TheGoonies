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
	die->setDefaultVolume(1.f);
	
	friendSaved = soundEngine->addSoundSourceFromFile("sounds/FriendSaved.mp3");
	friendSaved->setDefaultVolume(.5f);

	Win = soundEngine->addSoundSourceFromFile("sounds/Win.mp3");
	Win->setDefaultVolume(.5f);

	Key = soundEngine->addSoundSourceFromFile("sounds/Key.mp3");
	Key->setDefaultVolume(.5f);

	MenuTheme = soundEngine->addSoundSourceFromFile("sounds/MenuTheme.mp3");
	MenuTheme->setDefaultVolume(.5f);

	SonidoMolon = soundEngine->addSoundSourceFromFile("sounds/SonidoMolon.mp3");
	SonidoMolon->setDefaultVolume(.5f);

	CavernTheme = soundEngine->addSoundSourceFromFile("sounds/CavernTheme.mp3");
	CavernTheme->setDefaultVolume(.5f);
}

void SoundPlayer::play2DSong(const char* path, bool loop)
{
	if (path == "MainTheme")
	{
		
		soundEngine->play2D(MainTheme, loop);
		currentSound = path;
		
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
	else if (path == "Win")
	{

		soundEngine->play2D(Win);
	}
	else if (path == "Key")
	{

		soundEngine->play2D(Key);
	}
	else if (path == "MenuTheme")
	{

		soundEngine->play2D(MenuTheme);
		currentSound = path;
	}
	else if (path == "SonidoMolon")
	{

		soundEngine->play2D(SonidoMolon);
		currentSound = path;
	}
	else if (path == "CavernTheme")
	{

		soundEngine->play2D(CavernTheme);
		currentSound = path;
	}
	
	
}

void SoundPlayer::stopAllSongs()
{
	soundEngine->stopAllSounds();
	
}

string SoundPlayer::getCurrentSound()
{
	return currentSound;
}
