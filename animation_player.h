#pragma once
#include "bitmap_manager.h"

using namespace std;

extern double delta_time;

typedef struct ANIMATION {
	SPRITE_NAME name;
	ALLEGRO_BITMAP* bitmap;
	int frame_count;
	int current_frame = 0;
	bool looping;
	bool finished;
	double total_duration;
	double frame_duration;
	double current_time = 0.0;

	ANIMATION(SPRITE_NAME _name, float _total_duration, bool _looping = true) {
		looping = _looping;
		name = _name;
		bitmap = bitmap_manager->get_bitmap(_name);
		frame_count = al_get_bitmap_width(bitmap) / al_get_bitmap_height(bitmap);
		total_duration = _total_duration;
		frame_duration = total_duration / frame_count;
		finished = false;
	}
	~ANIMATION() {
		// nope
		/*al_destroy_bitmap(bitmap);*/
	}

	void play() {
		current_time = 0.0;
		current_frame = 0;
		finished = false;
	}

	void update() {
		current_time += delta_time;
		if (current_time >= frame_duration) {
			current_time -= frame_duration;

			current_frame = (current_frame + 1) % frame_count;
			if (current_frame == 0)
				finished = true;
		}
	}

	void draw() {
		al_draw_bitmap_region(bitmap, current_frame * al_get_bitmap_height(bitmap), 0, al_get_bitmap_height(bitmap), al_get_bitmap_height(bitmap), 0, 0, 0);
	}

} ANIMATION;

typedef struct ANIMATION_PLAYER {

	unordered_map<SPRITE_NAME, ANIMATION*> animations;
	SPRITE_NAME current_animation = SPRITE_NAME::NONE;

	~ANIMATION_PLAYER() {
		for (auto& per : animations) {
			delete per.second;
			per.second = nullptr;
		}
	}

	void add_animation(SPRITE_NAME _name, double _total_duration, bool _looping = true) {
		animations[_name] = new ANIMATION(_name, _total_duration, _looping);
		if (animations.size() == 1)
			current_animation = _name;
	}

	void play_animation(SPRITE_NAME _name) {
		if (animations.find(_name) == animations.end())
			return;
		if (current_animation == _name)
			return;
		current_animation = _name;
		animations[_name]->play();
	}

	bool animation_finished() {
		if (current_animation == SPRITE_NAME::NONE)
			return false;
		return animations[current_animation]->finished;
	}

	void update() {
		if (current_animation == SPRITE_NAME::NONE)
			return;
		animations[current_animation]->update();
	}

	void draw() {
		if (current_animation == SPRITE_NAME::NONE)
			return;
		animations[current_animation]->draw();
	}

} ANIMATION_PLAYER;