#include "soundmanager.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>


const int FREQUENCY = 22050;
const int CHUNKSIZE = 4096; 
const int CHANNELS = 2;

SoundManager* SoundManager::instance = NULL;

SoundManager*
SoundManager::Instance()
{
	if(SoundManager::instance == NULL)
	{
		instance = new SoundManager();
		instance->setEnable(true);
		return instance;
	}
	
	return instance;	

}


SoundManager::SoundManager()
{
	Mix_OpenAudio(FREQUENCY, AUDIO_S16, CHANNELS, CHUNKSIZE);
}

bool
SoundManager::loadSound(std::string path, std::string soundId, sound_type type)
{
	if(type == MUSIC)
	{
		Mix_Music* music = Mix_LoadMUS(path.c_str());

		if(!music)
		{
			std::cout<<"Could not load music: "<<Mix_GetError()<<std::endl;
			return false;
		}

		musicMap[soundId] = music;
		return true;
	}
	else if(type == SFX)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());

		if(!chunk)
		{
			std::cout<<"Could not load sfx: "<<Mix_GetError()<<std::endl;
			return false;
		} 

		sfxMap[soundId] = chunk;
		return true;
	}

	return false;
}

void
SoundManager::playMusic(std::string musicId, int loop)
{
	Mix_PlayMusic(musicMap[musicId], loop);
}

void
SoundManager::playSound(std::string soundId, int loop)
{
	Mix_PlayChannel(-1, sfxMap[soundId], loop);
}

void 
SoundManager::clearSoundManager()
{
	musicMap.clear();
	sfxMap.clear();
}

void 
SoundManager::clearFromSoundManager(std::string soundId, sound_type type)
{
	if(type == MUSIC)
		musicMap.erase(soundId);
	else if(type == SFX)
		sfxMap.erase(soundId);
}

void
SoundManager::stopSound()
{
	 Mix_HaltMusic();
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

bool 
SoundManager::isEnable()
{
    return soundEnable;
}

void 
SoundManager::setEnable(bool enable)
{
    this->soundEnable = enable;
}



