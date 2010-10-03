#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "SDL/SDL_mixer.h"
#include "sdl/sdl.h"
#include <string>
using namespace std;

enum SoundFX
{
	beat, Dice, crowdcheer/*, Music2, effect1, effect2*/
};


class Music
{
private:
	int volume;

public:
	//Music constructor
	Music();
	//Music Deconstructor
	~Music();
	//Music Array
	string *soundArray;
	void playWAV(int);
	bool fillMusic();
	void increaseVolume(int, int);
	void decreaseVolume(int, int);
	void stopMusic(int);

};