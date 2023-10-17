#include "PathFinder.hpp"
#include "WD_Function.hpp"

#include <iostream>

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

	tiles = NULL;
	tilemap_size = -1;

	current_path = -1;

	itinerary_done = false;

	src = EMPTY_POINT;
	dst = EMPTY_POINT;
}


PathFinder::~PathFinder()
{
	for (int i = 0; i < MAX_PATH_LENGTH; i++)
	{
		if (itinerary[i] != NULL)
		{
			SDL_free(itinerary[i]);
			itinerary[i] = NULL;
		}
	}

	tiles = NULL;
	tilemap_size = -1;
}


void PathFinder::addPath(SDL_Point coordinate)
{
	Path* path = NULL;

	if (current_path+1 >= MAX_PATH_LENGTH)
		return;

	if (itinerary[current_path+1] != NULL)
		return;
	
	current_path++;
//	std::cout << current_path << " addPath(" << printPoint(coordinate) << ")" << std::endl;

	itinerary[current_path] = (Path *)SDL_malloc(sizeof(Path));

	path = itinerary[current_path];

	path->id = current_path;
	path->coordinate = coordinate;
	path->tile = getTile(coordinate);

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
	for (int i = 0; i < tilemap_size; i++)
	{
		if (tiles[i] == NULL)
			continue;

		if (tiles[i]->getCoordinate() == tile_coordinate)
			return (tiles[i]);
	}

	return (NULL);
}


void PathFinder::setTilemap(Tile* tilemap[], int size)
{
	tiles = tilemap;
	tilemap_size = size;
}


void PathFinder::setSource(SDL_Point coordinate)
{
	src = coordinate;
}


void PathFinder::setDestination(SDL_Point coordinate)
{
	dst = coordinate;
}

WD_Direction getDirection(double angle)
{
	WD_Direction direction;

	if (angle > (-M_PI)/2 && angle < M_PI/8)
		direction = WD_Direction::WEST;

	if (angle >= M_PI/8 && angle <= (3*M_PI)/8)
		direction = WD_Direction::NORTH_WEST;	

	if (angle > (3*M_PI)/8 && angle < (5*M_PI)/8)
		direction = WD_Direction::NORTH;	

	if (angle >= (5*M_PI)/8 && angle <= (7*M_PI)/8)
		direction = WD_Direction::NORTH_EAST;	

	if (angle > (7*M_PI)/8 || angle < (-7*M_PI)/8)
		direction = WD_Direction::EAST;	

	if (angle >= (-7*M_PI)/8 && angle <= (-5*M_PI)/8)
		direction = WD_Direction::SOUTH_EAST;	

	if (angle > (-5*M_PI)/8 && angle < (-3*M_PI)/8)
		direction = WD_Direction::SOUTH;	

	if (angle >= (-3*M_PI)/8 && angle <= (-1*M_PI)/8)
		direction = WD_Direction::SOUTH_WEST;	

	return (direction);
}


Tile* PathFinder::findTile(WD_Direction direction, SDL_Point coo)
{
	Tile* north,*south,*west,*east;
	Tile* tile = NULL;

	north = findNorth(coo);
	south = findSouth(coo);
	west = findWest(coo);
	east = findEast(coo);

	switch (direction)
	{
	case WD_Direction::NORTH:
	case WD_Direction::NORTH_WEST:
		if (north != NULL)
			tile = north;
		else if (west != NULL)
			tile = west;
		else if (east != NULL)
			tile = east;
		else
			tile = south;
		break;
	case WD_Direction::SOUTH:
	case WD_Direction::SOUTH_WEST:
		if (south != NULL)
			tile = south;
		else if (west != NULL)
			tile = west;
		else if (east != NULL)
			tile = east;
		else
			tile = north;
		break;
	case WD_Direction::NORTH_EAST:
		if (north != NULL)
			tile = north;
		else if (east != NULL)
			tile = east;
		else if (west != NULL)
			tile = west;
		else
			tile = south;
		break;
	case WD_Direction::SOUTH_EAST:
		if (south != NULL)
			tile = south;
		else if (east != NULL)
			tile = east;
		else if (west != NULL)
			tile = west;
		else
			tile = north;
		break;
	case WD_Direction::WEST:
		if (west != NULL)
			tile = west;
		else if (south != NULL)
			tile = south;
		else if (north != NULL)
			tile = north;
		else
			tile = east;
		break;
	case WD_Direction::EAST:
		if (east != NULL)
			tile = east;
		else if (north != NULL)
			tile = north;
		else if (south != NULL)
			tile = south;
		else
			tile = west;
		break;
	case WD_Direction::ALL:
		if (north != NULL)
			tile = north;
		else if (west != NULL)
			tile = west;
		else if (east != NULL)
			tile = east;
		else
			tile = south;
		break;
	case WD_Direction::NONE:
	default:
		tile = NULL;
		break;
	}

	return (tile);
}



Tile* PathFinder::findNorth(SDL_Point coo)
{
	Tile* tile = getTile({coo.x,coo.y-1});
/*
	if (!tile->canWalk(WD_Direction::SOUTH))
		tile = NULL;
*/	
	return (tile);
}


Tile* PathFinder::findSouth(SDL_Point coo)
{
	Tile* tile = getTile({coo.x,coo.y+1});
/*
	if (!tile->canWalk(WD_Direction::NONE))
		tile = NULL;
*/	
	return (tile);
}


Tile* PathFinder::findWest(SDL_Point coo)
{
	Tile* tile = getTile({coo.x-1,coo.y});
/*
	if (!tile->canWalk(WD_Direction::EAST))
		tile = NULL;
	*/
	return (tile);
}


Tile* PathFinder::findEast(SDL_Point coo)
{
	Tile* tile = getTile({coo.x+1,coo.y});
/*
	if (!tile->canWalk(WD_Direction::WEST))
		tile = NULL;
	*/
	return (tile);
}



void PathFinder::find(void)
{
	if (src == dst)
		return;

	if (tiles == NULL || tilemap_size <= 0)
		return;

	// start

	SDL_Point pos = src;
	WD_Direction prefered_direction = WD_Direction::NONE;
	Tile* tmp_tile = NULL;
	double angle;
	int path_length = 0;

	addPath(src);

	do
	{
		angle = SDL_atan2(pos.y - dst.y, pos.x - dst.x);

		prefered_direction = getDirection(angle);

//		std::cout << "Pos: " << printPoint(pos) << "Angle: " << angle << " Direction: " << printDirection(prefered_direction) << std::endl;

		tmp_tile = findTile(prefered_direction, pos);

		if (tmp_tile == NULL)
		{
			std::cout << "[PathFinder] Error : no tile found in " << printPoint(pos) << std::endl;
			break;
		}

		pos = tmp_tile->getCoordinate();

		addPath(pos);
		path_length++;

		SDL_Rect hitbox = tmp_tile->getHitbox();
		renderQueue->addItem((new RenderItem())->setRectangle(hitbox, {255, 0, 0, 32}));

	} while (pos != dst);

	std::cout << "[PathFinder] : " << printPoint(src) << printPoint(dst) << "In " << path_length << " tiles" << std::endl;

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

void PathFinder::print_path(SDL_Renderer* render)
{
	SDL_Rect hitbox;

	for (int i = 0; i < MAX_PATH_LENGTH; i++)
	{
		if (itinerary[i] != NULL)
		{
//			std::cout << i << printRect(hitbox) << std::endl;
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
