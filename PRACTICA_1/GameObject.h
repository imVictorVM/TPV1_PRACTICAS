#pragma once

class Game;
class PlayState;

class GameObject {
protected:
	PlayState* gamePointer;
public:

	GameObject(PlayState* g);
	virtual ~GameObject() = 0;
	virtual void render() const = 0;
	virtual void update() = 0;
	
};