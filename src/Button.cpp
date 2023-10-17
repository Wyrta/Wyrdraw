#include "Button.hpp"

#include "WD_Type.hpp"
#include "Parameters.hpp"
#include "RenderQueue.hpp"

extern Parameters param;
extern RenderQueue* renderQueue;

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

	SDL_Color color = normal;;
	if (click || maintain)
		color = on_click; 
	else if (hover)
		color = on_hover;

	color.a = normal.a;
	SDL_Rect hitbox = getHitbox();
	renderQueue->addItem((new RenderItem())->setRectangle(hitbox, color));

	text.proc(click, hover, maintain);
}