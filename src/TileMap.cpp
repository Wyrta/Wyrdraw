#include "TileMap.hpp"
#include <iostream>
#include "Parameters.hpp"

#include <fstream>
#include <string>

extern Parameters param;

TileMap::TileMap(const char* name)
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		tile[i] = NULL;
	}

	for (int i = 0; i < MAX_ITEM; i++)
	{
		on_map_item[i] = false;
	}

	load(name);

	move({0,0});	// refresh all tiles coordinates
}


TileMap::~TileMap()
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		if (tile[i] == NULL)
			continue;

		delete (tile[i]);
		tile[i] = NULL;
	}
}

Tile* TileMap::addTile(const char* tile_name, TileType tile_type, SDL_Point tile_coo)
{
	Tile* new_tile = NULL;

	new_tile = new Tile(tile_name, tile_type, tile_coo);

	if (new_tile != NULL)
	{
		addTile(new_tile);
	}
	
	return (new_tile);
}

bool TileMap::addTile(Tile *tile_to_add)
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		if (tile[i] != NULL)
			continue;

		tile[i] = tile_to_add;
		return (true);
	}
	
	return (false);
}

void TileMap::setCoordinate(SDL_Point new_coordinate)
{
	SDL_Point old_coordinate = coordinate;
	coordinate = new_coordinate;

	for (int i = 0; i < MAX_TILE; i++)
	{
		if (tile[i] == NULL)
			continue;

		SDL_Point tile_pos = tile[i]->getMapCoordinate();

		tile_pos.x = (tile_pos.x * Tile::size) + coordinate.x;
		tile_pos.y = (tile_pos.y * Tile::size) + coordinate.y;
		tile[i]->setCoordinate(tile_pos);
	}

	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (!on_map_item[i])
			continue;

		GuiItem* itm = getItem(i);

		if (itm == NULL)
			continue;

		SDL_Point item_pos = itm->getCoordinate();

		item_pos.x = item_pos.x - old_coordinate.x + coordinate.x;
		item_pos.y = item_pos.y - old_coordinate.y + coordinate.y;
		
		itm->setCoordinate(item_pos);
	}
}

void TileMap::move(SDL_Point diff)
{
	SDL_Point new_coordinate;
	new_coordinate.x = coordinate.x + diff.x;
	new_coordinate.y = coordinate.y + diff.y;

	setCoordinate(new_coordinate);
}


void TileMap::proc(InputManager* input_manager)
{
	if (!isEnable())
		return;
	
	int number_tile_printed = 0;

/*		
	bool proc_wheel = false;

	if (input_manager->getWheel(WHEEL_UP))
	{
		Tile::size += 2;
		proc_wheel = true;
	}
	else if (input_manager->getWheel(WHEEL_DOWN))
	{
		Tile::size -= 2;
		proc_wheel = true;
	}
*/
	for (int i = 0; i < MAX_TILE; i++)
	{
		if (tile[i] == NULL)
			continue;

		tile[i]->render();

		SDL_Rect tile_hitbox = tile[i]->getHitbox();

/*
		if (proc_wheel)
		{
			tile_hitbox.w = Tile::size;
			tile_hitbox.h = Tile::size;
			tile[i]->setHitbox(tile_hitbox);
		
			tile_hitbox = tile[i]->getHitbox();

			SDL_Point tile_pos = tile[i]->getMapCoordinate();

			tile_pos.x = (tile_pos.x * Tile::size) + coordinate.x;
			tile_pos.y = (tile_pos.y * Tile::size) + coordinate.y;
			tile[i]->setCoordinate(tile_pos);
		}
*/
		SDL_Point mouse = input_manager->mouseCoordinate();

		if (SDL_PointInRect(&mouse, &tile_hitbox))
		{
			if (input_manager->mouseClicked(BUTTON_LEFT))
				SDL_SetRenderDrawColor(param.getRenderer(), 128, 64, 64, 128);
			else if (input_manager->mouseMaintained(BUTTON_LEFT))
				SDL_SetRenderDrawColor(param.getRenderer(), 255, 0, 0, 64);
			else
				SDL_SetRenderDrawColor(param.getRenderer(), 255, 255, 255, 64);

			SDL_RenderFillRect(param.getRenderer(), &tile_hitbox);
		}



		number_tile_printed++;
	}

//	std::cout << "TileMap::proc" << std::endl;

	Scene::proc(input_manager);
}


void TileMap::attachItemToMap(int id)
{
	if (id < 0 || id >= MAX_ITEM)
		return;

	GuiItem* itm = getItem(id);

	if (itm == NULL)
		return;

	on_map_item[id] = true;
}


void TileMap::detachItemfromMap(int id)
{
	if (id < 0 || id > MAX_ITEM)
		return;

	on_map_item[id] = false;
}


void TileMap::load(const char *file_name)
{
	char file_path[256];
	sprintf(file_path, "../assets/map/%s.map", file_name);

	std::ifstream config(file_path);

	if (!config.is_open())
	{
		std::cerr << "Failed loading map " << file_path << " cant open file" << std::endl;
	}

	std::cout << "Loading map " << file_path << std::endl;


	int nb_tiles = 0;
	int nb_lines = 0;

	std::string line;
	int l_idx, r_idx;


	while (getline(config, line) )
	{
		l_idx = 0;
		r_idx = line.find(";");

		nb_lines++;

		while (r_idx != (int)std::string::npos)
		{
			std::string strTile, strTile_x, strTile_y, strTile_type, strTile_walkable;
			TileType tile_type;
			int tile_walkable;
			SDL_Point tileCoo;
			int comma_idx[3];
//			int same_pos_tile = 0;

			if (l_idx > r_idx)
			{
				std::cout << "Invalid index l_idx > r_idx (" << l_idx << " > " << r_idx << ")" << std::endl;
				return;
			}

			strTile				= line.substr(l_idx, r_idx - l_idx);

//			console->log("\"%s\"", strTile.c_str());

			comma_idx[0]		= strTile.find(',', 0);
			comma_idx[1]		= strTile.find(',', comma_idx[0]+1);
			comma_idx[2]		= strTile.find(',', comma_idx[1]+1);

			strTile_x 			= strTile.substr(0	           , comma_idx[0]);
			strTile_y 			= strTile.substr(comma_idx[0]+1, comma_idx[1] - comma_idx[0]-1);
			strTile_type		= strTile.substr(comma_idx[1]+1, comma_idx[2] - comma_idx[1]-1);
			strTile_walkable	= strTile.substr(comma_idx[2]+1, r_idx        - comma_idx[2]-1);

			tileCoo.x		= atoi(strTile_x.c_str());
			tileCoo.y		= atoi(strTile_y.c_str());
			tile_type		= Tile::getTiletype(strTile_type.c_str());
			tile_walkable	= 0;//Tile::getTileDir(strTile_walkable);

			printf("> %d,%d,%d,%d\r\n", tileCoo.x, tileCoo.y, tile_type, tile_walkable);

//			for (unsigned int i = 0; i < MAX_TILE; i++)
//			{
//				if ((tile[i]->get().x == params.x) && (tilemap[i]->getPosition().y == params.y))
//					same_pos_tile++;
//			}

//			if (same_pos_tile > 0)
//				console->log(log_t::WARNING, "Already have %d tile%s on this position (x:%d y:%d)", same_pos_tile, (same_pos_tile == 1) ? "" : "s", params.x, params.y);

			addTile("Tile", tile_type, tileCoo);

			nb_tiles++;

			l_idx = r_idx +1;
			r_idx = line.find(";", l_idx);
		}
	}

	std::cout << "Successfully load map " << file_name << " (" << nb_tiles << " Tiles in " << nb_lines << " Lines)" << std::endl;

	config.close();
}