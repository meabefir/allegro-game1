#include "camera.h"
#include "setup.h"

extern unsigned char key[ALLEGRO_KEY_MAX];

CAMERA::CAMERA(float _width, float _height) {
	vec_pos = { 0.f, 0.f };
	vec_scale = { 1.f, 1.f };

	vec_size = { _width, _height };
	vec_size_half = { _width / 2, _height / 2 };

	debugger->add_field("scale", FIELD_TYPE::FLOAT, &scale);
}

void CAMERA::set_pos(const vector2<float>& _vec) {
	vec_pos = _vec;

	const float d = .002f;
	if (key[ALLEGRO_KEY_Q]) {
		set_scale({ vec_scale.x + d, vec_scale.y + d });
	}
	else if (key[ALLEGRO_KEY_E]) {
		set_scale({ vec_scale.x - d, vec_scale.y - d });
	}

	update_transform();
}

void CAMERA::set_scale(const vector2<float>& _vec) {
	vec_scale = _vec;
	scale = vec_scale.x;

	update_transform();
}

void CAMERA::update_transform() {

	al_identity_transform(&transform);
	al_translate_transform(&transform, -vec_pos.x + vec_size_half.x / scale, -vec_pos.y + vec_size_half.y / scale);
	al_scale_transform(&transform, vec_scale.x, vec_scale.y);
	al_use_transform(&transform);
}

void CAMERA::draw() {
	al_draw_filled_circle(vec_pos.x, vec_pos.y, 10, al_map_rgb_f(0, 0, 1));
}