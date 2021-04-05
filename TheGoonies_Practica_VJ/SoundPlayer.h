#pragma once

#include <irrKlang.h>
#include <string>
using namespace std;
using namespace irrklang;

class SoundPlayer
{

public:

	static SoundPlayer& instance()
	{
		static SoundPlayer SP;

		return SP;
	}

	void init();
	void play2DSong(const char* path, bool loop);
	void stopAllSongs();

	string getCurrentSound();
	void setCurrentSound(string sound);

private:

	ISoundEngine* soundEngine;
	ISoundSource* MainTheme;
	ISoundSource* punch;
	ISoundSource* die;
	ISoundSource* friendSaved;
	ISoundSource* Win;
	ISoundSource* Key;
	ISoundSource* MenuTheme;
	ISoundSource* SonidoMolon;
	ISoundSource* CavernTheme;

	string currentSound;
	
};

