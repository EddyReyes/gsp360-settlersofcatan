#include "SDL_music.h"
#include "SDL/SDL_mixer.h"



Music::Music(){}
Music::~Music(){}



void Music::playDiceWAV()
{	
	Mix_Chunk *_dice;
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    _dice = Mix_LoadWAV("dice_sound.wav");
	Mix_PlayChannel( -1, _dice, 0); //    Mix_PlayChannelTimed( -1, _dice, 1, -1);
}
void Music::playCheerWAV()
{	
	Mix_Chunk *_cheer;
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    _cheer = Mix_LoadWAV("cheer_sound.wav");
	Mix_PlayChannel( -1, _cheer, 0); 
}
void Music::playThemeWAV()
{	
	Mix_Chunk *_theme;
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    _theme = Mix_LoadWAV("theme_sound.wav");
   Mix_PlayChannel( -1, _theme, 0); 
}
//void Music::playWAV()
//{	
//	Mix_Chunk *_dice;
//    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
//    _dice = Mix_LoadWAV("dice_sound.wav");
//   Mix_PlayChannelTimed( -1, _dice, 0, -1); //    Mix_PlayChannelTimed( -1, _dice, 1, -1);
//}
void Music::stopMusic()
{
	Mix_Chunk *_dice;
	//Free the sound effects 
	Mix_FreeChunk( _dice); 
	//Mix_FreeChunk( _cheer); 
	//Mix_FreeChunk( _beat); 
	//Quit SDL_mixer 
	Mix_CloseAudio(); 
}

