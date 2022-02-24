#pragma once
#include "vector2.h"
#include "debugger.h"

class CAMERA {
public:
	vector2<float> vec_pos;
	vector2<float> vec_size;
	vector2<float> vec_size_half;
	vector2<float> vec_scale;
	float scale = 1.f;
	float rotation = 0;

	ALLEGRO_TRANSFORM transform;

	CAMERA(float _width, float _height);

	void set_pos(const vector2<float>& _vec);

	void set_scale(const vector2<float>& _vec);

	void update_transform();

	void draw();
};