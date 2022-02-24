#include "collidable.h"
#include "collision_manager.h"

COLLIDABLE::COLLIDABLE() {
	collision_layer = 0;
	collision_mask = 0;

	collision_manager->add_collidable(this);
}

COLLIDABLE::COLLIDABLE(int _collision_layer, int _collision_mask) {
	collision_layer = _collision_layer;
	collision_mask = _collision_mask;

	collision_manager->add_collidable(this);
}

COLLIDABLE::~COLLIDABLE() {
	// std::cout << "collidable destr\n";
}

void COLLIDABLE::collide_with(COLLIDABLE* _coll) {
	collided_with[_coll] = true;
}



///  COLL_RECT


COLL_RECT::COLL_RECT(const vector2<float>& _vec_center, const vector2<float>& _vec_size) {
	vec_center = _vec_center;
	vec_size = _vec_size;
	vec_size_half = vec_size * .5f;

	vec_start = vec_center - vec_size * .5f;
	vec_end = vec_start + vec_size;
}

COLL_RECT::COLL_RECT(const vector2<float>& _vec_center, const vector2<float>& _vec_size,
	int _collision_layer, int _collision_mask):
	COLLIDABLE(_collision_layer, _collision_mask)
{
	vec_center = _vec_center;
	vec_size = _vec_size;
	vec_size_half = vec_size * .5f;

	vec_start = vec_center - vec_size * .5f;
	vec_end = vec_start + vec_size;
}

void COLL_RECT::update_center(const vector2<float>& _vec_center) {
	vec_center = _vec_center;

	vec_start = vec_center - vec_size_half;
	vec_end = vec_start + vec_size;
}

bool COLL_RECT::aabb(COLL_RECT* _coll_rect) {
	bool no_overlap = vec_start.x > _coll_rect->vec_end.x ||
		_coll_rect->vec_start.x > vec_end.x ||
		vec_start.y > _coll_rect->vec_end.y ||
		_coll_rect->vec_start.y > vec_end.y;
	return !no_overlap;
}

bool COLL_RECT::collides_with(COLLIDABLE* _coll) {
	COLL_RECT* coll_rect;
	coll_rect = dynamic_cast<COLL_RECT*>(_coll);
	if (coll_rect != nullptr) {
		return aabb(coll_rect);
	}

	return false;
}

void COLL_RECT::draw() {
	al_draw_rectangle(vec_start.x, vec_start.y, vec_end.x, vec_end.y, al_map_rgb_f(0, 1, 0), 2);
}
