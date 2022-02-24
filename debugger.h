#pragma once
#include <string>
#include "alllegro.h"
#include "common.h"


enum class FIELD_TYPE {
	INT,
	FLOAT,
	DOUBLE,
	VECTOR2
};

class DEBUGGER {
private:
	static DEBUGGER* instance;
	DEBUGGER();
	~DEBUGGER() {
		al_destroy_font(font);
	}
public:
	static DEBUGGER* get_instance();
	static void delete_instance() {
		delete instance;
		instance = nullptr;
	}
private:
	ALLEGRO_FONT* font;
	std::vector<std::pair<std::string, std::pair<FIELD_TYPE, void*>>> fields;
	int line_height;
public:
	void add_field(std::string _name, FIELD_TYPE _type, void* _add);

	void update();

	void draw();
};

#define debugger DEBUGGER::get_instance()