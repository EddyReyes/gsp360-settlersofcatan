#include "dv_sdlgrafix.h"

/**
 * @param a_filename
 */
SDL_Surface *load_image(const char * a_filename)
{
	SDL_Surface* loadedImage = NULL;//Temporary storage for the image that's loaded
	SDL_Surface* optimizedImage = NULL;//The optimized image that will be used
	loadedImage = SDL_LoadBMP( a_filename ); //Load the image
	if( loadedImage != NULL )//If nothing went wrong in loading the image
	{ 
		optimizedImage = SDL_DisplayFormat( loadedImage ); //Create an optimized image
		SDL_FreeSurface( loadedImage );//Free the old image
	}
	return optimizedImage;//Return the optimized image
}

/*
 * @param a_transparentRGB (R | G << 8 | B << 16)
 */
void setTransparentColor(SDL_Surface * a_surface, const int & a_transparentRGB)
{
	Uint32 colorkey = SDL_MapRGB( a_surface->format, 	//Map the color key
		0xff & (a_transparentRGB), 
		0xff & (a_transparentRGB >> 8), 
		0xff & (a_transparentRGB >> 16));
	SDL_SetColorKey( a_surface, SDL_SRCCOLORKEY, colorkey );
}

void drawTile(SDL_Surface * a_source, SDL_Rect * a_tile, const int & a_index, SDL_Surface * a_dest, int a_x, int a_y)
{
	int dist = a_index * a_tile->w;
	SDL_Rect src = {dist % a_source->w, (dist / a_source->w) * a_tile->h, a_tile->w, a_tile->h}, dest = {a_x, a_y, 0,0};
	SDL_BlitSurface( a_source, &src, a_dest, &dest); 
}

void drawRect(SDL_Surface * a_surface, SDL_Rect * a_rect, Uint32 a_rgbColor, const int & a_borderSize)
{
	Uint32 formattedColor = SDL_MapRGB( a_surface->format,
		0xff & (a_rgbColor >> 16), 
		0xff & (a_rgbColor >> 8), 
		0xff & (a_rgbColor));
	SDL_Rect border = *a_rect;
	border.h = a_borderSize;
	SDL_FillRect(a_surface, &border, formattedColor);	// top

	border.y = a_rect->y + a_rect->h - a_borderSize;
	SDL_FillRect(a_surface, &border, formattedColor);	// bottom

	if(a_rect->h > a_borderSize*2)
	{
		border.y = a_rect->y + a_borderSize;
		border.h = a_rect->h - a_borderSize*2;
		border.w = a_borderSize;
		SDL_FillRect(a_surface, &border, formattedColor);	// left

		border.x = a_rect->x + a_rect->w - a_borderSize;
		SDL_FillRect(a_surface, &border, formattedColor);	// right
	}
}