#ifndef _button_hpp_
#define _button_hpp_

#include "SDL2/SDL.h"

#include "GuiItem.hpp"
#include "Text.hpp"
#include "WD_Type.hpp"

class Button : public GuiItem
{
	private: 
		bool click = false;
		bool hover = false;
		bool maintain = false;

		int activated_since_tick = 0;

		Text text;

	public: 
		Button(const char* text, WD_Size size);
		~Button();
		bool isClicked(void);
		bool isHovered(void);
		bool isMaintained(void);

		void proc(bool clicked, bool hovered, bool maintained);

		SDL_Color normal;
		SDL_Color on_hover;
		SDL_Color on_click;
};
#endif // _button_hpp_
