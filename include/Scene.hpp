#ifndef _scene_hpp_
#define _scene_hpp_

#include "GuiItem.hpp"
#include "InputManager.hpp"

#define MAX_ITEM	64

class Scene
{
	private: 
		GuiItem* item[MAX_ITEM];
		bool enable = false;

		int level = 0;	// highter value mean more on top 

	public: 
		Scene();
		~Scene();

		void proc(InputManager* input_manager);

		bool isEnable(void);
		void setEnable(bool state);
		int getLevel(void);


		int addItem(GuiItem* new_item);
		void removeItem(int id);
		void removeItem(GuiItem* item_to_remove);
		GuiItem* getItem(int id);

};
#endif // _scene_hpp_
