#include <GraphicItem.hpp>

#include <iostream>
#include <WD_Type.hpp>
#include <WD_Function.hpp>

GraphicItem::GraphicItem()
{
	hitbox = EMPTY_RECT;
	mask = EMPTY_RECT;
	const_texture = false;
	texture = NULL;
}


GraphicItem::~GraphicItem()
{
	if (const_texture && texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void GraphicItem::render(SDL_Renderer* render)
{
	int err = 0;

	SDL_Rect *src = NULL, dst;

	dst = hitbox;
	
	if (!isRectEmpty(mask))
	{
		src = (SDL_Rect *)malloc(sizeof(SDL_Rect));
		src->x = mask.x; 
		src->y = mask.y; 
		src->w = mask.w; 
		src->h = mask.h; 
	}

	err = SDL_RenderCopy(render, texture, src, &dst);

	free(src);

	if (err < 0)
	{
		std::cerr << "[GraphicItem] Error: render error \"" << SDL_GetError() << "\"" << std::endl;
	}
}


SDL_Rect GraphicItem::getHitbox(void)
{
	return (hitbox);
}


void GraphicItem::setHitbox(SDL_Rect new_hitbox)
{
	hitbox = new_hitbox;
}


SDL_Rect GraphicItem::getMask(void)
{
	return (mask);
}


void GraphicItem::setMask(SDL_Rect new_mask)
{
	mask = new_mask;
}


SDL_Texture* GraphicItem::getTexture(void)
{
	return (texture);
}


void GraphicItem::setTexture(SDL_Texture* new_texture)
{
	if (new_texture == NULL) return;
	
	texture = new_texture;
	SDL_QueryTexture(texture, NULL, NULL, &hitbox.w, &hitbox.h);
}


void GraphicItem::setConstTexture(bool isConst)
{
	const_texture = isConst;
}


GraphicItem* GraphicItem::newGraphicItem(const char* path, SDL_Rect hitbox, SDL_Rect mask)
{
	GraphicItem* graphicItem = NULL;
	SDL_Texture* texture = NULL;

	graphicItem = new GraphicItem();
	if (graphicItem == NULL) return (NULL);

	texture = createTexture(NULL, &hitbox, path);
	if (texture == NULL) return (NULL);

	graphicItem->setTexture(texture);
	graphicItem->setHitbox(hitbox);
	graphicItem->setMask(mask);

	return (graphicItem);
}
