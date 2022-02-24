#pragma once
#include "collidable.h"

enum class PROJECTILE_TYPE {
	LASER_RED,
	LASER_PURPLE,
	PROJECTILE_N
};

ALLEGRO_BITMAP* projectile_bitmaps[(int)PROJECTILE_TYPE::PROJECTILE_N];
float projectile_speed[(int)PROJECTILE_TYPE::PROJECTILE_N];
unsigned projectile_lifetime[(int)PROJECTILE_TYPE::PROJECTILE_N];
float projectile_scale[(int)PROJECTILE_TYPE::PROJECTILE_N];

class PROJECTILE: public COLL_RECT {
public:
	PROJECTILE_TYPE type;
	vector2<float> vec_pos;
	vector2<float> vec_vel;
	vector2<float> vec_dir;
	float speed;
	float angle;
	float cx, cy;
	unsigned lifetime;

	PROJECTILE(PROJECTILE_TYPE _type, const vector2<float>& _vec_dir, const vector2<float>& _vec_pos, COLL_LAYER _collision_layer, COLL_LAYER _collision_mask) :
		COLL_RECT(_vec_pos, { 20.f, 20.f }, (int)_collision_layer, (int)_collision_mask)
	{
		type = _type;
		speed = projectile_speed[(int)type];
		vec_pos = _vec_pos;
		vec_dir = _vec_dir;
		vec_vel = vec_dir * speed;
		angle = atan2(vec_vel.y, vec_vel.x);
		lifetime = projectile_lifetime[(int)type];
		cx = al_get_bitmap_width(projectile_bitmaps[(int)type]) / 2;
		cy = al_get_bitmap_height(projectile_bitmaps[(int)type]) / 2;
	}

	PROJECTILE(PROJECTILE_TYPE _type, const vector2<float>& _vec_dir, const vector2<float>& _vec_pos) :
		COLL_RECT(_vec_pos, { 20.f, 20.f }, (int)COLL_LAYER::PLAYER_BULLET, (int)COLL_LAYER::ENEMY)
	{
		type = _type;
		speed = projectile_speed[(int)type];
		vec_pos = _vec_pos;
		vec_dir = _vec_dir;
		vec_vel = vec_dir * speed;
		angle = atan2(vec_vel.y, vec_vel.x);
		lifetime = projectile_lifetime[(int)type];
		cx = al_get_bitmap_width(projectile_bitmaps[(int)type]) / 2;
		cy = al_get_bitmap_height(projectile_bitmaps[(int)type]) / 2;
	}
	~PROJECTILE() {
		// std:cout << "projectile destr\n";
	}

	void update() {
		vec_pos += vec_vel;
		lifetime--;
		if (lifetime == 0) {
			die();
		}

		COLL_RECT::update_center(vec_pos);
	}

	void draw() {
		float scale = projectile_scale[(int)type];
		al_draw_scaled_rotated_bitmap(projectile_bitmaps[(int)type], cx, cy, vec_pos.x, vec_pos.y, scale, scale, angle, 0);
		
		COLL_RECT::draw();
	}
};

void init_projectiles() {
	must_init(projectile_bitmaps[(int)PROJECTILE_TYPE::LASER_RED] = al_load_bitmap("assets/projectiles/laser_red.png"), "laser_red");
	projectile_speed[(int)PROJECTILE_TYPE::LASER_RED] = 1200.f / FRAMERATE;
	projectile_lifetime[(int)PROJECTILE_TYPE::LASER_RED] = 3 * FRAMERATE;
	projectile_scale[(int)PROJECTILE_TYPE::LASER_RED] = .25;

	must_init(projectile_bitmaps[(int)PROJECTILE_TYPE::LASER_PURPLE] = al_load_bitmap("assets/projectiles/laser_purple.png"), "laser_red");
	projectile_speed[(int)PROJECTILE_TYPE::LASER_PURPLE] = 600.f / FRAMERATE;
	projectile_lifetime[(int)PROJECTILE_TYPE::LASER_PURPLE] = 3 * FRAMERATE;
	projectile_scale[(int)PROJECTILE_TYPE::LASER_PURPLE] = .25;
}