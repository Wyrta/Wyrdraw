#ifndef _entity_hpp_
#define _entity_hpp_

#include "SDL2/SDL.h"
#include "MapItem.hpp"
#include "WD_Type.hpp"


/*

Dialog
	-ID: int
	-content[16]: char
	-type: enum -> IDLE, MISSION, INFO
*/


class Entity : public MapItem
{
    private:
		float speed;
		WD_Direction orientation;

		char name[32];

		int health;
		bool do_print_health;
		void printHealthBar(SDL_Renderer* render);

    public:
		Entity(const char* e_name);
		~Entity();

		void proc(SDL_Renderer* render);

		bool walk(SDL_Point target_coordinate);
		bool fly(SDL_Point target_coordinate);

		char *talk(void);

		void takeDamages(int damage);
		void onDead(void);
		void fight(Entity* opponent);
};
#endif // _entity_hpp_