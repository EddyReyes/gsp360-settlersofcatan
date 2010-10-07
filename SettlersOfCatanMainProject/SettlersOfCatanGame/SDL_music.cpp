#include "SDL_music.h"
#include "SDL/SDL_mixer.h"



Music::Music(){}
Music::~Music(){}

Mix_Chunk *_dice;

void Music::playWAV()
{ 
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    _dice = Mix_LoadWAV("dice_sound.wav");
   Mix_PlayChannelTimed( -1, _dice, 0, -1); //    Mix_PlayChannelTimed( -1, _dice, 1, -1);
}

void Music::stopMusic()
{
	//Free the sound effects 
	Mix_FreeChunk( _dice); 
	//Mix_FreeChunk( _cheer); 
	//Mix_FreeChunk( _beat); 
	//Quit SDL_mixer 
	Mix_CloseAudio(); 
}

