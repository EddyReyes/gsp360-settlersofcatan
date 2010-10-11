#include "SDL_music.h"
#include "SDL/SDL_mixer.h"



Music::Music(){}
Music::~Music(){}

//Dice Roll sound effect
Mix_Chunk *_dice;

//The BACKGROUND music that will be played
Mix_Music *_music;

//Mix_Chunk *_dice;
//Mix_Chunk *_dice;


void Music::play_diceWAV()
{ 
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    _dice = Mix_LoadWAV("dice_sound.wav");
   Mix_PlayChannel( -1, _dice, 0); //    Mix_PlayChannelTimed( -1, _dice, 1, -1);
}
void Music::play_musicWAV()
{ 
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	//Load the music
	_music = Mix_LoadMUS("music_sound.wav");
	Mix_PlayMusic( _music, -1 );
}

void Music::stopMusic()
{
	//Free the sound effects 
	Mix_FreeChunk( _dice); 
	//Mix_FreeChunk( _cheer); 
	//Mix_FreeChunk( _beat); 
	/*Quit SDL_mixer;*/
	Mix_CloseAudio(); 
}

