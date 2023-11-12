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

		Tile* tile;

		Path* itinerary[MAX_PATH_LENGTH];

		bool itinerary_done;
		int current_path;

		void addPath(Tile* added_tile);
		Path* getPath(SDL_Point coordinate);
		
		Tile* getTile(SDL_Point tile_coordinate);
		Tile* findTile(WD_Direction direction, SDL_Point coo);

		Tile* findNorth(Tile* current_tile);
		Tile* findSouth(Tile* current_tile);
		Tile* findWest(Tile* current_tile);
		Tile* findEast(Tile* current_tile);

		Tile* findClosest(Tile* current_tile, WD_Direction target, WD_Direction choice1, WD_Direction choice2);

	public:
		PathFinder();
		~PathFinder();

		void setSource(Tile* source);
		void setDestination(SDL_Point coordinate);

		void find(void);

		Path* getFirst(void);
		Path* getNext(SDL_Point coordinate);
		Path* getPrevious(SDL_Point coordinate);

		void print_path(void);

};
#endif // _pathfinder_hpp_