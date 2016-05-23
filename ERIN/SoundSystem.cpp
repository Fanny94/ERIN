#include "SoundSystem.h"

char * Sound::currentSound; //currently played sound
							//FMOD-specific stuff
FMOD_RESULT Sound::result;
FMOD_SYSTEM * Sound::fmodsystem;
FMOD::Sound *Gsound, *sound1, *sound2, *sound4;

void Sound::fmod()
{
	void *extradriverdata = 0;

	result = FMOD::System_Create(&system);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	result = system->createSound("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/Sound Effects/Game Sounds/Expulsion-Sound-Game-Shoot.wav", FMOD_DEFAULT, 0, &sound1);

	result = sound1->setMode(FMOD_LOOP_OFF);

	result = system->createSound("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/Sound Effects/Game Sounds/Expulsion-Sound-Game-Hit.wav", FMOD_DEFAULT, 0, &sound2);

	result = system->createSound("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/Sound Effects/Game Sounds/Expulsion-Sound-Game-Damage.wav", FMOD_DEFAULT, 0, &sound4);

	result = system->createStream("C:/Users/cyka/Documents/GitHub/ERIN/Sounds/Music/Expulsion-Music-Game.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &Gsound);

	result = system->update();
	{
		unsigned int ms = 0;
		unsigned int lenms = 0;
		int channelsplaying = 0;
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

void Sound::UseitGameSound()
{
	result = system->playSound(Gsound, 0, false, &channel);
}

void Sound::UseitSevereDmg()
{
	result = system->playSound(sound4, 0, false, &channel);
}

Sound::~Sound()
{
	result = sound1->release();
	result = sound2->release();
	result = sound4->release();
	result = Gsound->release();
	result = system->close();
	result = system->release();
	FMOD_System_Close;
}