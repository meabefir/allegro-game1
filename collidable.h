#pragma once
#include "alllegro.h"
#include "vector2.h"
#include "common.h"

enum class COLL_LAYER {
	PLAYER = 1,
	PLAYER_BULLET = 1 << 1,
	ENEMY = 1 << 2,
};

#define N_LAYERS 3

class COLLIDABLE {
public:
	bool dead = false;
	int collision_layer;
	int collision_mask;

	std::unordered_map<COLLIDABLE*, bool> collided_with;

public:
	COLLIDABLE();
	COLLIDABLE(int _collision_layer, int _collision_mask);
	virtual ~COLLIDABLE();
	void die() {
		dead = true;
	}

	bool can_collide_with(COLLIDABLE* _coll) {
		return (collided_with.find(_coll) == collided_with.end());
	}

	virtual void draw() = 0;
	virtual bool collides_with(COLLIDABLE*) = 0;
	virtual void collide_with(COLLIDABLE*) = 0;
};

class COLL_RECT: public COLLIDABLE {
private:
	vector2<float> vec_start;
	vector2<float> vec_end;
	vector2<float> vec_size;
	vector2<float> vec_size_half;
	vector2<float> vec_center;

public:
	COLL_RECT(const vector2<float>& _vec_center, const vector2<float>& _vec_size);
	COLL_RECT(const vector2<float>& _vec_center, const vector2<float>& _vec_size,
		int _collision_layer, int _collision_mask);
	~COLL_RECT() {
		// std::cout << " coll_rect destr\n";
	}
	void update_center(const vector2<float>& _vec_center);

	bool aabb(COLL_RECT* _coll_rect);

	bool collides_with(COLLIDABLE* _coll);

	void draw();
};