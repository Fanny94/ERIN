#pragma once
#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H
#include "Linker.h"
#include "fmod.hpp"
#include "fmod_errors.h" // Only if you want error checking

class SoundSystem
{
	// Pointer to the FMOD instance
	FMOD::System *m_pSystem;
	SoundSystem();
	typedef FMOD::Sound* SoundClass;
	void CreateSound(SoundClass *pSound, const char* pFile);
	void PlaySound(SoundClass pSound, bool bLoop = false);


}




#endif // !SOUNDSYSTEM_H