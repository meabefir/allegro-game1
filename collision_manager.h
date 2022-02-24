#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "debugger.h"

class COLLIDABLE;

class COLLISION_MANAGER {
private:
	static COLLISION_MANAGER* instance;
	COLLISION_MANAGER();
public:
	static COLLISION_MANAGER* get_instance();
private:
	std::vector<COLLIDABLE*> collidables;
	int collidable_count = 0;
public:
	void add_collidable(COLLIDABLE* _collidable);
	void update();
	void fixed_update();
};

#define collision_manager COLLISION_MANAGER::get_instance()