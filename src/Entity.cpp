#include "Entity.hpp"
#include "SDL2/SDL.h"
#include <iostream>
#include "WD_Function.hpp"

Entity::Entity(const char* e_name) : MapItem()
{
	SDL_strlcpy(name, e_name, 32);

	speed = 0.25;
	health = 100;
	orientation = WD_Direction::NONE;
	last_move = 0;
	pathfinder = NULL;

	current_tile = NULL;
}


Entity::~Entity()
{

}

void Entity::setTile(Tile* tile)
{
	current_tile = tile;
	setCoordinate(current_tile->getCoordinate());
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
	// if current_tile deal damages ?

	if (pathfinder != NULL)
	{
		Path* path = pathfinder->getNext(getCoordinate());

		if (path != NULL)
		{
			walkTo(path->coordinate);
			pathfinder->print_path(render);
		}
		else
		{
			delete (pathfinder);
			pathfinder = NULL;
		}
	}

	MapItem::render(render);
	if (do_print_health)
		printHealthBar(render);

	last_move++;
}


bool Entity::walk(SDL_Point diff, Tile* tile)
{
	SDL_Point coo = getCoordinate();
	WD_Direction dir;

	if (diff == (SDL_Point){0,0})
	{
		if (tile != NULL)
			current_tile = tile;
			
		return (true);
	}

	if (diff.x > 1 || diff.x < -1 || diff.y > 1 || diff.y < -1)
	{
		std::cout << "Entity::walk(...) To far away : " << printPoint(coo) << printPoint(diff) << std::endl;
		std::cout << "Try enable pathfinding" << std::endl;

		return (false);
	}

	if (last_move * speed < 1)
	{
		// std::cout << "Entity::walk(...) Cannot walk yet : " << last_move << " * " << speed << " = " << last_move * speed << std::endl;

		return (false);
	}

	if (diff.x == 1)
		dir = WD_Direction::EAST;
	else if (diff.x == -1)
		dir = WD_Direction::WEST;
	else if (diff.y == 1)
		dir = WD_Direction::SOUTH;
	else if (diff.y == -1)
		dir = WD_Direction::NORTH;
	else 
		dir = WD_Direction::NONE;

	if (tile == NULL && current_tile != NULL)
	{
		if (diff.x == 1)
			tile = current_tile->east;
		else if (diff.x == -1)
			tile = current_tile->west;
		else if (diff.y == 1)
			tile = current_tile->south;
		else if (diff.y == -1)
			tile = current_tile->north;
	}

	if (tile == NULL)
	{
		// std::cout << "Entity::walk(...) No tile found : " << printDirection(dir) << std::endl;
		return (false);
	}

	if (!tile->canWalk(dir))
	{
		// std::cout << "Entity::walk(...) Cannot walk there : " << printDirection(dir) << std::endl;
		return (false);
	}

	last_move = 0;
	move(diff);
	coo = getCoordinate();
	current_tile = tile;
	orientation = dir;

	return (true);
}


bool Entity::walkTo(SDL_Point coo, Tile* tile)
{
	SDL_Point diff, current_coo;
	bool retval;

	current_coo = getCoordinate();

	diff = coo - current_coo;

	retval = walk(diff, tile);

	return (retval);
}


bool Entity::goTo(SDL_Point coo, Tile **tilemap, int size)
{
	if (pathfinder == NULL)
	{
		pathfinder = new PathFinder();
	}
	else
	{
		delete (pathfinder);
		pathfinder = new PathFinder();
	}

	pathfinder->setSource(getCoordinate());
	pathfinder->setDestination(coo);
	pathfinder->setTilemap(tilemap, size);

	pathfinder->find();

	return (true);
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


int Entity::dealDamages(void)
{
	std::cout << "Entity::dealDamages(void) not implemented" << std::endl;
	return (0);
}



void Entity::onDead(void)
{
	std::cout << name << "is dead" << std::endl;
	std::cout << "Entity::onDead(void) not implemented" << std::endl;

}
