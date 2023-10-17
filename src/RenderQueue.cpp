#include "RenderQueue.hpp"
#include <chrono>
#include <iostream>
#include "WD_Function.hpp"


RenderItem::RenderItem(int time)
{
	time_to_live = time;
}


RenderItem::~RenderItem()
{

}


RenderItem* RenderItem::setRectangle(SDL_Rect r, SDL_Color c)
{
	type = RenderItemType::RECTANGLE;
	rectangle = r; 
	color = c;

	return (this);
}


RenderItem* RenderItem::setTexture(SDL_Texture* t, SDL_Rect s, SDL_Rect d)
{
	type = RenderItemType::TEXTURE;
	texture = t; 
	src = s;
	dst = d;

	return (this);
}


void RenderItem::render(SDL_Renderer* render_target)
{
	SDL_Rect* ptr_str = NULL;
	SDL_Rect* ptr_dst = NULL;

	switch (type)
	{
		case RenderItemType::RECTANGLE:
			SDL_SetRenderDrawColor(render_target, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(render_target, &rectangle);

			break;
		case RenderItemType::TEXTURE:
			if (src != 0)
				ptr_str = &src;
			if (dst != 0)
				ptr_dst = &dst;

			SDL_RenderCopy(render_target, texture, ptr_str, ptr_dst);
			break;
		
		default:
			time_to_live = 0;
			break;
	}

	time_to_live--;
}


bool RenderItem::doKill(void)
{
	return (time_to_live == 0);
}



RenderQueue::RenderQueue(SDL_Renderer* renderer, int base_queue_size)
{
	render_target = renderer;
	queue_size = base_queue_size;
	queue_count = 0;

	queue = (RenderItem**)SDL_malloc(queue_size * sizeof(RenderItem*));

	for (int i = 0; i < queue_size; i++)
		queue[i] = NULL;
}


RenderQueue::~RenderQueue()
{
	for (int i = 0; i < queue_size; i++)
	{
		if (queue[i] != NULL)
			delete (queue[i]);
	}
	
	SDL_free(queue);
}


void RenderQueue::addItem(RenderItem* item)
{
	int i;
	for (i = 0; i < queue_size; i++)
	{
		if (queue[i] != NULL)
			continue;

		queue[i] = item;
		break;
	}

	if (i == queue_size)
		std::cout << "RenderQueue::queue to small: " << queue_size << std::endl;
}



void RenderQueue::render(void)
{
	int number_rendered = 0;

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < queue_size; i++)
	{
		if (queue[i] == NULL)
			continue;

		queue[i]->render(render_target);
		number_rendered++;

		if (queue[i]->doKill())
		{
			delete (queue[i]);
			queue[i] = NULL;
		}
	}

	SDL_RenderPresent(render_target);

	auto stop = std::chrono::high_resolution_clock::now();
	int duration = (std::chrono::duration_cast<std::chrono::microseconds>(stop - start)).count();

	// std::cout << "Rendered: " << number_rendered << "items int " << duration << "us" << std::endl;
}

