#include "bitmap_manager.h"
#include "common.h"

BITMAP_MANAGER* BITMAP_MANAGER::instance = nullptr;

BITMAP_MANAGER::BITMAP_MANAGER() {
	init();
}

void BITMAP_MANAGER::init() {
	sprite_paths.resize((int)SPRITE_NAME::N_SPRITES);
	sprite_paths[(int)SPRITE_NAME::PLAYER_IDLE] = "assets/spritesheets/ranged_bot/run.png";
	sprite_paths[(int)SPRITE_NAME::PLAYER_RUN] = "assets/spritesheets/ranged_bot/run.png";
	sprite_paths[(int)SPRITE_NAME::PLAYER_SHOOT] = "assets/spritesheets/ranged_bot/shoot.png";
	sprite_paths[(int)SPRITE_NAME::ENEMY] = "assets/test.png";
}

BITMAP_MANAGER* BITMAP_MANAGER::get_instance() {
	if (instance == nullptr)
		instance = new BITMAP_MANAGER();
	return instance;
}

void BITMAP_MANAGER::delete_instance() {
	delete instance;
	instance = nullptr;
}

void BITMAP_MANAGER::clear() {
	for (auto& per : bitmaps) {
		if (per.second == nullptr)
			continue;
		al_destroy_bitmap(per.second);
	}
}

ALLEGRO_BITMAP* BITMAP_MANAGER::get_bitmap(SPRITE_NAME _name) {
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