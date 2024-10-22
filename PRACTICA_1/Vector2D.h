#ifndef VECTOR2D_H_ 
#define VECTOR2D_H_ 

#include <iostream>
template <class T>
class Vector2D {

private:
	T x;
	T y;

public:
	Vector2D() : x(), y() {};

	Vector2D(T x, T y) : x(x), y(y) {};

	T getX() const {
		return x;
	};

	T getY() const {
		return y;
	};

	Vector2D operator+(const Vector2D& v) const {
		Vector2D r;
		r.x = this->x + v.x;
		r.y = this->y + v.y;
		return r;
	};

	Vector2D operator-(const Vector2D& v) const {
		Vector2D r;
		r.x = this->x - v.x;
		r.y = this->y - v.y;
		return r;
	};

	Vector2D operator*(T d) const{
			Vector2D r;
			r.x = x * d;
			r.y = y * d;
			return r;
	};

	T operator*(const Vector2D& d) const {
		return ((d.x * this->x) + (d.y * this->y));
	};

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
		os << "(" << v.x << "," << v.y << ")";
		return os;
	};
};
#endif 