#ifndef _tilemap_hpp_
#define _tilemap_hpp_

#include "SDL2/SDL.h"

#include "Scene.hpp"
#include "Tile.hpp"
#include "InputManager.hpp"

#define MAX_TILE	512

class TileMap : public Scene
{
	private: 
		SDL_Point coordinate = {0, 0};
		WD_Size size;

		Tile* tile[MAX_TILE];

		bool on_map_item[MAX_ITEM];

		void load(const char *file_name);


	public: 
		TileMap(const char* name);
		~TileMap();

		Tile* addTile(const char* tile_name, TileType tile_type, SDL_Point coo);
		bool addTile(Tile *tile_to_add);

		void setCoordinate(SDL_Point new_coordinate);
		void move(SDL_Point diff);

		void attachItemToMap(int id);
		void detachItemfromMap(int id);

		void proc(InputManager* input_manager);

};
#endif // _tilemap_hpp_
