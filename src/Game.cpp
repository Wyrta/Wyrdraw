#include "Game.hpp"
#include <iostream>

#include "Parameters.hpp"
#include "InputManager.hpp"
#include "Text.hpp"
#include "Button.hpp"

#include "WD_Type.hpp"

extern Parameters param;
Entity* player,* player2,* player3;

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

	player = new Entity("Player1");
	player->setTile(map->getTile({0,0}));
	player->setTexture(createTexture(param.getRenderer(), NULL, "../assets/img/npcTest.png"));
	map->addEntity(player);


	player2 = new Entity("Player2");
	player2->setTile(map->getTile({1,1}));
	player2->setTexture(createTexture(param.getRenderer(), NULL, "../assets/img/mobTest.png"));
	map->addEntity(player2);

	player3 = new Entity("Player3");
	player3->setTile(map->getTile({2,2}));
	player3->setTexture(createTexture(param.getRenderer(), NULL, "../assets/img/mobTest.png"));
	map->addEntity(player3);

	map->setFollowEntity(0);
	map->setEnable(true);

	return (0);
}


int Game::proc(InputManager* input_manager)
{	
	++tick_number;

	player->updateOrder(input_manager);
	// player2->updateOrder(input_manager);

	map->proc(input_manager);

	return (0);
}


bool Game::run()
{
	return (running);
}
