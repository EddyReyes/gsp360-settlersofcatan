#include "SDL_music.h"
#include "SDL/SDL_mixer.h"

	////initializing gameSound
	//gameSound = new sound();

Music::Music(){fillMusic(); volume = 100;}
Music::~Music(){}

bool Music::fillMusic()
{	
//Load the music
	soundArray = new string[3];
	soundArray[0] =  "beat.wav";
	soundArray[1] = "crowdcheer.wav";
	soundArray[2] = "Dice.wav";
	return true;
}
void Music::playWAV(int wav)
{
    Mix_Chunk *music;
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    music = Mix_LoadWAV(soundArray[wav].c_str());
	Mix_Volume(wav, volume);
    Mix_PlayChannel(wav,music,-1);
}
void Music::increaseVolume(int chan, int amount)
{
	volume+= amount;
	Mix_Volume(chan,volume);
}
void Music::decreaseVolume(int chan, int amount)
{
	volume-= amount;
	Mix_Volume(chan,volume);
}
void Music::stopMusic(int chan)
{
	Mix_Pause(chan);

}

