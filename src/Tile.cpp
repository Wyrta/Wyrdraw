#include "Tile.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include "WD_Function.hpp"
#include "Parameters.hpp"

extern Parameters param;

int Tile::size = 64;

SDL_Texture *texture[TileType::LAST_TTYPE] = {NULL};

Tile::Tile(const char* name, TileType type, SDL_Point coo) : Sprite(name)
{
	map_coordinate = coo;

	setFrame(0, texture[type]);

	setHitbox({0, 0, Tile::size, Tile::size});
}


Tile::~Tile()
{

}


SDL_Point Tile::getMapCoordinate(void)
{
	return (map_coordinate);
}

void Tile::setMapCoordinate(SDL_Point new_coo)
{

}


Direction Tile::canWalk(void)
{
	return (walk_stat);
}

bool Tile::canWalk(Direction direction)
{
	if ((direction == walk_stat) || (walk_stat == Direction::ALL))
		return (true);
	else
		return (false);
}

void Tile::loadTexture(void)
{
	std::ifstream config("../assets/img/tiles.cnf");
	std::string line;
	int index;

	if (!config.is_open())
	{
		std::cout << "Failed to open tile config file" << std::endl;
	}

	TileType tile_type;
	std::string file;

	std::cout << "Load tiles..." << std::endl;

	/* reset tile */
	for (int i = 0; i < TileType::LAST_TTYPE; i++)
		texture[i] = NULL;


	while (getline(config, line) )
	{
		if (line.c_str()[0] == '#')
			continue;

		tile_type = TileType::LAST_TTYPE;
		file = "";

		index = line.find(";");
		if (index == (int)std::string::npos)
			continue;

		std::string str_tileType = line.substr(0, index);

		tile_type = getTiletype(str_tileType.c_str());

		file = line.substr(index+1, line.length());

		file.insert(0, "../assets/img/");

		texture[tile_type] = createTexture(param.getRenderer(), NULL, file.c_str());
	}

	std::cout << "Tiles loaded" << std::endl;


	config.close();
}

TileType Tile::getTiletype(const char* str)
{
	std::string tile_str = str;

	TileType type = TileType::EMPTY;

	if (tile_str == "DIRT")
		type = TileType::DIRT;
	else if (tile_str == "DIRT_PATH_1")
		type = TileType::DIRT_PATH_1;
	else if (tile_str == "DIRT_PATH_2")
		type = TileType::DIRT_PATH_2;
	else if (tile_str == "DIRT_PATH_3")
		type = TileType::DIRT_PATH_3;
	else if (tile_str == "DIRT_PATH_4")
		type = TileType::DIRT_PATH_4;
	else if (tile_str == "DIRT_NE_GRASS")
		type = TileType::DIRT_NE_GRASS;
	else if (tile_str == "DIRT_NW_GRASS")
		type = TileType::DIRT_NW_GRASS;
	else if (tile_str == "DIRT_SE_GRASS")
		type = TileType::DIRT_SE_GRASS;
	else if (tile_str == "DIRT_SW_GRASS")
		type = TileType::DIRT_SW_GRASS;
	else if (tile_str == "GRASS_E_W_DIRT")
		type = TileType::GRASS_E_W_DIRT;
	else if (tile_str == "GRASS_N_S_DIRT")
		type = TileType::GRASS_N_S_DIRT;
	else if (tile_str == "GRASS_NE_DIRT")
		type = TileType::GRASS_NE_DIRT;
	else if (tile_str == "GRASS_NW_DIRT")
		type = TileType::GRASS_NW_DIRT;
	else if (tile_str == "GRASS_S_N_DIRT")
		type = TileType::GRASS_S_N_DIRT;
	else if (tile_str == "GRASS_SE_DIRT")
		type = TileType::GRASS_SE_DIRT;
	else if (tile_str == "GRASS_SW_DIRT")
		type = TileType::GRASS_SW_DIRT;
	else if (tile_str == "GRASS_W_E_DIRT")
		type = TileType::GRASS_W_E_DIRT;
	else if (tile_str == "GRASS_1")
		type = TileType::GRASS_1;
	else if (tile_str == "GRASS_2")
		type = TileType::GRASS_2;
	else if (tile_str == "GRASS_3")
		type = TileType::GRASS_3;
	else if (tile_str == "TINYBUSH_1")
		type = TileType::TINYBUSH_1;
	else if (tile_str == "TINYBUSH_2")
		type = TileType::TINYBUSH_2;
	else if (tile_str == "TINYBUSH_3")
		type = TileType::TINYBUSH_3;
	else if (tile_str == "TINYBUSH_4")
		type = TileType::TINYBUSH_4;

	return (type);
}