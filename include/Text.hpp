#ifndef _text_hpp_
#define _text_hpp_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "GuiItem.hpp"

typedef enum {
	CENTER,
	LEFT,
	RIGHT,
	NONE
} Align;

class Text : public GuiItem
{
	private: 
		char text[128];
		SDL_Color text_color;
		
		bool has_background;
		SDL_Point margin;
		SDL_Rect background_area;
		SDL_Color background_color;
		bool const_size = false;

		SDL_Texture* texture = NULL;
		SDL_Rect texture_hitbox;

		bool need_to_update = true;
		void update(void);

	public: 
		Text(const char* content, WD_Size size, SDL_Color txt_color);
		Text(const char* content, WD_Size size, SDL_Color txt_color, SDL_Color bg_color, SDL_Point hasMargin = {0,0});
		~Text();

		void proc(bool clicked, bool hovered, bool maintained);

		void setText(const char* content);
		void setTextColor(SDL_Color color);
		void align(Align align_to);

		void setBackground(bool state);
		void setBackgroundColor(SDL_Color color);	// this function enable background
		bool hasBackground(void);
};
#endif // _text_hpp_
