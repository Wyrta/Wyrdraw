#include "Sprite.hpp"
#include "Parameters.hpp"

#include <cstring>
#include <iostream>

#include "WD_Function.hpp"

extern Parameters param;


Sprite::Sprite(const char* sprite_name)
{
	strcpy(name, sprite_name);

	frame[0] = NULL;

	do_destroy_texture = false;
}

Sprite::Sprite(const char* sprite_name, SDL_Texture* texture, bool can_destroy_texture)
{
	strcpy(name, sprite_name);

	do_destroy_texture = can_destroy_texture;

	frame[0] = texture;
	number_of_frame = 1;

	SDL_QueryTexture(texture, NULL, NULL, &hitbox.w, &hitbox.h);
}


Sprite::Sprite(const char* sprite_name, const char* path)
{
	strcpy(name, sprite_name);

	std::cout << "create sprite: " << name << std::endl;

	do_destroy_texture = true;

	SDL_Rect rect;
	frame[0] = createTexture(param.getRenderer(), &rect, path);
	number_of_frame = 1;

	if (frame[0] == NULL)
		std::cerr << "frame[0] == NULL" << std::endl;

	hitbox = rect;
}


Sprite::~Sprite()
{
	if (do_destroy_texture)
	{
		for (int i = 0; i < number_of_frame;i++)
		{
			SDL_DestroyTexture(frame[i] );
		}
	}
}

void Sprite::render(void)
{
	SDL_Rect src, dst;

	src = {0, 0, hitbox.w, hitbox.h};
	dst = {coordinate.x, coordinate.y, hitbox.w, hitbox.h};

	if (number_of_frame > 0)
	{
		if (last_frame >= (param.getTick() + frame_duration ))
			current_frame++;

		if (current_frame >= number_of_frame)
			current_frame = 0;
	}

	if ((current_frame >= 0) && (current_frame < MAX_ANIMATION_FRAME) && (frame[current_frame] != NULL))
	{
		int render_ret_val = SDL_RenderCopy(param.getRenderer(), frame[current_frame], &src, &dst);
		if (render_ret_val < 0)
			std::cerr << "[Sprite] Error: render error in \"" << name << "\"" << std::endl;

	}
	else
	{
		std::cerr << "[Sprite] Error: texture empty in \"" << name << "\"" << std::endl;
	}
}


bool Sprite::setFrame(int frame_ID, SDL_Texture* frame_texture)
{
	if (frame[frame_ID] != NULL)
		return (false);
	
	if (frame_texture == NULL)
		return (false);

	if (frame_ID >= MAX_ANIMATION_FRAME)
		return (false);
	
	frame[frame_ID] = frame_texture;

	if (frame_ID >= number_of_frame)
		number_of_frame = frame_ID + 1;

	return (true);
}


bool Sprite::setFrame(int frame_ID, const char* path)
{
	SDL_Texture* frame_texture = NULL;

	std::cout << "[Sprite] TODO: setFrame(int, const char*)" << std::endl;

	return (setFrame(frame_ID, frame_texture) );
}


void Sprite::setCoordinate(SDL_Point new_coo)
{
	coordinate = new_coo;
}

SDL_Point Sprite::getCoordinate(void)
{
	return(coordinate);
}


void Sprite::setHitbox(SDL_Rect new_hitbox)
{
	hitbox.x = new_hitbox.x;
	hitbox.y = new_hitbox.y;
	hitbox.w = new_hitbox.w;
	hitbox.h = new_hitbox.h;
}

SDL_Rect Sprite::getHitbox(void)
{
	SDL_Rect zone;
	zone.x = coordinate.x;
	zone.y = coordinate.y;
	zone.w = hitbox.w;
	zone.h = hitbox.h;

	return (zone);
}
