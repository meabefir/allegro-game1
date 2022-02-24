#pragma once
#include "alllegro.h"
#include "vector2.h"
#include "collidable.h"

class ENEMY: public COLL_RECT {
	ALLEGRO_BITMAP* bitmap;

	vector2<float> vec_pos;

public:
	ENEMY(const vector2<float> _pos);
	void update();
	void draw();
};