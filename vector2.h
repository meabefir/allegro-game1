#pragma once
#include "common.h"

template <typename T>
class vector2 {
public:
	T x;
	T y;

public:
	vector2(): x(), y() {
	}
	vector2(T _x, T _y): x(_x), y(_y) {
	}
	vector2(const vector2& other) {
		x = other.x;
		y = other.y;
	}

	vector2& operator= (const vector2& other) {
		if (&other != this) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	void set(T _x, T _y) {
		x = _x;
		y = _y;
	}

	void reset() {
		x = 0;
		y = 0;
	}

	void normalize() {
		if (x == 0 && y == 0)
			return;
		float len = sqrt(x * x + y * y);
		if (x != 0) x /= len;
		if (y != 0) y /= len;
	}

	float get_length() {
		return sqrt(x * x + y * y);
	}

	float get_length_squared() {
		return x * x + y * y;
	}

	template <class U>
	vector2<T> operator+ (const vector2<U>& other) const {
		vector2<T> ret(x + other.x, y + other.y);
		return ret;
	}

	template <class U>
	vector2<T>& operator+= (const vector2<U>& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	template <class U>
	vector2<T> operator- (const vector2<U>& other) const {
		vector2<T> ret(x - other.x, y - other.y);
		return ret;
	}

	template <class U>
	vector2<T>& operator-= (const vector2<U>& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template <class U>
	vector2<T> operator* (U scalar) const {
		vector2<T> ret(x * scalar, y * scalar);
		return ret;
	}

	template <class U>
	vector2<T>& operator*= (U scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	template <class U>
	vector2<T> operator+ (U scalar) const {
		vector2<T> ret(x + scalar, y + scalar);
		return ret;
	}

	template <class U>
	vector2<T>& operator+= (U scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}

	template <class U>
	bool operator== (const vector2<U>& other) {
		return (x == other.x && y == other.y);
	}

	/*template <class U>
	friend ostream& operator << (ostream& os, const vector2<U>& v) {
		os << v.x << ' ' << v.y << '\n';
		return os;
	}*/

	vector2<T> rotate_degrees(float _degrees) {
		float _rad = deg_to_rad(_degrees);

		vector2<T> ret;
		ret.x = cos(_rad) * x - sin(_rad) * y;
		ret.y = sin(_rad) * x + cos(_rad) * y;
		return ret;
	}

	vector2<T> rotate(float _rad) {
		vector2<T> ret;
		ret.x = cos(_rad) * x - sin(_rad) * y;
		ret.y = sin(_rad) * x + cos(_rad) * y;
		return ret;
	}

	static float deg_to_rad(float _deg) {
		return _deg * _pi_180;
	}

	static float rad_to_deg(float _rad) {
		return _rad * _180_pi;
	}
};