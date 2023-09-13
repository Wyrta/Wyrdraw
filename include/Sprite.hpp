#ifndef _sprite_hpp_
#define _sprite_hpp_

#include <SDL2/SDL.h>

#define MAX_ANIMATION_FRAME	8

class Sprite
{
	private:
		SDL_Texture* frame[MAX_ANIMATION_FRAME];
		bool do_destroy_texture = true;

		SDL_Rect hitbox;
		SDL_Point coordinate = {0, 0};

		int number_of_frame = 0;
		int current_frame = 0;
		int frame_duration = 1;
		int last_frame = 0;
		char name[32];

	public:
		Sprite(const char* sprite_name);
		Sprite(const char* sprite_name, SDL_Texture* texture, bool can_destroy_texture = true);
		Sprite(const char* sprite_name, const char* path);
		~Sprite();

		void render(void);

		bool setFrame(int frame_ID, SDL_Texture* frame_texture);
		bool setFrame(int frame_ID, const char* path);

		void setCoordinate(SDL_Point new_coo);
		SDL_Point getCoordinate(void);

		void setHitbox(SDL_Rect new_hitbox);
		SDL_Rect getHitbox(void);

};
#endif // _sprite_hpp_
