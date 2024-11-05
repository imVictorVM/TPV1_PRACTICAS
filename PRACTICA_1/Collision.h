#pragma once
struct Collision {
	bool collides;
	bool damages;

	operator bool() const { return collides; }
};