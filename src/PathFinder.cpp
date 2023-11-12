#include "PathFinder.hpp"
#include "WD_Function.hpp"

#include "Log.hpp"

#include "Parameters.hpp"
#include "RenderQueue.hpp"

extern RenderQueue* renderQueue;
extern Parameters param;

PathFinder::PathFinder()
{
	for (int i = 0; i < MAX_PATH_LENGTH; i++)
	{
		itinerary[i] = NULL;
	}

	tile = NULL;

	current_path = -1;

	itinerary_done = false;

	src = EMPTY_POINT;
	dst = EMPTY_POINT;
}


PathFinder::~PathFinder()
{
	for (int i = 0; i < MAX_PATH_LENGTH; i++)
	{
		if (itinerary[i] == NULL)
			continue;

		SDL_free(itinerary[i]);
		itinerary[i] = NULL;
	}

	tile = NULL;
}


void PathFinder::addPath(Tile* added_tile)
{
	Path* path = NULL;

	if (current_path+1 >= MAX_PATH_LENGTH)
		return;

	if (itinerary[current_path+1] != NULL)
		return;
	
	current_path++;

	itinerary[current_path] = (Path *)SDL_malloc(sizeof(Path));

	path = itinerary[current_path];

	path->id = current_path;
	path->coordinate = added_tile->getCoordinate();
	path->tile = added_tile;

	path->previous = itinerary[current_path-1];
	path->next = NULL;

}


Path* PathFinder::getPath(SDL_Point coordinate)
{
	for (int i = 0; i < MAX_PATH_LENGTH; i++)
	{
		if (itinerary[i] == NULL)
			continue;

		if (itinerary[i]->coordinate == coordinate)
			return (itinerary[i]);
	}

	return (NULL);
}


Tile* PathFinder::getTile(SDL_Point tile_coordinate)
{
	int x, y;
	Tile* moving_tile = tile;
	SDL_Point current_pos;

	current_pos = moving_tile->getCoordinate();
	x = current_pos.x;
	y = current_pos.y;
	
	while (tile_coordinate != current_pos)
	{
		if (x < tile_coordinate.x)
			moving_tile = moving_tile->get(EAST);

		if (x > tile_coordinate.x)
			moving_tile = moving_tile->get(WEST);

		if (y > tile_coordinate.y)
			moving_tile = moving_tile->get(NORTH);

		if (y < tile_coordinate.y)
			moving_tile = moving_tile->get(SOUTH);

		current_pos = moving_tile->getCoordinate();
		x = current_pos.x;
		y = current_pos.y;
	}

	return (tile);
}


void PathFinder::setSource(Tile* source)
{
	tile = source;
	src = tile->getCoordinate();
}


void PathFinder::setDestination(SDL_Point coordinate)
{
	dst = coordinate;
}

WD_Direction getDirection(double angle)
{
	WD_Direction direction;

	if (angle > (-M_PI)/2 && angle < M_PI/8)
		direction = WEST;

	if (angle >= M_PI/8 && angle <= (3*M_PI)/8)
		direction = NORTH_WEST;	

	if (angle > (3*M_PI)/8 && angle < (5*M_PI)/8)
		direction = NORTH;	

	if (angle >= (5*M_PI)/8 && angle <= (7*M_PI)/8)
		direction = NORTH_EAST;	

	if (angle > (7*M_PI)/8 || angle < (-7*M_PI)/8)
		direction = EAST;	

	if (angle >= (-7*M_PI)/8 && angle <= (-5*M_PI)/8)
		direction = SOUTH_EAST;	

	if (angle > (-5*M_PI)/8 && angle < (-3*M_PI)/8)
		direction = SOUTH;	

	if (angle >= (-3*M_PI)/8 && angle <= (-1*M_PI)/8)
		direction = SOUTH_WEST;	

	return (direction);
}


Tile* PathFinder::findNorth(Tile* current_tile)
{
	Tile* founded_tile = NULL;

	if (current_tile->get(NORTH) == NULL)
		return (current_tile);

	if (current_tile->get(NORTH)->canWalk(NORTH))
		founded_tile = current_tile->get(NORTH);
	else
		founded_tile = findClosest(current_tile, NORTH, WEST, EAST);

	return (founded_tile);
}


Tile* PathFinder::findSouth(Tile* current_tile)
{
	Tile* founded_tile = NULL;

	if (current_tile->get(SOUTH) == NULL)
		return (current_tile);

	if (current_tile->get(SOUTH)->canWalk(SOUTH))
		founded_tile = current_tile->get(SOUTH);
	else
		founded_tile = findClosest(current_tile, SOUTH, WEST, EAST);


	return (founded_tile);
}


Tile* PathFinder::findWest(Tile* current_tile)
{
	Tile* founded_tile = NULL;

	if (current_tile->get(WEST) == NULL)
		return (current_tile);

	if (current_tile->get(WEST)->canWalk(WEST))
		founded_tile = current_tile->get(WEST);
	else
		founded_tile = findClosest(current_tile, WEST, NORTH, SOUTH);

	return (founded_tile);
}


Tile* PathFinder::findEast(Tile* current_tile)
{
	Tile* founded_tile = NULL;

	if (current_tile->get(EAST) == NULL)
		return (current_tile);

	if (current_tile->get(EAST)->canWalk(EAST))
		founded_tile = current_tile->get(EAST);
	else
		founded_tile = findClosest(current_tile, EAST, NORTH, SOUTH);

	return (founded_tile);
}


Tile* PathFinder::findClosest(Tile* current_tile, WD_Direction target, WD_Direction choice1, WD_Direction choice2)
{
	Tile* tmp = NULL;

	int number1 = 0, number2 = 0;

	tmp = current_tile;
	while (!tmp->get(target)->canWalk(target))
	{
		tmp = tmp->get(choice1);
		number1++;
		if (tmp == NULL)
		{
			number1 = 1024;
			break;
		}
	}

	tmp = current_tile;
	while (!tmp->get(target)->canWalk(target))
	{
		tmp = tmp->get(choice2);
		number2++;
		if (tmp == NULL)
		{
			number2 = 1024;
			break;
		}
	}

	if (number1 < number2)
		tmp = current_tile->get(choice1);
	else
		tmp = current_tile->get(choice2);

	return (tmp);
}


void PathFinder::find(void)
{
	Log::info("Start finding path from %s to %s", printPoint(src), printPoint(dst) );

	if (src == dst)
		return;

	if (tile == NULL)
		return;

	SDL_Point pos = src;
	Tile* current_tile = tile;
	Tile* next_tile = current_tile;
	int path_length = 0;

	addPath(tile);

	int max_i = 32, i= 0;

	while (pos != dst)
	{
/*
		if (abs(dst.x - pos.x) > abs(dst.y - pos.y))
		{
			if (pos.x < dst.x && current_tile == next_tile)
				next_tile = findEast(current_tile);
		
			if (pos.x > dst.x && current_tile == next_tile)
				next_tile = findWest(current_tile);
		}
		else
		{
			if (pos.y > dst.y && current_tile == next_tile)
				next_tile = findNorth(current_tile);

			if (pos.y < dst.y && current_tile == next_tile)
				next_tile = findSouth(current_tile);
		}

		if (abs(dst.x - pos.x) < abs(dst.y - pos.y))
		{
			if (pos.x < dst.x && current_tile == next_tile)
				next_tile = findEast(current_tile);
		
			if (pos.x > dst.x && current_tile == next_tile)
				next_tile = findWest(current_tile);
		}
		else
		{
			if (pos.y > dst.y && current_tile == next_tile)
				next_tile = findNorth(current_tile);

			if (pos.y < dst.y && current_tile == next_tile)
				next_tile = findSouth(current_tile);
		}
*/
		if (pos.x < dst.x && current_tile == next_tile)
			next_tile = findEast(current_tile);
	
		if (pos.x > dst.x && current_tile == next_tile)
			next_tile = findWest(current_tile);

		if (pos.y < dst.y && current_tile == next_tile)
			next_tile = findSouth(current_tile);
			
		if (pos.y > dst.y && current_tile == next_tile)
			next_tile = findNorth(current_tile);


		pos = next_tile->getCoordinate();

		if (current_tile == next_tile)
		{
			Log::error("Didn't find next tile %s", printPoint(pos));
			return;
		}

		addPath(next_tile);
		current_tile = next_tile;

		SDL_Rect hitbox = current_tile->getHitbox();
		renderQueue->addItem((new RenderItem())->setRectangle(hitbox, {255, 0, 0, 32}));
		path_length++;

		if (++i > max_i)
			return;
	}

	Log::info("%s to %s in %d tiles", printPoint(src), printPoint(dst), path_length);

	for (int i = 0; i < MAX_PATH_LENGTH; i++)
	{
		if (itinerary[i] == NULL)
			continue;

		itinerary[i]->next = itinerary[i+1];
	}

	// finished

	itinerary_done = true;
	current_path = -1;
}

void PathFinder::print_path(void)
{
	SDL_Rect hitbox;

	for (int i = 0; i < MAX_PATH_LENGTH; i++)
	{
		if (itinerary[i] != NULL)
		{
			hitbox = itinerary[i]->tile->getHitbox();
			renderQueue->addItem((new RenderItem())->setRectangle(hitbox, {255, 0, 0, 32}));
		}
	}

}


Path* PathFinder::getFirst(void)
{
	if (!itinerary_done)
		return (NULL);

	current_path = 0;

	return (itinerary[current_path]);
}


Path* PathFinder::getNext(SDL_Point coordinate)
{
	Path* path = getPath(coordinate);
	
	if (path == NULL)
		return (NULL);

	return (path->next);
}


Path* PathFinder::getPrevious(SDL_Point coordinate)
{
	Path* path = getPath(coordinate);
	
	if (path == NULL)
		return (NULL);

	return (path->previous);
}
