#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "sdl/sdl_mixer.h"
#include "sdl/sdl.h"
#include <string>
using namespace std;

class Music
{
private:

void loadSounds();
public:

	//Music constructor
	Music();
	//Music Deconstructor
	~Music();
	/*void playWAV();*/
	
	void play_diceWAV();
	void play_cheerWAV();
	void play_musicWAV();
	void stopMusic();

};