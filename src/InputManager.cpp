#include "InputManager.hpp"
#include "Parameters.hpp"

#include <iostream>

extern Parameters param;

void InputManager::proc(void)
{
	pollEvent();
}


SDL_Event* InputManager::getEvent(void)
{
	return (NULL);
}


bool InputManager::mouseClicked(int button)
{
	if (button == SDL_BUTTON_LEFT)
		return (mouse.click_left);
	else if (button == SDL_BUTTON_RIGHT)
		return (mouse.click_right);
	else
		return (false);
} 


bool InputManager::mouseMaintained(int button)
{
	if (button == SDL_BUTTON_LEFT)
		return (mouse.left);
	else if (button == SDL_BUTTON_RIGHT)
		return (mouse.right);
	else
		return (false);
} 


SDL_Point InputManager::mouseCoordinate(void)
{
	SDL_Point coordinate;
	coordinate.x = mouse.x;
	coordinate.y = mouse.y;

	return (coordinate);
}


void InputManager::pollEvent(void)
{
	int event_polling = 0;
	int has_event	 = 0;
	
	mouse.wheel = 0;

	/* store last value of the keyboard */
	for (int i = 0; i < SDL_Scancode::SDL_NUM_SCANCODES; i++)
	{
		this->last_keyboard_state[i] = this->keyboard_state[i];
	}

	for (int i = 0; i < number_event; i++)
	{
		/* code */
	}
		
	/* event proc */
	do
	{
		has_event = SDL_PollEvent(&event);
		
		/* reset click value */
		mouse.click_left = false;
		mouse.click_right = false; 
		
		if (!has_event)
			continue;

		event_queue[event_polling] = event;
		event_polling++;

		switch (event.type)
		{
			case SDL_QUIT: quit = true; break;
			case SDL_WINDOWEVENT: {
				if (this->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					int width, height;
					SDL_GetRendererOutputSize(param.getRenderer(), &width, &height);
					param.setSreenDim(width, height);
					std::cout << "Window size changed " << width << " x " <<  height << std::endl;
				}
				
			} break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			{
				Uint32 mask = SDL_GetMouseState(&mouse.x, &mouse.y);
				mouse.left  = (mask & SDL_BUTTON_LMASK);
				mouse.right = (mask & SDL_BUTTON_RMASK);
			} break;
			case SDL_MOUSEWHEEL:
			{
				if(event.wheel.y > 0) // scroll up
				{
					// console->log("Wheel UP");	// Put code for handling "scroll up" here!
					mouse.wheel++;
					std::cout << "Wheel UP" << mouse.wheel << std::endl;
				}
				else if(event.wheel.y < 0) // scroll down
				{
					// console->log("Wheel DOWN");	// Put code for handling "scroll down" here!
					mouse.wheel--;
					std::cout << "Wheel DOWN" << mouse.wheel << std::endl;
				}

				if(event.wheel.x > 0) // scroll right
				{
					//console->log("Wheel RIGHT");	// ...
				}
				else if(event.wheel.x < 0) // scroll left
				{
					//console->log("Wheel LEFT");	// ...
				}

			} break;
			case SDL_KEYDOWN: {
				if (keyPressed(SDL_SCANCODE_ESCAPE))	/* ESCAPE */
					quit = true;

				// std::cout << "Key pressed: " << event.key.keysym.scancode << std::endl;

			} break;
			case SDL_KEYUP: {

			} break;

			default:  break;
		}
		
	} while ((has_event) && (event_polling < MAX_EVENT));

	number_event = event_polling;

	if (mouse.left)
	{
		if (mouse.left != mouse.last_left)
		{
			mouse.click_left = true;
		}
	}

	if (mouse.right)
	{
		if (mouse.right != mouse.last_right)
		{
			mouse.click_right = true;
		}
	}

	/* save current value */
	mouse.last_left  = mouse.left;
	mouse.last_right = mouse.right;

}


bool InputManager::keyPressed(SDL_Scancode key)
{
	bool retval;

	retval = (last_keyboard_state[key] == false) && (keyboard_state[key] == true);

	return (retval);
}


bool InputManager::keyMaintained(SDL_Scancode key)
{
	return (last_keyboard_state[key]);
}

bool InputManager::keyPressed(SDL_Keycode key)
{
	return (keyPressed(SDL_GetScancodeFromKey(key)));	
}

bool InputManager::keyMaintained(SDL_Keycode key)
{
	return (keyMaintained(SDL_GetScancodeFromKey(key)));
}


bool InputManager::getWheel(int wheel)
{
	if (wheel == WHEEL_UP && mouse.wheel > 0)
		return (true);
	else if (wheel == WHEEL_DOWN && mouse.wheel < 0)
		return (true);
	else
		return (false);
}



bool InputManager::doQuit()
{
	return (quit);
}