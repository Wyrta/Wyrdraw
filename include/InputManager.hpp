#ifndef _inputmanager_hpp_
#define _inputmanager_hpp_

#include "SDL2/SDL.h"
#include "Tile.hpp"

#define MAX_EVENT		16
#define BUTTON_LEFT		SDL_BUTTON_LEFT
#define BUTTON_RIGHT	SDL_BUTTON_RIGHT

#define WHEEL_UP		1
#define WHEEL_DOWN		0

typedef struct Mouse_s
{
	int x, y;

	bool left, right;

	bool click_left, click_right;

	bool last_left, last_right;	/* dont use */

	Tile* current_tile;
	Tile* waypoint_tile;

/* > 0 UP 
< 0 DOWN */
	int wheel;	
} Mouse_t;


class InputManager
{
    private:
		SDL_Event event;
		SDL_Event event_queue[MAX_EVENT];
		int number_event = 0;
		
		bool quit = false;
		Mouse_t mouse;

	    const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
        Uint8 last_keyboard_state[SDL_Scancode::SDL_NUM_SCANCODES];

		void pollEvent(void);

    public:
		InputManager();
		~InputManager();

		void proc(void);
		SDL_Event* getEvent(void);

		bool mouseClicked(int button); 
		bool mouseMaintained(int button); 
		SDL_Point mouseCoordinate(void);
		void mouseSetTile(int button, Tile* tile);
		Tile* mouseGetTile(int button);

		bool getWheel(int wheel);

		bool keyPressed(SDL_Scancode key); 
		bool keyMaintained(SDL_Scancode key); 
		bool keyPressed(SDL_Keycode key); 
		bool keyMaintained(SDL_Keycode key); 

		bool doQuit();

};
#endif // _inputmanager_hpp_