#include "SDL_music.h"
#include "SDL/SDL_mixer.h"



Music::Music(){}
Music::~Music(){}

//Dice Roll sound effect
Mix_Chunk *_dice;
Mix_Chunk *_cheer;

//The BACKGROUND music that will be played
Mix_Music *_music;


void Music::play_diceWAV()
{ 
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    _dice = Mix_LoadWAV("dice_sound.wav");
   Mix_PlayChannel( -1, _dice, 0); 
}

void Music::play_cheerWAV()
{ 
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    _cheer = Mix_LoadWAV("cheer_sound.wav");
   Mix_PlayChannel( -1,_cheer , 0); 
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
	Mix_FreeChunk( _cheer);
	Mix_FreeMusic( _music); 

	//Stop the music
     Mix_HaltMusic();
	 _dice = NULL; 
	 _music = NULL;
	 _cheer = NULL;
	Mix_CloseAudio(); 

}

