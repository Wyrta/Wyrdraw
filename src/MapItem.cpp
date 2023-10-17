#include <MapItem.hpp>
#include <WD_Function.hpp>


WD_Size MapItem::tile_size = (WD_Size){64,64};

MapItem::MapItem() : GraphicItem()
{
	map_coordinate = NULL;
	coordinate = EMPTY_POINT;
}


MapItem::~MapItem()
{

}

void MapItem::proc(SDL_Point offset)
{
	SDL_Rect new_hitbox = getHitbox();

	new_hitbox.x = (coordinate.x * MapItem::tile_size.w) + offset.x;
	new_hitbox.y = (coordinate.y * MapItem::tile_size.h) + offset.y;

	if (map_coordinate != NULL)
	{
		new_hitbox.x += map_coordinate->x;
		new_hitbox.y += map_coordinate->y;
	}

	setHitbox(new_hitbox);

	GraphicItem::proc();
}


SDL_Point MapItem::getCoordinate(void)
{
	return (coordinate);
}


void MapItem::setCoordinate(SDL_Point new_coordinate)
{
	coordinate = new_coordinate;

	SDL_Rect new_hitbox = getHitbox();

	new_hitbox.x = coordinate.x * MapItem::tile_size.w;
	new_hitbox.y = coordinate.y * MapItem::tile_size.h;

	if (map_coordinate != NULL)
	{
		new_hitbox.x += map_coordinate->x;
		new_hitbox.y += map_coordinate->y;
	}

	setHitbox(new_hitbox);
}

void MapItem::followMap(SDL_Point* new_map_coordinate)
{
	map_coordinate = new_map_coordinate;
}

void MapItem::move(SDL_Point diff)
{
	coordinate.x = coordinate.x + diff.x;
	coordinate.y = coordinate.y + diff.y;
}

MapItem* MapItem::newMapItem(const char* path, SDL_Point coordinate, SDL_Rect hitbox, SDL_Rect mask)
{
	MapItem* mapItem = NULL;
	SDL_Texture* texture = NULL;

	mapItem = new MapItem();
	if (mapItem == NULL) return (NULL);

	texture = createTexture(NULL, &hitbox, path);
	if (texture == NULL) return (NULL);

	mapItem->setTexture(texture);
	mapItem->setHitbox(hitbox);
	mapItem->setMask(mask);
	mapItem->setCoordinate(coordinate);

	return (mapItem);
}
