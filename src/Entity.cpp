#include "Entity.hpp"
#include "SDL2/SDL.h"
#include <iostream>

Entity::Entity(const char* e_name) : MapItem()
{
	SDL_strlcpy(name, e_name, 32);

	speed = 1.0;
	health = 100;
	orientation = WD_Direction::NONE;
}


Entity::~Entity()
{

}

void Entity::printHealthBar(SDL_Renderer* render)
{

	SDL_Rect health_bar = getHitbox();
	//health_bar.x;
	health_bar.y = health_bar.y - 20;
	//health_bar.w = health_bar.w * health / 100;
	health_bar.h = 16;

	SDL_SetRenderDrawColor(render, 117, 69, 11, 255);
	SDL_RenderFillRect(render, &health_bar);

	health_bar.x += 2;
	health_bar.y += 2;
	health_bar.w -= 4;
	health_bar.h -= 4;

	SDL_SetRenderDrawColor(render, 92, 45, 6, 255);
	SDL_RenderFillRect(render, &health_bar);

	health_bar.w = (int)((float)health_bar.w * (float)health / (float)100);

	SDL_SetRenderDrawColor(render, 250, 68, 40, 255);
	SDL_RenderFillRect(render, &health_bar);
}



void Entity::proc(SDL_Renderer* render)
{
	MapItem::render(render);
	if (do_print_health)
		printHealthBar(render);
}


bool Entity::walk(SDL_Point target_coordinate)
{
	std::cout << "Entity::walk(SDL_Point ) not implemented" << std::endl;
return false;
	//orientation

}


bool Entity::fly(SDL_Point target_coordinate)
{
	std::cout << "Entity::fly(SDL_Point ) not implemented" << std::endl;
	//orientation

return false;
}


char *Entity::talk(void)
{
	std::cout << "Entity::talk(void) not implemented" << std::endl;

return NULL;
}

void Entity::takeDamages(int damage)
{
	health -= damage;

	if (health <= 0)
	{
		onDead();
		health = 0;
	}
}


void Entity::onDead(void)
{
	std::cout << name << "is dead" << std::endl;
	std::cout << "Entity::onDead(void) not implemented" << std::endl;

}


void Entity::fight(Entity* opponent)
{
	std::cout << "Entity::fight(Entity* ) not implemented" << std::endl;

}

