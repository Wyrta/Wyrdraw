#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Game.hpp"
#include "Parameters.hpp"
#include "InputManager.hpp"

#define APP_NAME	"Wyrdraw engine"


Parameters param;

SDL_Window* createWindow(SDL_Rect screen, const char* window_name);
SDL_Renderer* createRenderer(SDL_Window* window);
int openAudio(void);

int main(int argc, char **argv)
{
	std::cout << "Starting " << APP_NAME << std::endl;

	SDL_Rect screen;
	screen.x = 0;
	screen.y = 0;
	screen.h = 600;
	screen.w = 800;
	
	Game game;


	// SDL init
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
	srand(0);

	game.init(&screen);

	SDL_Window* window = createWindow(screen, APP_NAME);
	
	if (window == NULL)
	{
		std::cerr << "Fatal error: Cannot create window " << SDL_GetError() << std::endl;
		return (-1);
	}
	
	SDL_Renderer* render = createRenderer(window);

	if (render == NULL)
	{
		std::cerr << "Fatal error: Cannot create renderer " << SDL_GetError() << std::endl;
		return (-1);
	}

	int audio = openAudio();

	if (audio < 0)
	{
		std::cerr << "Fatal error: Cannot open audio " << SDL_GetError() << std::endl;
		return (-1);
	}

	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

	param.setSreen(screen);
	param.setWindow(window);
	param.setRenderer(render);

	InputManager input_manager;

	Tile::loadTexture();

	game.ready();

	Uint32 last_tick = SDL_GetTicks();

	while (game.run() && !input_manager.doQuit())
	{
		param.setTick(game.tick_number);

		input_manager.proc();
		
		game.proc(&input_manager);

		// proc all


		SDL_RenderPresent(param.getRenderer());
		
		Uint32 current_tick = SDL_GetTicks();
		Uint32 wait = param.getTicksDuration() - (current_tick - last_tick);
		if (wait > 0 && wait < 100)
			SDL_Delay(wait);

		// clean render area
		SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(param.getRenderer(), &screen);

		last_tick = SDL_GetTicks();
	}
	
	SDL_Quit();	
	return (0);
}


SDL_Window* createWindow(SDL_Rect screen, const char* window_name)
{
	SDL_Window* window = NULL;

	window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w, screen.h, SDL_WINDOW_RESIZABLE);

	return (window);
}


SDL_Renderer* createRenderer(SDL_Window* window)
{
	SDL_Renderer* render = NULL;
	render	= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	return (render);
}


int openAudio(void)
{
	int audio, mixer;

	audio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	if (audio < 0)
	{
		std::cout << "Error while init SDL audio\r\n";
		return (-1);
	}
	else
	{
		std::cout << "Init SDL audio\r\n";
	}

	mixer = Mix_Init(MIX_INIT_OGG);

	if (mixer == 0)
	{
		std::cout << "Error while init SDL_Mixer audio\r\n";
		return (-1);
	}
	else
	{
		std::cout << "Init SDL_Mixer audio\r\n";
	}

	return (0);
}

