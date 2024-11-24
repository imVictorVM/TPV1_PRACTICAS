#pragma once

class Game;

class GameObject {
protected:
	Game* gamePointer;
public:

	GameObject(Game* g);
	virtual ~GameObject() = 0;
	virtual void render() const = 0;
	virtual void update() = 0;
	
};