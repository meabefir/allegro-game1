#pragma once
#include "camera.h"
#include "animation_player.h"
#include "helper.h"
#include "mouse.h"
#include "projectile_manager.h"
#include "collision_manager.h"

extern unsigned char key[ALLEGRO_KEY_MAX];

enum class PLAYER_STATE {
	IDLE,
	RUNNING,
	SHOOTING
};

class PLAYER: public COLL_RECT {
public:
	CAMERA* camera;
	ANIMATION_PLAYER animation_player;
	PLAYER_STATE player_state;
	
	vector2<float> vec_pos;
	vector2<float> vec_input;
	float move_speed = 160 / FRAMERATE;
	vector2<float> gun_offset_default{ 0, 60 };
	vector2<float> vec_gun_tip;
	float rotation_degrees;
	float rotation;

	PLAYER(CAMERA* _camera):
	COLL_RECT({0,0}, {50, 50}, (int)COLL_LAYER::PLAYER, 0)
	{
		vec_pos.x = BUFFER_W / 2;
		vec_pos.y = BUFFER_H / 2;
		camera = _camera;

		set_player_state(PLAYER_STATE::IDLE);
		camera->set_pos(vec_pos);

		// adaug animatie in animation player
		animation_player.add_animation(SPRITE_NAME::PLAYER_IDLE, .5);
		animation_player.add_animation(SPRITE_NAME::PLAYER_RUN, .5);
		animation_player.add_animation(SPRITE_NAME::PLAYER_SHOOT, .013, false);

		// debug info
		debugger->add_field("player pos", FIELD_TYPE::VECTOR2, &vec_pos);
	}
	~PLAYER() {
		
	}

	void set_rotation(float _rads) {
		rotation = _rads;
		rotation_degrees = vector2<float>::rad_to_deg(_rads);
	}

	void set_rotation_degrees(float _deg) {
		rotation_degrees = _deg;
		rotation = vector2<float>::deg_to_rad(_deg);
	}

	void set_player_state(PLAYER_STATE state) {
		player_state = state;
		switch (player_state) {
		case PLAYER_STATE::IDLE:
			animation_player.play_animation(SPRITE_NAME::PLAYER_IDLE);
			break;
		case PLAYER_STATE::RUNNING:
			animation_player.play_animation(SPRITE_NAME::PLAYER_RUN);
			break;
		case PLAYER_STATE::SHOOTING:
			animation_player.play_animation(SPRITE_NAME::PLAYER_SHOOT);
			shoot();
			break;
		}
	}

	void shoot() {
		float spread = 2.5f;
		update_gun_tip_vec();

		vector2<float> vec_to_mouse = get_vec_to_mouse();
		if (vec_to_mouse == vector2<float>(0, 0)) {
			vec_to_mouse.x = 1;
		}

		projectile_manager->add_projectile(PROJECTILE_TYPE::LASER_RED, vec_to_mouse, vec_gun_tip);
		projectile_manager->add_projectile(PROJECTILE_TYPE::LASER_RED, vec_to_mouse.rotate_degrees(spread*2), vec_gun_tip);
		projectile_manager->add_projectile(PROJECTILE_TYPE::LASER_PURPLE, vec_to_mouse.rotate_degrees(spread), vec_gun_tip);
		projectile_manager->add_projectile(PROJECTILE_TYPE::LASER_PURPLE, vec_to_mouse.rotate_degrees(-spread), vec_gun_tip);
		projectile_manager->add_projectile(PROJECTILE_TYPE::LASER_RED, vec_to_mouse.rotate_degrees(-spread*2), vec_gun_tip);
	}

	void update_gun_tip_vec() {
		vector2<float> gun_offset = gun_offset_default.rotate_degrees(rotation_degrees);
		vec_gun_tip = { vec_pos.x + gun_offset.x, vec_pos.y + gun_offset.y };
	}

	void update() {
		camera->set_pos(vec_pos);
		
		ALLEGRO_MOUSE_STATE mouse_state;
		al_get_mouse_state(&mouse_state);

		// update animation player
		animation_player.update();

		set_rotation(get_angle_to_mouse());
		/// tmp
		update_gun_tip_vec();

		switch (player_state) {
		case PLAYER_STATE::IDLE:
			update_movement_input();
			move();

			if (vec_input.get_length_squared() != 0) {
				set_player_state(PLAYER_STATE::RUNNING);
			}
			if (mouse_state.buttons & (int)MOUSE_BUTTON::LEFT) {
				set_player_state(PLAYER_STATE::SHOOTING);
			}
			break;
		case PLAYER_STATE::RUNNING:
			update_movement_input();
			move();

			if (vec_input.get_length_squared() == 0) {
				set_player_state(PLAYER_STATE::IDLE);
			}
			if (mouse_state.buttons & (int)MOUSE_BUTTON::LEFT) {
				set_player_state(PLAYER_STATE::SHOOTING);
			}
			break;
		case PLAYER_STATE::SHOOTING:
			update_movement_input();
			move();

			if (animation_player.animation_finished()) {
				set_player_state(PLAYER_STATE::IDLE);
			}
			break;
		}

		// update collision
		update_center(vec_pos);
	}

	void update_movement_input() {
		vec_input.reset();
		if (key[ALLEGRO_KEY_A])
			vec_input.x -= 1;
		if (key[ALLEGRO_KEY_D])
			vec_input.x += 1;
		if (key[ALLEGRO_KEY_W])
			vec_input.y -= 1;
		if (key[ALLEGRO_KEY_S])
			vec_input.y += 1;
		vec_input.normalize();
	}

	void move() {
		vec_pos += vector2<float>(vec_input * move_speed);
	}

	float get_angle_to_mouse() {
		ALLEGRO_MOUSE_STATE mouse_state;
		al_get_mouse_state(&mouse_state);
		float mouse_world_x, mouse_world_y;
		mouse_world_x = mouse_state.x + camera->vec_pos.x - camera->vec_size_half.x;
		mouse_world_y = mouse_state.y + camera->vec_pos.y - camera->vec_size_half.y;
		return atan2(mouse_world_y - vec_pos.y, mouse_world_x - vec_pos.x) - pi / 2;
	}

	vector2<float> get_vec_to_mouse() {
		ALLEGRO_MOUSE_STATE mouse_state;
		al_get_mouse_state(&mouse_state);
		float mouse_world_x, mouse_world_y;
		mouse_world_x = mouse_state.x + camera->vec_pos.x - camera->vec_size_half.x;
		mouse_world_y = mouse_state.y + camera->vec_pos.y - camera->vec_size_half.y;
		vector2<float> ret(mouse_world_x - vec_pos.x, mouse_world_y - vec_pos.y);
		ret.normalize();
		return ret;
	}

	void draw() {
		// draw self

		// save the old bitmap
		ALLEGRO_BITMAP* old_bitmap = al_get_target_bitmap();
		ALLEGRO_BITMAP* tmp_bitmap = al_create_bitmap(300, 300);
		
		al_set_target_bitmap(tmp_bitmap);
		animation_player.draw();
		al_set_target_bitmap(old_bitmap);

		float cx = 150;
		float cy = 150;
		al_draw_scaled_rotated_bitmap(tmp_bitmap, cx, cy, vec_pos.x, vec_pos.y, .5, .5, rotation, 0);
		al_destroy_bitmap(tmp_bitmap);

		// temp debug
		al_draw_filled_circle(vec_pos.x, vec_pos.y, 5, al_map_rgb(255, 0, 0));
		vector2<float> mouse_pos = mouse->get_world_position(camera);
		al_draw_filled_circle(mouse_pos.x, mouse_pos.y, 5, al_map_rgb(0, 255, 0));

		al_draw_line(vec_pos.x, vec_pos.y, vec_gun_tip.x, vec_gun_tip.y, al_map_rgb(255, 0, 0), 3);

		// draw collision
		COLL_RECT::draw();
	}

	void collide_with(COLLIDABLE* _coll) {

	}
};