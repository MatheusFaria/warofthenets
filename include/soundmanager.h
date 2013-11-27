#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "SDL2/SDL_mixer.h"
#include <string>
#include <map>

enum sound_type
{
	MUSIC = 0,
	SFX = 1
};

class SoundManager{

public:

	static SoundManager* Instance();

	bool loadSound(std::string path, std::string soundId, sound_type type);

	void playSound(std::string soundId, int loop);
	void playMusic(std::string musicId, int loop);
	
	void stopSound();

	void clearSoundManager();
	void clearFromSoundManager(std::string soundId, sound_type type);
    
    bool isEnable();
    void setEnable(bool enable);

private:

	static SoundManager* instance;	

	std::map<std::string, Mix_Chunk*> sfxMap;
	std::map<std::string, Mix_Music*> musicMap;

	SoundManager();
	~SoundManager();
    
	bool soundEnable;
};

#endif
