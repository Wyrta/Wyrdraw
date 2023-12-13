#include <GraphicItem.hpp>
#include "Log.hpp"

#include "RenderQueue.hpp"
#include "WD_Type.hpp"
#include "WD_Function.hpp"
#include "RenderQueue.hpp"

extern RenderQueue* renderQueue;

GraphicItem::GraphicItem()
{
	hitbox = EMPTY_RECT;
	mask = EMPTY_RECT;
	const_texture = false;
	texture = NULL;

	highlighted = false;
	highlight_color = {255,255,255,64};
}


GraphicItem::~GraphicItem()
{
	if (const_texture && texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void GraphicItem::proc(void)
{
	SDL_Rect src = {0,0,0,0}, dst;

	dst = hitbox;

	if (!isRectEmpty(mask))
	{
		src = mask;
	}

	renderQueue->addItem((new RenderItem(blur))->setTexture(texture, src, dst));

	if (highlighted)
		renderQueue->addItem((new RenderItem(blur))->setRectangle(hitbox, highlight_color));

	highlighted = false;
}


void GraphicItem::highlight(void)
{
	highlighted = true;
}

SDL_Rect GraphicItem::getHitbox(void)
{
	return (hitbox);
}


void GraphicItem::move(SDL_Point diff)
{
	hitbox.x = hitbox.x + diff.x;
	hitbox.y = hitbox.y + diff.y;
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
	if (new_texture == NULL) 
		return;
	
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
