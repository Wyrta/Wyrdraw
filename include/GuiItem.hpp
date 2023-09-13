#ifndef _guiitem_hpp_
#define _guiitem_hpp_

#include "SDL2/SDL.h"

#include "WD_Type.hpp"

class GuiItem
{
	private: 
		SDL_Point coordinate;
		WD_Size size;

	public: 
		GuiItem() {};
		virtual ~GuiItem() {};

		virtual void proc(bool clicked, bool hovered, bool maintain);

		SDL_Point getCoordinate(void);
		void setCoordinate(SDL_Point coo);

		WD_Size getSize(void);
		void setSize(WD_Size siz);
		void setSize(SDL_Rect rect);

		SDL_Rect getHitbox(void);
};
#endif // _guiitem_hpp_
