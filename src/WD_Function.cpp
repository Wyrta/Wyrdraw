#include "WD_Function.hpp"
#include "WD_Type.hpp"

#include <iostream>



bool operator==(WD_Size size1, WD_Size size2)
{
	if (size1.w == size2.w && size1.h == size2.h)
		return (true);
	else
		return (false);
}

bool operator!=(WD_Size size1, WD_Size size2)
{
	if (size1.w != size2.w || size1.h != size2.h)
		return (true);
	else
		return (false);
}

bool operator==(SDL_Point pos1, SDL_Point pos2)
{
	if (pos1.x == pos2.x && pos1.y == pos2.y)
		return (true);
	else
		return (false);
}

bool operator!=(SDL_Point pos1, SDL_Point pos2)
{
	if (pos1.x != pos2.x || pos1.y != pos2.y)
		return (true);
	else
		return (false);
}


bool operator==(SDL_Rect rect, int value)
{
	if (rect.x == value && rect.y == value && rect.w == value && rect.h == value)
		return (true);
	else
		return (false);
}


bool operator!=(SDL_Rect rect, int value)
{
	if (rect.x != value || rect.y != value || rect.w != value || rect.h != value)
		return (true);
	else
		return (false);
}


SDL_Point operator-(SDL_Point pos1, SDL_Point pos2)
{
	SDL_Point res;
	res.x = pos1.x - pos2.x;
	res.y = pos1.y - pos2.y;

	return (res);
}


SDL_Point operator+(SDL_Point pos1, SDL_Point pos2)
{
	SDL_Point res;
	res.x = pos1.x + pos2.x;
	res.y = pos1.y + pos2.y;

	return (res);
}

bool RectCollide(SDL_Rect rect1, SDL_Rect rect2)
{
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		rect1.h + rect1.y > rect2.y) 
	{
		return (true);
	}
	else
	{
		return (false);

	}
}


SDL_Texture *createTexture(SDL_Renderer* render, SDL_Rect* rectangle, const char* path)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;

	surface = IMG_Load(path);

	if (surface == NULL)
	{
		std::cerr << "Create texture : \"" << path << "\": " << SDL_GetError() << std::endl;
		return (NULL);
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	if(rectangle != NULL)
		SDL_QueryTexture(texture, NULL, NULL, &rectangle->w, &rectangle->h);

	return (texture);
}


TTF_Font *createFont(const char *path, int size)
{
	TTF_Font *font = NULL;
	font = TTF_OpenFont(path, size);

	if (!font)
	{
		std::cerr << "Opening font (" << path << ") " << SDL_GetError() << std::endl;
	}
	
	return (font);
}


SDL_Texture *write(SDL_Renderer* render, SDL_Rect *rect, TTF_Font *font, const char *text, SDL_Color color)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;

	surface = TTF_RenderText_Solid(font, text, color);

	texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) 
	{
		std::cerr << "Create texte texture : texture NULL" << std::endl;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
	}

	return (texture);
}


bool isRectEmpty(SDL_Rect rect)
{
	if (rect.x == 0 && 
		rect.y == 0 && 
		rect.w == 0 && 
		rect.h == 0)
		return (true);
	else
		return (false);
}

std::string printDirection(WD_Direction dir)
{
    #define PROCESS_VAL(p) case(p): return #p;
        switch(dir){
			PROCESS_VAL(NORTH);
			PROCESS_VAL(NORTH_WEST);
			PROCESS_VAL(NORTH_EAST);
			PROCESS_VAL(SOUTH);
			PROCESS_VAL(SOUTH_WEST);
			PROCESS_VAL(SOUTH_EAST);
			PROCESS_VAL(WEST);
			PROCESS_VAL(EAST);
			PROCESS_VAL(ALL);
			PROCESS_VAL(NONE);
        }
    #undef PROCESS_VAL

	return ((std::string)"ERROR");
}
