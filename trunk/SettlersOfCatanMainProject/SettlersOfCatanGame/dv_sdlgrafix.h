#pragma once

#include "SDL/SDL.h"

// TODO http://www.libsdl.org/cgi/docwiki.cgi/Introduction_to_SDL_Video

/**
 * @param a_filename bitmap image to load
 */
SDL_Surface *load_image(const char * a_filename);

/**
 * @param a_surface the surface to make the transparency change to
 * @param a_transparentRGB (R | G << 8 | B << 16)
 */

//just commented out
void setTransparentColor(SDL_Surface * a_surface, 
						 const int & a_transparentRGB);

/**
 * @param a_source the SDL surface (tile bitmap) to treat as the tile source
 * @param a_tileSize an SDL_Rect who's width and height values are the width
 * and height of the tiles in the tile source
 * @param a_index the tile from the tile source to draw, with the upper-left
 * most tile being index 0.
 * @param a_dest what surface to draw the tile to
 * @param a_x
 * @param a_y coordinate to draw the tile to on the destination surface
 */
void drawTile(SDL_Surface * a_source, SDL_Rect * a_tileSize, 
			  const int & a_index, SDL_Surface * a_dest, int a_x, int a_y);

/** draws the given rectangle using the given 0xRRGGBB color */
void drawRect(SDL_Surface * a_surface, SDL_Rect * a_rect, Uint32 a_rgbColor, 
			  const int & a_borderSize);