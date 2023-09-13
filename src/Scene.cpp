#include "Scene.hpp"

#include <iostream>
#include "WD_Function.hpp"

Scene::Scene()
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		item[i] = NULL;
	}
}

Scene::~Scene()
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		removeItem(i);
	}
}

void Scene::proc(InputManager* input_manager)
{
//	std::cout << "Scene::proc" << std::endl;

	if (!enable)
		return;

	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (item[i] == NULL)
			continue;

		bool clicked = false;
		bool hovered = false;
		bool maintain = false;
		
		if (input_manager != NULL)
		{

			SDL_Point mouse = input_manager->mouseCoordinate();
			SDL_Rect hitbox = item[i]->getHitbox();

			if (SDL_PointInRect(&mouse, &hitbox) )
			{
				hovered = true;

				if (input_manager->mouseClicked(BUTTON_LEFT))
					clicked = true;

				if (input_manager->mouseMaintained(BUTTON_LEFT))
					maintain = true;

				std::cout << printPoint(mouse) << printRect(hitbox) << std::endl;
			}
		}

		item[i]->proc(clicked, hovered, maintain);
	}
	
}


bool Scene::isEnable(void)
{
	return (enable);
}


void Scene::setEnable(bool state)
{
	enable = state;
}


int Scene::getLevel(void)
{
	return (level);
}


int Scene::addItem(GuiItem* new_item)
{
	if (new_item == NULL)
		return (-1);

	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (item[i] != NULL)
			continue;

		item[i] = new_item;

		return (i);
	}

	return (-1);
}


void Scene::removeItem(int id)
{
	if (id < 0 || id >= MAX_ITEM)
		return;

	if (item[id] == NULL)
		return;

	delete (item[id]);
	item[id] = NULL;

	return;
}


void Scene::removeItem(GuiItem* item_to_remove)
{
	if (item_to_remove == NULL)
		return;

	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (item_to_remove != item[i])
			continue;

		removeItem(i);

		return;
	}
	
}

GuiItem* Scene::getItem(int id)
{
	if (id < 0 || id >= MAX_ITEM)
		return (NULL);

	return (item[id]);
}
