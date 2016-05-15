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
	//static void initialise(); //initialises sound
	~Sound();

								  //sound control
	/*void setVolume(float v); //sets the actual playing sound's volume
	void loadStream(const char * filename); //loads a soundfile
	void loadSample(const char * filename);
	void unload(void); //frees the sound object
	void play(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)

								  //getters
	bool getSound(void); //checks whether the sound is on

						//setters
	void setPause(bool pause); //pause or unpause the sound
	void setSound(bool sound); //set the sound on or off

							  //toggles
	void toggleStreamSound(void); //toggles sound on and off
	void toggleSampleSound(void);
	void togglePause(void); //toggle pause on/off*/

	/*void CreateSound(Sound *pSound, const char* pFile);
	void playSound(Sound pSound, bool bLoop = false);
	void ReleaseSound(Sound pSound);*/


	void UseitGameSound();
	void UseitMenuSound();
	void UseitFire();
	void UseitHit();
	void UseitEngineSound();
	void UseitDmg();
	void fmod();
	void setPause(bool paused) { this->paused = paused; };
	bool getPause() { return paused; };
	void setPlaying(bool playing) { this->playing = playing; };
	bool getPlaying() { return playing; };
	
};

/*
class Sound
{
public:
	// Pointer to the FMOD instance
	FMOD::System *m_pSystem;
	Sound();
	typedef FMOD::Sound* SoundClass;

	void UseInGameSong();
	SoundClass pSound;
};*/


#endif // !SOUNDSYSTEM_H