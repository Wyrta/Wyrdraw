#ifndef _game_hpp_
#define _game_hpp_

#include "SDL2/SDL.h"

#include "Scene.hpp"
#include "TileMap.hpp"

class Game
{
	private: 
		bool running = true;

	public: 
		int init(SDL_Rect* screen);
		int ready(void);
		int proc(InputManager* input_manager);
		
		bool run(void);

		
		int tick_number = 0;

		TileMap* map = NULL;

};
#endif // _game_hpp_
