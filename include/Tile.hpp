#ifndef _tile_hpp_
#define _tile_hpp_

#include "SDL2/SDL.h"

#include "MapItem.hpp"
#include "WD_Type.hpp"



typedef enum {
	DIRT = 0,
	DIRT_PATH_1,
	DIRT_PATH_2,
	DIRT_PATH_3,
	DIRT_PATH_4,
	DIRT_NE_GRASS,
	DIRT_NW_GRASS,
	DIRT_SE_GRASS,
	DIRT_SW_GRASS,
	GRASS_E_W_DIRT,
	GRASS_N_S_DIRT,
	GRASS_NE_DIRT,
	GRASS_NW_DIRT,
	GRASS_S_N_DIRT,
	GRASS_SE_DIRT,
	GRASS_SW_DIRT,
	GRASS_W_E_DIRT,
	GRASS_1,
	GRASS_2,
	GRASS_3,
	TINYBUSH_1,
	TINYBUSH_2,
	TINYBUSH_3,
	TINYBUSH_4,
	EMPTY,
	LAST_TTYPE		/* Dont use */
} TileType;


class Tile : public MapItem
{
	private: 
		WD_Direction walk_stat;



	public: 
		Tile(const char* name, TileType type, SDL_Point coo, WD_Direction dir);
		~Tile();

		WD_Direction canWalk(void);
		bool canWalk(WD_Direction direction);
		void setWalk(WD_Direction direction);

		static int size;
		static void loadTexture(void);
		static TileType getTiletype(const char* str);
		static WD_Direction getTileDirection(const char* str);
		static SDL_Texture *texture[TileType::LAST_TTYPE];

		Tile* north;
		Tile* south;
		Tile* west;
		Tile* east;
};
#endif // _tile_hpp_