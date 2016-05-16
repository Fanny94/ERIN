#include "SoundSystem.h"

char * Sound::currentSound; //currently played sound
							//FMOD-specific stuff
FMOD_RESULT Sound::result;
FMOD_SYSTEM * Sound::fmodsystem;
FMOD::Sound  *Msound, *Gsound, *sound1, *sound2, *sound3, *sound4;

void Sound::fmod()
{
	void *extradriverdata = 0;

	result = FMOD::System_Create(&system);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	result = system->createSound("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/In Game sounds/Expulsion-Sound-Game-Shoot.wav", FMOD_DEFAULT, 0, &sound1);

	result = sound1->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
					                            /* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */

	result = system->createSound("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/In Game sounds/Expulsion-Sound-Game-Hit.wav", FMOD_DEFAULT, 0, &sound2);

	result = system->createSound("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/In Game sounds/Expulsion-Sound-Game-Engine.wav", FMOD_DEFAULT, 0, &sound3);

	result = system->createSound("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/In Game sounds/Expulsion-Sound-Game-Damage.wav", FMOD_DEFAULT, 0, &sound4);

	result = system->createStream("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/Music for the Game/Expulsion-Music-Game.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &Gsound);

	result = system->createStream("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/Music for the Game/Expulsion-Music-Menu.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &Msound);
	
	result = system->update();
		{
			unsigned int ms = 0;
			unsigned int lenms = 0;
			int     channelsplaying = 0;

			if (channel)
			{
				FMOD::Sound *currentsound = 0;

				result = channel->isPlaying(&playing);
			
				result = channel->getPaused(&paused);
			
				result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
				
			}

			system->getChannelsPlaying(&channelsplaying, NULL);
		}
}

void Sound::UseitFire()
{
	result = system->playSound(sound1, 0, false, &channel);
}

void Sound::UseitHit()
{
	result = system->playSound(sound2, 0, false, &channel);
}

void Sound::UseitEngineSound()
{
	result = system->playSound(sound3, 0, false, &channel);
}

void Sound::UseitGameSound()
{
	result = system->playSound(Gsound, 0, false, &channel);
}

void Sound::UseitMenuSound()
{
	result = system->playSound(Msound, 0, false, &channel);
}

void Sound::UseitSevereDmg()
{
	result = system->playSound(sound4, 0, false, &channel);
}

Sound::~Sound()
{
	result = sound1->release();

	result = sound2->release();

	result = sound3->release();

	result = Gsound->release();
	
	result = system->close();

	result = system->release();

	FMOD_System_Close;
}


/*void Sound::initialise()
{
	//create the sound system. If fails, sound is set to impossible
	result = FMOD_System_Create(&fmodsystem);
	if (result != FMOD_OK) possible = false;
	//if initialise the sound system. If fails, sound is set to impossible
	if (possible) result = FMOD_System_Init(fmodsystem, 36, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) possible = false;
	//sets initial sound volume (mute)
	if (possible) FMOD_Channel_SetVolume(channel, 0.0f);
}

//sets the actual playing sound's volume
void Sound::setVolume(float v)
{
	if (possible && on && v >= 0.0f && v <= 1.0f) {
		FMOD_Channel_SetVolume(channel, v);
	}
}

//loads a soundfile
void Sound::loadStream(const char * filename)
{
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound);
		result = FMOD_System_CreateStream(fmodsystem, currentSound, NULL, 0, &sound);
		if (result != FMOD_OK) possible = false;
	}
}

void Sound::loadSample(const char * filename)
{
	currentSound = (char *)filename;
	if (possible && on)
	{
		result = FMOD_Sound_Release(sound);
		result = FMOD_System_CreateSound(FMOD_DEFAULT, currentSound, FMOD_DEFAULT, 0, &sound);
		if (result != FMOD_OK) possible = false;
	}
}

//frees the sound object
void Sound::unload(void)
{
	if (possible) {
		result = FMOD_Sound_Release(sound);
	}
}

//plays a sound (no argument to leave pause as dafault)
void Sound::play(bool pause)
{
	if (possible && on)
	{
		result = FMOD_System_PlaySound(fmodsystem, sound, NULL, pause, &channel);
		FMOD_Channel_SetMode(channel, FMOD_LOOP_NORMAL);
	}
}

//toggles sound on and off
void Sound::toggleStreamSound(void)
{
	on = !on;
	if (on == true) { loadStream(currentSound); play(); }
	if (on == false) { unload(); }
}

void Sound::toggleSampleSound(void)
{
	on = !on;
	if (on == true) { loadSample(currentSound); play(); }
	if (on == false) { unload(); }
}

//pause or unpause the sound
void Sound::setPause(bool pause)
{
	FMOD_Channel_SetPaused(channel, pause);
}

//turn sound on or off
void Sound::setSound(bool s)
{
	on = s;
}

//toggle pause on and off
void Sound::togglePause(void)
{
	FMOD_BOOL p;
	FMOD_Channel_GetPaused(channel, &p);
	FMOD_Channel_SetPaused(channel, !p);
}

//tells whether the sound is on or off
bool Sound::getSound(void)
{
	return on;
}*/

/*FSOUND_SAMPLE* handle;

void Sound::playFire()
{
	initialise();
	load
	// init FMOD sound system
	FSOUND_Init(44100, 32, 0);

	// load and play sample
	handle = FSOUND_Sample_Load(0, "sample.mp3", 0, 0, 0);
	FSOUND_PlaySound(0, handle);

	// wait until the users hits a key to end the app
	while (!_kbhit())
	{
	}

	// clean up
	FSOUND_Sample_Free(handle);
	FSOUND_Close();
}


/*Sound::Sound()
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

void Sound::CreateSound(SoundClass *pSound, const char* pFile)
{
	m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
}


void Sound::playSound(SoundClass pSound, bool bLoop)
{
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	m_pSystem->playSound(pSound, FMOD_DEFAULT, false, 0);
}

void Sound::ReleaseSound(SoundClass pSound)
{
	pSound->release();
}

void Sound::UseInGameSong()
{
	CreateSound(&pSound, "C:/Users/cyka/Desktop/Sounds/Music for the Game/Expulsion-Music-Game.wav");
	playSound(pSound, true);
	ReleaseSound(pSound);
}*/