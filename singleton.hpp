#pragma once

class SINLGETON {
private:
	static SINLGETON* instance;
	SINLGETON() {

	}
public:
	static SINLGETON* get_instance() {
		if (instance == nullptr) {
			instance = new SINLGETON();
		}
		return instance;
	}
};

SINLGETON* SINLGETON::instance = nullptr;

#define singleton SINLGETON::get_instance()