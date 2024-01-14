#include "Game.hpp"
#include "Log.hpp"

#include "Parameters.hpp"
#include "InputManager.hpp"
#include "Text.hpp"
#include "Button.hpp"

#include "WD_Type.hpp"

#include "Animation.hpp"

extern Parameters param;
Entity* player,* player2,* player3;


#define FRAMERATE		4

int Game::init(SDL_Rect* screen)
{
	WD_Size size1, size2;

	size1 = size2 = {0,0};
	
	return (0);
}


int Game::ready(void)
{
	Log::info("Game launched !");

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
	Log::print_debug = true;

	Log::debug("Init animation");
	Animation *animation = NULL;

	Log::debug("Animation 1");
	animation = new Animation(5);
	animation->addFrame("../assets/img/player_1/01.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/02.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/03.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/04.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/05.png", param.getRenderer());
	animation->setFrameRate(FRAMERATE);
	player->addAnimation(animation, AnimationType::WALK, WD_Direction::NORTH);
	Log::debug("OK");

	Log::debug("Animation 2");
	animation = new Animation(5);
	animation->addFrame("../assets/img/player_1/11.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/12.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/13.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/14.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/15.png", param.getRenderer());
	animation->setFrameRate(FRAMERATE);
	player->addAnimation(animation, AnimationType::WALK, WD_Direction::WEST);
	Log::debug("OK");
	
	Log::debug("Animation 3");
	animation = new Animation(5);
	Log::debug(" - create obj: OK");

	animation->addFrame("../assets/img/player_1/21.png", param.getRenderer());
	Log::debug(" - addframe1: OK");
	SDL_Delay(100);
	animation->addFrame("../assets/img/player_1/22.png", param.getRenderer());
	Log::debug(" - addframe2: OK");
	SDL_Delay(100);
	animation->addFrame("../assets/img/player_1/23.png", param.getRenderer());
	Log::debug(" - addframe3: OK");
	SDL_Delay(100);
	animation->addFrame("../assets/img/player_1/24.png", param.getRenderer());
	Log::debug(" - addframe4: OK");
	SDL_Delay(100);
	animation->addFrame("../assets/img/player_1/25.png", param.getRenderer());
	Log::debug(" - addframe5: OK");
	SDL_Delay(100);
	animation->setFrameRate(FRAMERATE);
	Log::debug(" - set framerate: OK");
	player->addAnimation(animation, AnimationType::WALK, WD_Direction::SOUTH);
	Log::debug(" - add animation: OK");
	Log::debug("OK");
/*

	animation = new Animation(5);
	animation->addFrame("../assets/img/player_1/31.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/32.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/33.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/34.png", param.getRenderer());
	animation->addFrame("../assets/img/player_1/35.png", param.getRenderer());
	animation->setFrameRate(FRAMERATE);
	Log::debug("%d", cpt++);

	player->addAnimation(animation, AnimationType::WALK, WD_Direction::EAST);
	Log::debug("%d", cpt++);
*/
	Log::debug("Entity: 0x%x", player);
	map->addEntity(player);
	Log::debug("Entity loaded successfully");

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
