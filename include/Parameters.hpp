#ifndef _parameters_hpp_
#define _parameters_hpp_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "WD_Function.hpp"


class Parameters
{
    private:
		int tick = 33;	// ~30FPS
		int current_tick = 0;
		SDL_Rect screen;
		SDL_Renderer* render = NULL;
		SDL_Window* window = NULL;

		TTF_Font *avara = NULL;
		
		// ...
    public:
		SDL_Renderer* getRenderer(void);
		bool setRenderer(SDL_Renderer* new_renderer);

		SDL_Window* getWindow(void);
		bool setWindow(SDL_Window* new_window);

		bool setTicksDuration(int tick_duration);
		int getTicksDuration(void);
		
		bool setTick(int tick_number);
		int getTick(void);
		
		bool setSreen(SDL_Rect rect_sreen);
		void setSreenDim(int w, int h);
		SDL_Rect getScreen(void);

		TTF_Font* getFont(int size = 16);
		bool loadFont(int size = 16);
};
#endif // _parameters_hpp_
