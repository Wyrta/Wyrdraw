#include "Animation.hpp"
#include "WD_Function.hpp"

#include "Log.hpp"

Animation::Animation(int frame_alloc_size)
{
	if (frame_alloc_size > 0)
	{
		frames = (SDL_Texture**)SDL_malloc(max_frame * sizeof(SDL_Texture*));
		max_frame = frame_alloc_size;

		for (int i = 0; i < max_frame; i++)
			frames[i] = NULL;
	}

	frame_rate = 4;
	frame_time = (1000 / frame_rate);
}


Animation::~Animation()
{
	for (int i = 0; i < max_frame; i++)
	{
		SDL_DestroyTexture(frames[i]);
	}
	
	SDL_free(frames);
}


void Animation::setFrameRate(float new_frame_rate)
{
	frame_rate = new_frame_rate;
	frame_time = (1000 / frame_rate);
}


bool Animation::addFrame(SDL_Texture* texture)
{
	if (texture == NULL)
		return (false);

	if (last_frame_setup+1 == max_frame)
	{
		max_frame++;
		frames = (SDL_Texture**)SDL_realloc(frames, max_frame * sizeof(SDL_Texture*));
	}

	last_frame_setup++;

	frames[last_frame_setup] = texture;

	return (true);
}


bool Animation::addFrame(const char* texture_path, SDL_Renderer* render)
{
	SDL_Texture* texture = NULL;

	texture = createTexture(render, NULL, texture_path);

	if (texture == NULL)
		return (false);

	return (addFrame(texture));
}


SDL_Texture* Animation::getNextFrame(void)
{
	if (do_count)
	{
		Uint32 current_frame = SDL_GetTicks();

		if (current_frame - last_frame >= frame_time)
		{
			last_frame = current_frame;
			frame_id++;
		}

		if (frame_id > last_frame_setup)
			frame_id = 0;
	}

	return (frames[frame_id]);
}


SDL_Texture* Animation::getFrame(int id)
{
	if (id >= frame_id)
		id = frame_id;

	if (id < 0)
		id = 0;

	return (frames[id]);
}


void Animation::restart(void)
{
	frame_id = 0;
}


void Animation::stop(void)
{
	do_count = false;
}


void Animation::start(void)
{
	do_count = true;
}