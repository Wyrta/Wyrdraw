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

	Log::debug("test");
	int cpt = 0;
	Log::debug("%d", cpt++);

	Animation *animation;

	animation = new Animation(5);
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/01.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/02.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/03.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/04.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/05.png"));
	animation->setFrameRate(FRAMERATE);
	Log::debug("%d", cpt++);

	player->addAnimation(animation, AnimationType::WALK, WD_Direction::NORTH);
	Log::debug("%d", cpt++);

	animation = new Animation(5);
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/11.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/12.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/13.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/14.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/15.png"));
	animation->setFrameRate(FRAMERATE);
	Log::debug("%d", cpt++);

	player->addAnimation(animation, AnimationType::WALK, WD_Direction::WEST);
	Log::debug("%d", cpt++);

	animation = new Animation(5);
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/21.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/22.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/23.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/24.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/25.png"));
	animation->setFrameRate(FRAMERATE);
	Log::debug("%d", cpt++);

	player->addAnimation(animation, AnimationType::WALK, WD_Direction::SOUTH);
	Log::debug("%d", cpt++);

	animation = new Animation(5);
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/31.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/32.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/33.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/34.png"));
	animation->addFrame(createTexture(param.getRenderer(), NULL, "../assets/img/player_1/35.png"));
	animation->setFrameRate(FRAMERATE);
	Log::debug("%d", cpt++);

	player->addAnimation(animation, AnimationType::WALK, WD_Direction::EAST);
	Log::debug("%d", cpt++);

	map->addEntity(player);
	Log::debug("%d", cpt++);

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
