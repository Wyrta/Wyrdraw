#ifndef _tilemap_hpp_
#define _tilemap_hpp_

#include "SDL2/SDL.h"

#include "Scene.hpp"
#include "Tile.hpp"
#include "InputManager.hpp"
#include "Entity.hpp"

#define MAX_TILE	1024
#define MAX_ENTITY	32

class TileMap : public Scene
{
	private: 
		SDL_Point coordinate = {0, 0};
		WD_Size size;

		Tile* tile[MAX_TILE];
		Entity* entity[MAX_ENTITY];

		bool on_map_item[MAX_ITEM];

		void load(const char *file_name);

		int entity_to_follow;
	public: 
		TileMap(const char* name);
		~TileMap();

		Tile* addTile(const char* tile_name, TileType tile_type, SDL_Point tile_coo, WD_Direction tile_dir);
		bool addTile(Tile *tile_to_add);
		Tile* getTile(SDL_Point tile_coordinate);

		Entity* addEntity(const char* entity_name, SDL_Point entity_coo);
		bool addEntity(Entity *entity_to_add);
		Entity* getEntity(SDL_Point entity_coordinate);

		void setCoordinate(SDL_Point new_coordinate);
		void move(SDL_Point diff);
		void setFollowEntity(int entity_id);
		void followEntity(void);

		void attachItemToMap(int id);
		void detachItemfromMap(int id);

		void proc(InputManager* input_manager);

		SDL_Point public_coordinate = {0, 0};
};
#endif // _tilemap_hpp_
