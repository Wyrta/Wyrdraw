#ifndef _wdfunction_hpp_
#define _wdfunction_hpp_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include <WD_Type.hpp>
#include <string>

#define printRect(rect)		"["<<#rect<<"] : x"<<rect.x<<" y" <<rect.y<<" w"<<rect.w<<" h"<<rect.h<<" "
#define printPoint(point)	"["<<#point<<"] : x"<<point.x<<" y" <<point.y<<" "

bool RectCollide(SDL_Rect rect1, SDL_Rect rect2);


SDL_Texture *createTexture(SDL_Renderer* render, SDL_Rect* rectangle, const char* path);
TTF_Font *createFont(const char *path, int size);
SDL_Texture *write(SDL_Renderer* render, SDL_Rect *rect, TTF_Font *font, const char *text, SDL_Color color);

bool isRectEmpty(SDL_Rect rect);

std::string printDirection(WD_Direction dir);

bool operator==(WD_Size size1, WD_Size size2);
bool operator!=(WD_Size size1, WD_Size size2);
bool operator==(SDL_Point pos1, SDL_Point pos2);
bool operator!=(SDL_Point pos1, SDL_Point pos2);
SDL_Point operator-(SDL_Point pos1, SDL_Point pos2);
SDL_Point operator+(SDL_Point pos1, SDL_Point pos2);

#endif // _wdfunction_hpp_
