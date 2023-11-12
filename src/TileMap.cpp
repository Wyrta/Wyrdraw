#include "TileMap.hpp"
#include "Log.hpp"
#include "Parameters.hpp"
#include "RenderQueue.hpp"

#include <fstream>
#include <string>

extern RenderQueue* renderQueue;
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

	for (int i = 0; i < MAX_ENTITY; i++)
	{
		entity[i] = NULL;
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

	for (int i = 0; i < MAX_ENTITY; i++)
	{
		if (entity[i] == NULL)
			continue;

		delete (entity[i]);
		entity[i] = NULL;
	}
}


Tile* TileMap::addTile(const char* tile_name, TileType tile_type, SDL_Point tile_coo, WD_Direction tile_dir)
{
	Tile* new_tile = NULL;

	new_tile = new Tile(tile_name, tile_type, tile_coo, tile_dir);

	if (new_tile != NULL)
	{
		addTile(new_tile);
	}
	
	return (new_tile);
}


bool TileMap::addTile(Tile *tile_to_add)
{
	if (tile_to_add == NULL)
		return (false);

	for (int i = 0; i < MAX_TILE; i++)
	{
		if (tile[i] != NULL)
			continue;

		tile[i] = tile_to_add;

		SDL_Point t_coo = tile[i]->getCoordinate();
		
		tile[i]->set(NORTH, getTile({t_coo.x,t_coo.y-1}) );
		if (tile[i]->get(NORTH) != NULL)
			tile[i]->get(NORTH)->set(SOUTH, tile[i]);

		tile[i]->set(SOUTH, getTile({t_coo.x,t_coo.y+1}) );
		if (tile[i]->get(SOUTH) != NULL)
			tile[i]->get(SOUTH)->set(NORTH, tile[i]);

		tile[i]->set(WEST, getTile({t_coo.x-1,t_coo.y}) );
		if (tile[i]->get(WEST) != NULL)
			tile[i]->get(WEST)->set(EAST, tile[i]);

		tile[i]->set(EAST, getTile({t_coo.x+1,t_coo.y}) );
		if (tile[i]->get(EAST) != NULL)
			tile[i]->get(EAST)->set(WEST, tile[i]);

		tile[i]->followMap(&public_coordinate);
		return (true);
	}
	
	return (false);
}

Tile* TileMap::getTile(SDL_Point tile_coordinate)
{
	for (int i = 0; i < MAX_TILE; i++)
	{
		if (tile[i] == NULL)
			continue;

		if (tile[i]->getCoordinate() == tile_coordinate)
			return (tile[i]);
	}

	return (NULL);
}



Entity* TileMap::addEntity(const char* entity_name, SDL_Point entity_coo)
{
	Entity* entity_to_add = NULL;

	entity_to_add = new Entity(entity_name);
	entity_to_add->setCoordinate(entity_coo);
	
	if (entity_to_add != NULL)
	{
		addEntity(entity_to_add);
	}
	
	return (entity_to_add);
}


bool TileMap::addEntity(Entity *entity_to_add)
{
	if (entity_to_add == NULL)
		return (false);
		
	for (int i = 0; i < MAX_ENTITY; i++)
	{
		if (entity[i] != NULL)
			continue;

		entity[i] = entity_to_add;
		entity[i]->followMap(&public_coordinate);
		return (true);
	}
	
	return (false);
}

Entity* TileMap::getEntity(SDL_Point entity_coordinate)
{
	for (int i = 0; i < MAX_ENTITY; i++)
	{
		if (entity[i] == NULL)
			continue;

		if (entity[i]->getCoordinate() == entity_coordinate)
			return (entity[i]);
	}

	return (NULL);
}

void TileMap::setCoordinate(SDL_Point new_coordinate)
{
	SDL_Point old_coordinate = coordinate;
	public_coordinate = coordinate = new_coordinate;

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


void TileMap::setFollowEntity(int entity_id)
{
	if (entity_id < 0 && entity_id >= MAX_ENTITY)
	{
		entity_to_follow = -1;
		return;
	}

	if (entity[entity_id] == NULL)
	{
		entity_to_follow = -1;
		return;
	}

	entity_to_follow = entity_id;
}


void TileMap::followEntity(void)
{
	if (entity_to_follow == -1)
		return;

	Entity* followed = entity[entity_to_follow];

	if (followed == NULL)
		return;

	
	SDL_Point entity_coordinate = followed->getCoordinate();
	SDL_Rect entity_size = followed->getHitbox();
	entity_coordinate.x *= MapItem::tile_size.w;
	entity_coordinate.y *= MapItem::tile_size.h;

	SDL_Rect screen = param.getScreen();

	SDL_Point map_coordinate = coordinate;

	map_coordinate.x = (-entity_coordinate.x - entity_size.w/2) + (screen.w/2);
	map_coordinate.y = (-entity_coordinate.y - entity_size.h/2) + (screen.h/2);

	map_coordinate = map_coordinate - coordinate;

	static WD_Size speed = {10,10};
	bool proc_speed = false;

	if (map_coordinate.x > speed.w)
	{
		map_coordinate.x = speed.w;
		proc_speed = true;
	}	

	if (map_coordinate.y > speed.h)
	{
		map_coordinate.y = speed.h;
		proc_speed = true;
	}
	
	if (map_coordinate.x < -speed.w)
	{
		map_coordinate.x = -speed.w;
		proc_speed = true;
	}

	if (map_coordinate.y < -speed.h)
	{
		map_coordinate.y = -speed.h;
		proc_speed = true;
	}

	if (proc_speed)
	{
		WD_Size entity_speed;
		entity_speed.w = followed->getSpeed() * Tile::tile_size.w;
		entity_speed.h = followed->getSpeed() * Tile::tile_size.h;

		speed.w = (speed.w <= entity_speed.w) ? speed.w+1 : entity_speed.w;
		speed.h = (speed.h <= entity_speed.h) ? speed.h+1 : entity_speed.h;
	}
	else
	{
		speed.w = speed.w/2;
		speed.h = speed.h/2;
	}

	map_coordinate = map_coordinate + coordinate;

	setCoordinate(map_coordinate);
}


void TileMap::proc(InputManager* input_manager)
{
	if (!isEnable())
		return;

	int number_tile_printed = 0;
	
	bool proc_wheel = false;

	Tile* tile_hovered = NULL;

	if (input_manager->getWheel(WHEEL_UP))
	{
		Tile::tile_size.w += 2;
		Tile::tile_size.h += 2;
		proc_wheel = true;
	}
	else if (input_manager->getWheel(WHEEL_DOWN))
	{
		Tile::tile_size.w -= 2;
		Tile::tile_size.h -= 2;
		proc_wheel = true;
	}

	followEntity();

	for (int i = 0; i < MAX_TILE; i++)
	{
		if (tile[i] == NULL)
			continue;

		SDL_Rect tile_hitbox = tile[i]->getHitbox();

		if (proc_wheel)
		{
			tile_hitbox.w = MapItem::tile_size.w;
			tile_hitbox.h = MapItem::tile_size.h;
			tile[i]->setHitbox(tile_hitbox);
		
			tile_hitbox = tile[i]->getHitbox();
		}

		tile[i]->proc();

		SDL_Point mouse = input_manager->mouseCoordinate();

		if (SDL_PointInRect(&mouse, &tile_hitbox))
		{
			tile_hovered = tile[i];
			
			SDL_Color color;
			if (input_manager->mouseClicked(BUTTON_LEFT))
				color = {128, 64, 64, 128};
			else if (input_manager->mouseMaintained(BUTTON_LEFT))
				color = {255, 0, 0, 64};
			else
				color = {255, 255, 255, 64};

			renderQueue->addItem((new RenderItem())->setRectangle(tile_hitbox, color));
			input_manager->mouseSetTile(BUTTON_LEFT, tile_hovered);
		}

		number_tile_printed++;
	}

	if (input_manager->mouseMaintained(BUTTON_RIGHT))
		input_manager->mouseSetTile(BUTTON_RIGHT, tile_hovered);
		
	if (input_manager->mouseGetTile(BUTTON_RIGHT) != NULL)
		renderQueue->addItem((new RenderItem())->setRectangle(input_manager->mouseGetTile(BUTTON_RIGHT)->getHitbox(), {0,0,0,32}));


	for (int i = 0; i < MAX_ENTITY; i++)
	{
		if (entity[i] == NULL)
			continue;

		SDL_Rect entity_hitbox = entity[i]->getHitbox();

		if (proc_wheel)
		{
			entity_hitbox.w = MapItem::tile_size.w;
			entity_hitbox.h = MapItem::tile_size.h;
			entity[i]->setHitbox(entity_hitbox);
		
			entity_hitbox = entity[i]->getHitbox();
		}

		entity[i]->proc();
	}

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

	Log::info("Loading map ... \"%s\"", file_path);

	Uint32 time = SDL_GetTicks();

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
			WD_Direction tile_walkable;
			SDL_Point tileCoo;
			int comma_idx[3];
//			int same_pos_tile = 0;

			if (l_idx > r_idx)
			{
				Log::error("Invalid index l_idx > r_idx (%d>%d)", l_idx, r_idx);
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
			tile_walkable	= Tile::getTileDirection(strTile_walkable.c_str());

//			printf("> %d,%d,%d,%d\r\n", tileCoo.x, tileCoo.y, tile_type, tile_walkable);

//			for (unsigned int i = 0; i < MAX_TILE; i++)
//			{
//				if ((tile[i]->get().x == params.x) && (tilemap[i]->getPosition().y == params.y))
//					same_pos_tile++;
//			}

//			if (same_pos_tile > 0)
//				console->log(log_t::WARNING, "Already have %d tile%s on this position (x:%d y:%d)", same_pos_tile, (same_pos_tile == 1) ? "" : "s", params.x, params.y);

			addTile("Tile", tile_type, tileCoo, tile_walkable);

			nb_tiles++;

			l_idx = r_idx +1;
			r_idx = line.find(";", l_idx);
		}
	}

	time = SDL_GetTicks() - time;

	Log::info("Successfully load map %s (%d tiles) in %dms", file_name, nb_tiles, time);

	config.close();
}