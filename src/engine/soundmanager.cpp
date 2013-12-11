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
	std::string realPath = "/opt/warofthenets/resources/";
	int i = (int) path.size() - 1;
	for(; i >= 0; i--)
	{
		if(path[i] == '/')
			break;
	}
	realPath += std::string(path.begin() + i + 1, path.end());
	path = realPath;

	if(type == MUSIC)
	{
		Mix_Music* music = Mix_LoadMUS(path.c_str());

		if(!music)
		{
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
    if(!soundEnable)
        return;
	Mix_PlayMusic(musicMap[musicId], loop);
}

void
SoundManager::playSound(std::string soundId, int loop)
{
    if(!soundEnable)
        return;
	Mix_PlayChannel(-1, sfxMap[soundId], loop);
}

void
SoundManager::stopSound()
{
	 Mix_HaltMusic();
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
	{
		Mix_Music*  music= musicMap[soundId];	
		musicMap.erase(soundId);
		Mix_FreeMusic(music);
	}	
	else if(type == SFX)
	{
		Mix_Chunk *sound = sfxMap[soundId];
		sfxMap.erase(soundId);
		Mix_FreeChunk(sound);
	}
		
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

void
SoundManager::setVolumeSound(int volume)
{
	int percent = (volume * MIX_MAX_VOLUME) / 10;
	Mix_VolumeMusic(percent);
}

void 
SoundManager::setVolumeEffect(int volume)
{
	int percent = (volume * MIX_MAX_VOLUME) / 10;
	Mix_Volume(-1, percent);
}

