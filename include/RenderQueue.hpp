#ifndef _renderqueue_hpp_
#define _renderqueue_hpp_

#include "SDL2/SDL.h"

#include "WD_Type.hpp"

typedef enum 
{
	RECTANGLE,
	TEXTURE
} RenderItemType;

class RenderItem
{
	private:
		int time_to_live = 1;

		RenderItemType type;
		
		// If type = RECTANGLE

		SDL_Color color;
		SDL_Rect rectangle;

		// If type = TEXTURE

		SDL_Texture* texture;
		SDL_Rect src, dst;


	public: 
		RenderItem(int time = 1);
		~RenderItem();

		RenderItem* setTexture(SDL_Texture* t, SDL_Rect s, SDL_Rect d);
		RenderItem* setRectangle(SDL_Rect r, SDL_Color c);

		void render(SDL_Renderer* render_target);	// true > destroy
		bool doKill(void);
};

class RenderQueue
{
	private: 
		SDL_Renderer* render_target;
		RenderItem** queue;
		int queue_size;
		int queue_count;
	
	public: 
		RenderQueue(SDL_Renderer* renderer, int base_queue_size = 1024);
		~RenderQueue();

		void addItem(RenderItem* item);

		void render(void);

};
#endif // _renderqueue_hpp_