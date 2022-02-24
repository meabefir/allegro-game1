#include "mouse.h"
#include "alllegro.h"
#include "camera.h"

MOUSE* MOUSE::instance = nullptr;

MOUSE::MOUSE() {

}

MOUSE* MOUSE::get_instance() {
	if (instance == nullptr) {
		instance = new MOUSE();
	}
	return instance;
}

vector2<float> MOUSE::get_world_position(CAMERA* _camera) {
	ALLEGRO_MOUSE_STATE mouse_state;
	al_get_mouse_state(&mouse_state);

	return { _camera->vec_pos.x - _camera->vec_size_half.x / _camera->vec_scale.x + mouse_state.x / _camera->vec_scale.x,
			 _camera->vec_pos.y - _camera->vec_size_half.y / _camera->vec_scale.y + mouse_state.y / _camera->vec_scale.y };
}