#pragma once
#include "vector2.h"

class CAMERA;

enum class MOUSE_BUTTON {
	LEFT = 1 << 0,
	RIGHT = 1 << 1,
	MIDDLE = 1 << 2
};

class MOUSE {
private:
	static MOUSE* instance;
	MOUSE();
public:
	static MOUSE* get_instance();
	vector2<float> get_world_position(CAMERA*);
};

#define mouse MOUSE::get_instance()