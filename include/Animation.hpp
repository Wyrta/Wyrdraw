#ifndef _animation_hpp_
#define _animation_hpp_

#include "SDL2/SDL.h"

class Animation
{
    private:
		SDL_Texture** frames;
		int max_frame = 0;
		int last_frame_setup = -1;
		int frame_id;

		
		float frame_rate;
		int   frame_time;

		bool do_count = true;
		float last_frame = 0;

    public:
		Animation(int frame_alloc_size = 0);
		~Animation();

		void setFrameRate(float new_frame_rate);
		bool addFrame(SDL_Texture* texture);
		bool addFrame(const char* texture_path, SDL_Renderer* render);

		SDL_Texture* getNextFrame(void);
		SDL_Texture* getFrame(int id);

		void restart(void);
		void stop(void);
		void start(void);
};
#endif // _animation_hpp_