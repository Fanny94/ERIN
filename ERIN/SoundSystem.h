#pragma once
#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H
#include "Linker.h"
#include "fmod.hpp"
#include "fmod_errors.h" // Only if you want error checking
#include "fmod.h" //FMOD Ex
#include "fmod_common.h"
class Sound
{
private:
	static char * currentSound; //currently played sound
								//FMOD-specific stuff
	static FMOD_RESULT result;
	static FMOD_SYSTEM * fmodsystem;
	static FMOD_SOUND * sound;
	FMOD::System   *system;
	FMOD::Channel  *channel = 0;

	bool paused = false;
	bool playing = true;

public:
	~Sound();

	void UseitGameSound();
	void UseitFire();
	void UseitHit();
	void UseitSevereDmg();
	void fmod();
	void setPause(bool paused) { this->paused = paused; };
	bool getPause() { return paused; };
	void setPlaying(bool playing) { this->playing = playing; };
	bool getPlaying() { return playing; };

};

#endif // !SOUNDSYSTEM_H