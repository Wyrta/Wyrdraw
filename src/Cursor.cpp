#include "Cursor.hpp"
#include "Parameters.hpp"

extern Parameters param;

Cursor::Cursor() : GraphicItem()
{
	SDL_Rect rect;
	SDL_Texture* new_texture = createTexture(param.getRenderer(), &rect, "../assets/img/artoria.png");
	setTexture(new_texture);

	rect.w = rect.h = 60;

	setHitbox(rect);

	SDL_ShowCursor(SDL_DISABLE);
}


Cursor::~Cursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}

