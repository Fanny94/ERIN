#include "SoundSystem.h"


SoundSystem::SoundSystem()
{
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		// Report Error
		return;
	}

	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		// Report Error
		return;
	}

	// Initialize our Instance with 36 Channels
	m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);
}

void SoundSystem::CreateSound(SoundClass *pSound, const char* pFile)
{
	m_pSystem->createSound(pFile, FMOD_HARDWARE, 0, pSound);
}


void SoundSystem::PlaySound(SoundClass pSound, bool bLoop = false)
{
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, 0);
}