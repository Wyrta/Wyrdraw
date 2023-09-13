#ifndef _wdtype_hpp_
#define _wdtype_hpp_

#define COLOR_BLACK		(SDL_Color){0,0,0,SDL_ALPHA_OPAQUE}
#define COLOR_WHITE		(SDL_Color){255,255,255,SDL_ALPHA_OPAQUE}
#define COLOR_GREY		(SDL_Color){128,128,128,SDL_ALPHA_OPAQUE}


typedef struct _WD_Size {
	int w;	// Width
	int h;	// Height
} WD_Size;

#define WD_SIZE_FIT_CONTENT	(WD_Size){-1,-1}

bool operator==(WD_Size size1, WD_Size size2);

bool operator!=(WD_Size size1, WD_Size size2);

#endif // _wdtype_hpp_
