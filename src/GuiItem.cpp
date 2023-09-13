#include "GuiItem.hpp"


SDL_Point GuiItem::getCoordinate(void)
{
	return (coordinate);
}


void GuiItem::setCoordinate(SDL_Point coo)
{
	coordinate = coo;
}


WD_Size GuiItem::getSize(void)
{
	return (size);
}


void GuiItem::setSize(WD_Size siz)
{
	size = siz;
}

void GuiItem::setSize(SDL_Rect rect)
{
	size.h = rect.h;
	size.w = rect.w;
}

SDL_Rect GuiItem::getHitbox(void)
{
	SDL_Rect hitbox;
	hitbox.x = coordinate.x;
	hitbox.y = coordinate.y;
	hitbox.w = size.w;
	hitbox.h = size.h;

	return (hitbox);
}

