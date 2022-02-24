#pragma once
#include <unordered_map>

using namespace std;

enum class SPRITE_NAME {
	NONE = -1,
	PLAYER_IDLE = 0,
	PLAYER_RUN,
	PLAYER_SHOOT,
	N_SPRITES
};

class BITMAP_MANAGER {

private:
	static BITMAP_MANAGER* instance;
	unordered_map<SPRITE_NAME, ALLEGRO_BITMAP*> bitmaps;
	vector<string> sprite_paths;
private:
	BITMAP_MANAGER() {
		init();
	}
	void init() {
		sprite_paths.resize((int)SPRITE_NAME::N_SPRITES);
		sprite_paths[(int)SPRITE_NAME::PLAYER_IDLE] = "assets/spritesheets/ranged_bot/run.png";
		sprite_paths[(int)SPRITE_NAME::PLAYER_RUN] = "assets/spritesheets/ranged_bot/run.png";
		sprite_paths[(int)SPRITE_NAME::PLAYER_SHOOT] = "assets/spritesheets/ranged_bot/shoot.png";
	}
public:
	static BITMAP_MANAGER* get_instance() {
		if (instance == nullptr)
			instance = new BITMAP_MANAGER();
		return instance;
	}
	static void delete_instance() {
		delete instance;
		instance = nullptr;
	}

	void clear() {
		for (auto& per : bitmaps) {
			if (per.second == nullptr)
				continue;
			al_destroy_bitmap(per.second);
		}
	}

	ALLEGRO_BITMAP* get_bitmap(SPRITE_NAME _name) {
		if (bitmaps.find(_name) != bitmaps.end()) {
			return bitmaps[_name];
		}
		else {
			const char* path = sprite_paths[(int)_name].c_str();
			ALLEGRO_BITMAP* new_bitmap = al_load_bitmap(path);
			must_init(new_bitmap, "loading bitmap from bitmap manager");
			bitmaps[_name] = new_bitmap;
			return new_bitmap;
		}
	}
};

BITMAP_MANAGER* BITMAP_MANAGER::instance = nullptr;

#define bitmap_manager BITMAP_MANAGER::get_instance()