#ifndef _graphicitem_hpp_
#define _graphicitem_hpp_

#include "SDL2/SDL.h"
#include "WD_Type.hpp"

class GraphicItem
{
    private:
		SDL_Rect hitbox;
		SDL_Rect mask;

		SDL_Texture* texture = NULL;

		bool const_texture;

		int blur = 1;

    public:
		GraphicItem();
		~GraphicItem();

		void proc(void);

		SDL_Rect getHitbox(void);
		void setHitbox(SDL_Rect new_hitbox);
		void move(SDL_Point diff);

		SDL_Rect getMask(void);
		void setMask(SDL_Rect new_mask);

		SDL_Texture* getTexture(void);
		void setTexture(SDL_Texture* new_texture);
		void setConstTexture(bool isConst);

		void setBlur(int blr) {blur = blr;}

		static GraphicItem* newGraphicItem(const char* path, SDL_Rect hitbox = EMPTY_RECT, SDL_Rect mask = EMPTY_RECT);
};
#endif // _graphicitem_hpp_