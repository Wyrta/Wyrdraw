#include "Game.hpp"
#include <iostream>

#include "Parameters.hpp"
#include "InputManager.hpp"
#include "Text.hpp"
#include "Button.hpp"

#include "WD_Type.hpp"

extern Parameters param;

int Game::init(SDL_Rect* screen)
{
	WD_Size size1, size2;

	size1 = size2 = {0,0};
	
	return (0);
}


int Game::ready(void)
{
	std::cout << "Game launched !" << std::endl;

	map = new TileMap("test");

	int item0 = map->addItem(new Text("Text", WD_SIZE_FIT_CONTENT, {255, 255, 255, SDL_ALPHA_OPAQUE}, {128, 128, 128, SDL_ALPHA_OPAQUE}, {10,10}));
	int item1 = map->addItem(new Button("Button", {128,32}));
	
	map->getItem(item0)->setCoordinate({50,50});
	map->attachItemToMap(item0);

	map->getItem(item1)->setCoordinate({100,100});

	Button* button = (Button* )map->getItem(item1);
	button->normal = (SDL_Color){64, 64, 64, SDL_ALPHA_OPAQUE};
	button->on_click = (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE};
	button->on_hover = (SDL_Color){128, 128, 128, SDL_ALPHA_OPAQUE};

	map->setEnable(true);

	return (0);
}


int Game::proc(InputManager* input_manager)
{	
	std::cout << "Tick number: " << ++tick_number << std::endl;

	if (input_manager->keyMaintained(SDLK_d))
	{
		map->move({-5, 0});
	}
	if (input_manager->keyMaintained(SDLK_q))
	{
		map->move({5, 0});
	}
	if (input_manager->keyMaintained(SDLK_z))
	{
		map->move({0, 5});
	}
	if (input_manager->keyMaintained(SDLK_s))
	{
		map->move({0, -5});
	}
	if (input_manager->keyPressed(SDLK_SPACE))
	{
		Text* item = (Text* )(map->getItem(0));
		item->setBackground(!item->hasBackground());
	}

	map->proc(input_manager);

	return (0);
}


bool Game::run()
{
	return (running);
}
