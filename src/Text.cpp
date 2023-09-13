#include "Text.hpp"
#include <cstring>
#include "Parameters.hpp"
#include "WD_Function.hpp"
#include <iostream>

extern Parameters param;

Text::Text(const char* content, WD_Size size, SDL_Color txt_color)
{
	strcpy(text, content);
	text_color = txt_color;
	setCoordinate({0,0});

	has_background = false;
	if (size != WD_SIZE_FIT_CONTENT)
	{
		const_size = true;
		setSize(size);
	}
	
	margin = {0,0};

	update();
}


Text::Text(const char* content, WD_Size size, SDL_Color txt_color, SDL_Color bg_color, SDL_Point hasMargin)
{
	strcpy(text, content);
	text_color = txt_color;
	setCoordinate({0,0});

	has_background = true;
	if (size != WD_SIZE_FIT_CONTENT)
	{
		const_size = true;
		setSize(size);
	}
	background_color = bg_color;
	margin = hasMargin;

	update();
}


Text::~Text()
{

}

void Text::update(void)
{
	SDL_Rect rect;

	SDL_DestroyTexture(texture);
	texture = write(param.getRenderer(), &rect, param.getFont(20), text, text_color);

	texture_hitbox = rect;
	
	if (has_background)
	{
		rect.w += margin.x*2;
		rect.h += margin.y*2;
	}
	
	if (!const_size)
		setSize(rect);

	if (background_area.x == -1 || background_area.y == -1)
		background_area = rect;

	need_to_update = false;

}


void Text::proc(bool clicked, bool hovered, bool maintained)
{
	if (need_to_update)
		update();
		
	SDL_Rect hitbox = getHitbox();

	texture_hitbox.x = hitbox.x + margin.x;
	texture_hitbox.y = hitbox.y + margin.y;

	if (has_background)
	{
		SDL_SetRenderDrawColor(param.getRenderer(), background_color.r, background_color.g, background_color.b, background_color.a);
		SDL_RenderFillRect(param.getRenderer(), &hitbox);
	}

	if (texture != NULL)
		SDL_RenderCopy(param.getRenderer(), texture, NULL, &texture_hitbox);
}


void Text::setText(const char* content)
{
	SDL_strlcpy(text, content, 128);

	need_to_update = true;
}

void Text::setBackgroundColor(SDL_Color color)
{
	background_color = color;
	has_background = true;
	need_to_update = true;
}

void Text::setBackground(bool state)
{
	has_background = state;
}

bool Text::hasBackground(void)
{
	return (has_background);
}


void Text::setTextColor(SDL_Color color)
{
	text_color = color;
	need_to_update = true;
}

void Text::align(Align align_to)
{
	switch (align_to)
	{
		case Align::CENTER:
			break;
		case Align::LEFT:
			break;
		case Align::RIGHT:
			break;

	default:
		break;
	}

	std::cout << "Text::align(Align ) -> not implemented" << std::endl;
}
