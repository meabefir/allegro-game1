#include "collision_manager.h"
#include "collidable.h"

COLLISION_MANAGER* COLLISION_MANAGER::instance = nullptr;

COLLISION_MANAGER::COLLISION_MANAGER() {
	debugger->add_field("collidables", FIELD_TYPE::INT, &collidable_count);
}

COLLISION_MANAGER* COLLISION_MANAGER::get_instance() {
	if (instance == nullptr) {
		instance = new COLLISION_MANAGER();
	}
	return instance;
}

void COLLISION_MANAGER::add_collidable(COLLIDABLE* _collidable) {
	collidables.push_back(_collidable);
}

void COLLISION_MANAGER::update() {
	// remove dead ones
	collidables.erase(std::remove_if(collidables.begin(), collidables.end(), [](const COLLIDABLE* p) {return p->dead; }), collidables.end());
	collidable_count = collidables.size();
}

void COLLISION_MANAGER::fixed_update() {
	// check collisions
	for (auto coll : collidables) {
		for (auto coll_2 : collidables) {
			if (coll == coll_2)
				continue;
			if (coll->collides_with(coll_2)) {
				// std::cout << " collision between " << coll << " and " << coll_2 << '\n';
			}
		}
	}
}