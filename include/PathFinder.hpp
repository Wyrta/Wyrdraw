#ifndef _pathfinder_hpp_
#define _pathfinder_hpp_

#include "SDL2/SDL.h"
#include "Tile.hpp"

#define MAX_PATH_LENGTH		512

typedef struct _path
{
	int id;
	SDL_Point coordinate;
	_path* next;
	_path* previous;
	Tile* tile;
} Path;

class PathFinder
{
	private:
		SDL_Point src, dst;

		Tile** tiles;
		int tilemap_size;

		Path* itinerary[MAX_PATH_LENGTH];

		bool itinerary_done;
		int current_path;

		void addPath(SDL_Point coordinate);
		Path* getPath(SDL_Point coordinate);
		
		Tile* getTile(SDL_Point tile_coordinate);
		Tile* findTile(WD_Direction direction, SDL_Point coo);

		Tile* findNorth(SDL_Point coo);
		Tile* findSouth(SDL_Point coo);
		Tile* findWest(SDL_Point coo);
		Tile* findEast(SDL_Point coo);

	public:
		PathFinder();
		~PathFinder();

		void setTilemap(Tile* tilemap[], int size);
		void setSource(SDL_Point coordinate);
		void setDestination(SDL_Point coordinate);

		void find(void);

		Path* getFirst(void);
		Path* getNext(SDL_Point coordinate);
		Path* getPrevious(SDL_Point coordinate);

		void print_path(void);

};
#endif // _pathfinder_hpp_