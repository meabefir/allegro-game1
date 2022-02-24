#include "debugger.h"

DEBUGGER* DEBUGGER::instance = nullptr;

DEBUGGER::DEBUGGER() {
	font = al_create_builtin_font();
	must_init(font, "creating debug font");

	line_height = al_get_font_line_height(font);
}

DEBUGGER* DEBUGGER::get_instance() {
	if (instance == nullptr)
		instance = new DEBUGGER();
	return instance;
}

void DEBUGGER::add_field(std::string _name, FIELD_TYPE _type, void* _add) {
	fields.push_back({ _name, {_type, _add} });
}

void DEBUGGER::update() {

}

void DEBUGGER::draw() {
	int current_y = 0;
	for (auto& field : fields) {
		std::string text = field.first;
		text += " ";
		FIELD_TYPE type = field.second.first;

		switch (type) {
		case FIELD_TYPE::INT:
			text += std::to_string((*(int*)(field.second.second)));
			break;
		case FIELD_TYPE::FLOAT:
			text += std::to_string((*(float*)(field.second.second)));
			break;
		case FIELD_TYPE::DOUBLE:
			text += std::to_string((*(double*)(field.second.second)));
			break;
		default:
			break;
		}

		al_draw_text(font, al_map_rgb(255, 255, 255), 0, current_y, 0, text.c_str());

		current_y += line_height * 1.5;
	}
}