#include "Button.hpp"

#include "WD_Type.hpp"
#include "Parameters.hpp"

extern Parameters param;

Button::Button(const char* content, WD_Size size) : text(content, size, COLOR_BLACK, COLOR_GREY)
{
	setSize(size);

	text.setBackground(false);
}


Button::~Button()
{

}


bool Button::isClicked(void)
{
	return (click);
}


bool Button::isHovered(void)
{
	return (hover);
}


bool Button::isMaintained(void)
{
	return (maintain);
}


void Button::proc(bool clicked, bool hovered, bool maintained)
{
	click = clicked;
	hover = hovered;
	maintain = maintained;

	if (maintain)
		activated_since_tick++;
	else 
		activated_since_tick = 0;

	text.setCoordinate(getCoordinate());


	if (click || maintain)
		SDL_SetRenderDrawColor(param.getRenderer(), on_click.r, on_click.g, on_click.b, normal.a);
	else if (hover)
		SDL_SetRenderDrawColor(param.getRenderer(), on_hover.r, on_hover.g, on_hover.b, normal.a);
	else
		SDL_SetRenderDrawColor(param.getRenderer(), normal.r, normal.g, normal.b, normal.a);

	SDL_Rect hitbox = getHitbox();
	SDL_RenderFillRect(param.getRenderer(), &hitbox);

	text.proc(click, hover, maintain);
}