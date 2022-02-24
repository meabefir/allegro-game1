#pragma once
#include "projectile.h"
#include "blender_manager.h"
#include "debugger.h"
#include "vector2.h"
#include <algorithm>

class PROJECTILE_MANAGER {
private:
	static PROJECTILE_MANAGER* instance;
	PROJECTILE_MANAGER() {
		debugger->add_field("projectile count", FIELD_TYPE::INT, &projectile_count);
	}
public:
	static PROJECTILE_MANAGER* get_instance() {
		if (instance == nullptr) {
			instance = new PROJECTILE_MANAGER();
		}
		return instance;
	}
	static void delete_instance() {
		delete instance;
		instance = nullptr;
	}
private:
	std::vector<PROJECTILE*> projectiles;
	int projectile_count = 0;

public:
	void add_projectile(PROJECTILE_TYPE _type, const vector2<float>& _dir, const vector2<float>& _pos) {
		projectiles.push_back(new PROJECTILE(_type, _dir, _pos ));
	}
	void update() {
		for (auto projectile : projectiles) {
			projectile->update();
		}
	}
	void cleanup() {
		// stable_partition instead of remove_if because remove_if fucks it up and doesnt guarantee that the pointers we have to delete will be at the end of the vector
		// stable_partition partitions the vector so that the elements that meet the condition are put first
		auto it_begin = stable_partition(projectiles.begin(), projectiles.end(), [](const PROJECTILE* p) {return !p->dead; });
		for_each(it_begin, projectiles.end(), [](PROJECTILE* p) { delete p; });
		projectiles.erase(it_begin, projectiles.end());

		projectile_count = projectiles.size();
	}
	void draw() {
		blender_manager->set_blend_mode("tint", al_map_rgb(255, 222, 33));

		for (auto projectile : projectiles) {
			projectile->draw();
		}

		blender_manager->reset();
	}
};

PROJECTILE_MANAGER* PROJECTILE_MANAGER::instance = nullptr;

#define projectile_manager PROJECTILE_MANAGER::get_instance()