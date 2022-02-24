#include <iostream>
#include "enemy.h"
#include "bitmap_manager.h"
#include "debugger.h"

ENEMY::ENEMY(const vector2<float> _pos):
	COLL_RECT(_pos, {40, 40}, (int)COLL_LAYER::ENEMY, 0)
{
	vec_pos = _pos;

	bitmap = bitmap_manager->get_bitmap(SPRITE_NAME::ENEMY);
}

void ENEMY::update() {
	update_center(vec_pos);
}

void ENEMY::draw() {
	al_draw_scaled_rotated_bitmap(bitmap, 300, 300, vec_pos.x, vec_pos.y, .5, .5, 0, 0);

	COLL_RECT::draw();
}