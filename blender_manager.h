#pragma once

class BLENDER_MANAGER {
private:
	static BLENDER_MANAGER* instance;
	BLENDER_MANAGER() {
		prev_blend_mode.resize(3);
		al_get_blender(&prev_blend_mode[0], &prev_blend_mode[1], &prev_blend_mode[2]);

		blend_modes["tint"] = { ALLEGRO_ADD, ALLEGRO_CONST_COLOR, ALLEGRO_ONE };
	}
public:
	static BLENDER_MANAGER* get_instance() {
		if (instance == nullptr) {
			instance = new BLENDER_MANAGER();
		}
		return instance;
	}
	static void delete_instance() {
		delete instance;
		instance = nullptr;
	}
private:
	std::unordered_map<std::string, std::vector<int>> blend_modes;
	std::vector<int> prev_blend_mode;
public:
	void set_blend_mode(const std::string& _mode, ALLEGRO_COLOR _color = al_map_rgb(255, 255, 255)) {
		if (blend_modes.find(_mode) == blend_modes.end())
			return;
		// save prev blend mode
		al_get_blender(&prev_blend_mode[0], &prev_blend_mode[1], &prev_blend_mode[2]);
		const std::vector<int>& blend_vec = blend_modes[_mode];
		al_set_blender(blend_vec[0], blend_vec[1], blend_vec[2]);

		al_set_blend_color(_color);
	}

	void reset() {
		al_set_blender(prev_blend_mode[0], prev_blend_mode[1], prev_blend_mode[2]);
	}
};

BLENDER_MANAGER* BLENDER_MANAGER::instance = nullptr;

#define blender_manager BLENDER_MANAGER::get_instance()