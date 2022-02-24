#pragma once
#include <unordered_map>
#include "alllegro.h"

using namespace std;

enum class SPRITE_NAME {
	NONE = -1,
	PLAYER_IDLE = 0,
	PLAYER_RUN,
	PLAYER_SHOOT,
	ENEMY,
	N_SPRITES
};

class BITMAP_MANAGER {

private:
	static BITMAP_MANAGER* instance;
	unordered_map<SPRITE_NAME, ALLEGRO_BITMAP*> bitmaps;
	vector<string> sprite_paths;
private:
	BITMAP_MANAGER();
	void init();
public:
	static BITMAP_MANAGER* get_instance();
	static void delete_instance();

	void clear();

	ALLEGRO_BITMAP* get_bitmap(SPRITE_NAME _name);
};

#define bitmap_manager BITMAP_MANAGER::get_instance()