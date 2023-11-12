#include "Entity.hpp"
#include "SDL2/SDL.h"
#include "Log.hpp"
#include "WD_Function.hpp"
#include "RenderQueue.hpp"

extern RenderQueue* renderQueue;


Entity::Entity(const char* e_name, EntityType entity_type) : MapItem()
{
	SDL_strlcpy(name, e_name, 32);

	speed = 0.25;
	health = 100;
	orientation = NONE;
	last_move = 0;
	pathfinder = NULL;

	current_tile = NULL;

	type = entity_type;
}


Entity::~Entity()
{

}

void Entity::setTile(Tile* tile)
{
	current_tile = tile;
	setCoordinate(current_tile->getCoordinate());
}


void Entity::printHealthBar(void)
{
	SDL_Rect health_bar = getHitbox();
	//health_bar.x;
	health_bar.y = health_bar.y - 20;
	//health_bar.w = health_bar.w * health / 100;
	health_bar.h = 16;

	renderQueue->addItem((new RenderItem())->setRectangle(health_bar, {117, 69, 11, 255}));

	health_bar.x += 2;
	health_bar.y += 2;
	health_bar.w -= 4;
	health_bar.h -= 4;

	renderQueue->addItem((new RenderItem())->setRectangle(health_bar, {92, 45, 6, 255}));

	health_bar.w = (int)((float)health_bar.w * (float)health / (float)100);

	renderQueue->addItem((new RenderItem())->setRectangle(health_bar, {250, 68, 40, 255}));
}


void Entity::procPathfinder(void)
{
	if (pathfinder == NULL)
		return;

	Path* path = pathfinder->getNext(getCoordinate());

	if (path != NULL)
	{
		walkTo(path->coordinate);
		pathfinder->print_path();
	}
	else
	{
		delete (pathfinder);
		pathfinder = NULL;
	}
}


SDL_Point Entity::procMove(void)
{
	SDL_Point offset = {0,0};

	if (last_move * speed < 1)
	{
		WD_Size step;
		step.w = MapItem::tile_size.w - (MapItem::tile_size.w * last_move * speed);
		step.h = MapItem::tile_size.h - (MapItem::tile_size.h * last_move * speed);

		switch (orientation)
		{
			case NORTH:
				offset.y = step.h;
				break;
			case SOUTH:
				offset.y = -step.h;
				break;
			case WEST:
				offset.x = step.w;
				break;
			case EAST:
				offset.x = -step.w;
				break;
			case NORTH_WEST:
			case SOUTH_WEST:
			case NORTH_EAST:
			case SOUTH_EAST:
			case ALL:
				Log::warn("Entity direction not supported");
			case NONE:
			default:
				break;
		}
	}

	return (offset);
}

void Entity::updateOrder(InputManager* input_manager)
{
	if (input_manager->mouseGetTile(BUTTON_LEFT) != NULL && input_manager->mouseClicked(BUTTON_LEFT))
	{
		goTo(input_manager->mouseGetTile(BUTTON_LEFT));
	}

	if (input_manager->keyMaintained(SDLK_d))
	{
		walk({1, 0});
	}
	else if (input_manager->keyMaintained(SDLK_q))
	{
		walk({-1, 0});
	}
	else if (input_manager->keyMaintained(SDLK_z))
	{
		walk({0, -1});
	}
	else if (input_manager->keyMaintained(SDLK_s))
	{
		walk({0, 1});
	}
	if (input_manager->keyMaintained(SDLK_SPACE))
	{
		takeDamages(2);
	}
}


void Entity::proc(void)
{
	procPathfinder();

	SDL_Point offset;
	offset = procMove();

	MapItem::proc(offset);

	// if current_tile deal damages ?

	current_tile->highlight();

	if (do_print_health)
		printHealthBar();

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
		Log::error("Entity::walk(...) To far away : %s %s", printPoint(coo), printPoint(diff));
		Log::error("Try enable pathfinding");

		return (false);
	}

	if (last_move * speed < 1)
	{
		return (false);
	}

	if (diff.x == 1)
		dir = EAST;
	else if (diff.x == -1)
		dir = WEST;
	else if (diff.y == 1)
		dir = SOUTH;
	else if (diff.y == -1)
		dir = NORTH;
	else 
		dir = NONE;

	if (tile == NULL && current_tile != NULL)
	{
		if (diff.x == 1)
			tile = current_tile->get(EAST);
		else if (diff.x == -1)
			tile = current_tile->get(WEST);
		else if (diff.y == 1)
			tile = current_tile->get(SOUTH);
		else if (diff.y == -1)
			tile = current_tile->get(NORTH);
	}

	if (tile == NULL)
	{
		Log::warn("No tile found : %s", printDirection(dir));
		return (false);
	}

	if (!tile->canWalk(dir))
	{
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


bool Entity::goTo(Tile* tile)
{
	if (pathfinder != NULL)
		delete (pathfinder);

	pathfinder = new PathFinder();

	pathfinder->setSource(current_tile);
	pathfinder->setDestination(tile->getCoordinate());

	pathfinder->find();

	return (true);
}


float Entity::getSpeed(void)
{
	return (speed);
}


char *Entity::talk(void)
{
	Log::debug("Entity::talk(void) not implemented");

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
	Log::debug("Entity::dealDamages(void) not implemented");
	return (0);
}



void Entity::onDead(void)
{
	Log::info("%s is dead", name);
	Log::debug("Entity::onDead(void) not implemented");
}
