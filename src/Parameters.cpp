#include "Parameters.hpp"


int Parameters::getTicksDuration(void)
{
	return (tick);
}


int Parameters::getTick(void)
{
	return (current_tick);
}


SDL_Rect Parameters::getScreen(void)
{
	return (screen);
}


bool Parameters::setTicksDuration(int tick_duration)
{
	if (tick_duration <= 0)
		return (false);
	
	tick = tick_duration;
	return (true);
}



bool Parameters::setTick(int tick_number)
{
	current_tick = tick_number;
	return (true);
}


bool Parameters::setSreen(SDL_Rect rect_screen)
{
	if (rect_screen.w <= 0 || rect_screen.h <= 0)
		return (false);

	screen = rect_screen;
	return (true);
}


SDL_Renderer* Parameters::getRenderer(void)
{
	return (render);
}

bool Parameters::setRenderer(SDL_Renderer* new_renderer)
{
	if (new_renderer == NULL)
		return (false);

	render = new_renderer;

	return (true);
}


void Parameters::setSreenDim(int w, int h)
{
	if (h > 0)
		screen.h = h;

	if (w > 0)
		screen.w = w;
}



SDL_Window* Parameters::getWindow(void)
{
	return (window);
}


bool Parameters::setWindow(SDL_Window* new_window)
{
	if (window == NULL)
		return (false);

	window = new_window;
	return (true);
}



TTF_Font* Parameters::getFont(int size)
{
	if (avara == NULL)
		loadFont(size);

	if (TTF_FontHeight(avara) != size)
	{
		TTF_CloseFont(avara);
		loadFont(size);
	}

	return (avara);
}

bool Parameters::loadFont(int size)
{
	avara = createFont("../assets/font/Avara.ttf", size);

	if (avara == NULL)
		return (false);
	else
		return (true);
}
