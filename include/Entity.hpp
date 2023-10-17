#ifndef _entity_hpp_
#define _entity_hpp_

#include "SDL2/SDL.h"
#include "MapItem.hpp"
#include "WD_Type.hpp"
#include "PathFinder.hpp"
#include "Tile.hpp"


/*

Dialog
	-ID: int
	-content[16]: char
	-type: enum -> IDLE, MISSION, INFO
*/


class Entity : public MapItem
{
	private:
		float speed;	// tile per tick
		int last_move;
		WD_Direction orientation;

		char name[32];

		int health;
		bool do_print_health;
		void printHealthBar(void);

		Tile* current_tile;

	public:
		Entity(const char* e_name);
		~Entity();

		void setTile(Tile* tile);

		void proc(void);

		bool walk(SDL_Point diff, Tile* tile = NULL);
		bool walkTo(SDL_Point coo, Tile* tile = NULL);
		bool goTo(SDL_Point coo, Tile **tilemap, int size);

		float getSpeed(void);


		char *talk(void);

		void takeDamages(int damage);
		int  dealDamages(void);
		void onDead(void);
		
		PathFinder *pathfinder;
};
#endif // _entity_hpp_