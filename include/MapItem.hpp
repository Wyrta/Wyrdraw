#ifndef _mapitem_hpp_
#define _mapitem_hpp_

#include "SDL2/SDL.h"
#include "GraphicItem.hpp"
#include "WD_Type.hpp"

class MapItem : public GraphicItem
{
    private:
		SDL_Point coordinate;
		SDL_Point* map_coordinate;

    public:
		MapItem();
		~MapItem();

		void render(SDL_Renderer* render, SDL_Point offset = {0,0});

		SDL_Point getCoordinate(void);
		void setCoordinate(SDL_Point new_coordinate);
		void followMap(SDL_Point* new_map_coordinate);
		void move(SDL_Point diff);

		static WD_Size tile_size;

		static MapItem* newMapItem(const char* path, SDL_Point coordinate = EMPTY_POINT, SDL_Rect hitbox = EMPTY_RECT, SDL_Rect mask = EMPTY_RECT);
};
#endif // _mapitem_hpp_